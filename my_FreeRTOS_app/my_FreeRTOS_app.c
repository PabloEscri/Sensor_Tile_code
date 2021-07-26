/*
 * my_FreeRTOS_app.c
 *
 *  Created on: Apr 27, 2021
 *  Author: Pablo Escribano
 */

#include "my_FreeRTOS_app.h"
#include "sensor_service.h"
#include "cmsis_os2.h"
#include <inttypes.h>

//--------------------------------------------------------------------
//FUNCIONES: utilizadas en este archivo
//--------------------------------------------------------------------
//Funciones para la gestión de la máquina de estados
static void maquina_estados(void *argument);

//Funciones de leer de los sensores
static void leer_sensores(void *argument);
static void procesar_datos(void *argument);


//Funciones de gestión de BLE
static void gestionar_comandos_BLE(void *argument);
static void enviar_BLE(void *argument);

//Función que indica un pulso de vida
static void dormir_uc(void *argument);

static void Escaneo(void *argument);

//Funciones de inicialización
static void Iniciar_sensores(void);
static void crear_configuracion_archivos_inicial(void);

//Extraccion
static FRESULT extraer_fichero(void *argument);

//Otras:
void MCU_PowerSave(void);
void iniciar_pin_SWDIO(void);
void encender_zona_3v3(void);
void apagar_zona_3v3(void);
FRESULT scan_files (char* path /* Start node to be scanned (***also used as work area***) */);
static void PA2_Init(void);
static void wake_up_uc(void);

//--------------------------------------------------------------------
//VARIABLES: utilizadas en este archivo
//--------------------------------------------------------------------
//Variables de estado globales para todos los archivos
Estados_Uc_t estado_uc_actual = BAJO_CONSUMO;
Estados_Uc_t estado_uc_actual_ant = BAJO_CONSUMO;

//Variables para la SD:
static char nombre_fichero_sensores[100]; //Nombre del fichero con datos de sensores
static char nombre_fichero_ble[100]; //Nombre del fichero con datos de sensores

static char nombre_fichero_raw[100]; //Nombre del fichero con datos de sensores
volatile int despertar = 0;
volatile int estaba_dormido = 1;

//Variables para FreeRTOS:
static osThreadId_t dormir_uc_Id;
const osThreadAttr_t dormir_uc_Att = {
  .name = "pulso_de_vida",
  .priority = (osPriority_t) osPriorityNone,
  .stack_size = 128 * 10
};

static osThreadId_t gestionar_comandos_BLE_Id;
const osThreadAttr_t gestionar_comandos_BLE_Att = {
  .name = "gestionar_comandos_BLE",
  .priority = (osPriority_t) osPriorityISR,
  .stack_size = 128 * 20
};

static osThreadId_t leer_sensores_Id;
const osThreadAttr_t leer_sensores_Atributos = {
  .name = "leer_sensores",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 10
};

static osThreadId_t procesar_datos_Id;
const osThreadAttr_t procesar_datos_Attr = {
  .name = "procesar_datos",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 20
};

static osThreadId_t enviar_BLE_Id;
const osThreadAttr_t enviar_BLE_Attr = {
  .name = "enviar_BLE",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 128 * 10
};

static osThreadId_t maquina_estados_Id;
const osThreadAttr_t maquina_estados_Attr = {
  .name = "enviar_BLE",
  .priority = (osPriority_t) osPriorityRealtime7,
  .stack_size = 128 * 20
};

static osThreadId_t escaneo_Id;
const osThreadAttr_t escaneo_Att = {
  .name = "guardar_sd",
  .priority = (osPriority_t) osPriorityRealtime6,
  .stack_size = 128 * 20
};


static osThreadId_t extraer_fichero_Id;
const osThreadAttr_t extraccion_Att = {
  .name = "extraccion",
  .priority = (osPriority_t) osPriorityRealtime6,
  .stack_size = 128 * 50
};

osSemaphoreId_t ble_semaphore_Id,maquina_estados_semaphore_Id, escaneo_semaphore_Id, extraccion_semaphore_Id,dormir_uc_semaphore_Id; //Semáforo para liberar o no token de procesar datos de BLE
osMessageQueueId_t Q_Raw_Data;    //Cola necesaria para almacenar los datos


//Variables para Procesado de datos:
#define VECTOR_CIRCULAR_VENTANA_SIZE 40 //20 = 800 ms   Tamaño del vector circular
#define AVANCE_VECTOR_CIRCULAR VECTOR_CIRCULAR_VENTANA_SIZE/2
#define VECTOR_CIRCULAR_SIZE (VECTOR_CIRCULAR_VENTANA_SIZE + AVANCE_VECTOR_CIRCULAR)
#define GPS_DATA_NUMBER 7

typedef struct {
	BSP_MOTION_SENSOR_Axes_t Axes_accel;
	BSP_MOTION_SENSOR_Axes_t Axes_gyro;
	BSP_MOTION_SENSOR_Axes_t Axes_magne;
  uint32_t Idx;
} MEM_BLOCK_t; //Esctructura para guardar los datos de los sensores y ponerlos en la cola

void Init_my_tasks(void)
{
	Iniciar_sensores();
	//iniciar_pin_SWDIO();
    //encender_zona_3v3();
    DATALOG_SD_Init();
    RTC_Init();
    Init_BlueNRG_Stack(PERIPHERAL);
    Init_BlueNRG_Custom_Services(PERIPHERAL);
    PA2_Init();
	//Iniciamos Kernel
	osKernelInitialize();
	//Creamos las tareas
	//------------------------------------------------------------------------------------------------------------

		//1- Dormir
			dormir_uc_Id = osThreadNew(dormir_uc, NULL, &dormir_uc_Att);
			dormir_uc_semaphore_Id = osSemaphoreNew(1, 0U, NULL);
		//2- Lectura de sensores y procesado de los datos
			leer_sensores_Id = osThreadNew(leer_sensores, NULL, &leer_sensores_Atributos);
			procesar_datos_Id= osThreadNew( procesar_datos, NULL, &procesar_datos_Attr);
		//3- Gestión de los comandos BLE
			gestionar_comandos_BLE_Id = osThreadNew(gestionar_comandos_BLE, NULL, &gestionar_comandos_BLE_Att);
			enviar_BLE_Id = osThreadNew(enviar_BLE, NULL, &enviar_BLE_Attr);
			//Semáforo necesario:
				ble_semaphore_Id = osSemaphoreNew(1U, 0U, NULL);
		//4- Escaneo:
			escaneo_Id	= osThreadNew(Escaneo , NULL, &escaneo_Att);
			escaneo_semaphore_Id = osSemaphoreNew(1U, 1U, NULL);
		//5- Máquina de estados:
			maquina_estados_Id = osThreadNew(maquina_estados, NULL, &maquina_estados_Attr);
			//Semáforo necesario:
				maquina_estados_semaphore_Id = osSemaphoreNew(1U, 1U, NULL);
		//6- Extraccion
				extraccion_semaphore_Id = osSemaphoreNew(1U, 0U, NULL);
				extraer_fichero_Id = osThreadNew( extraer_fichero, NULL, &extraccion_Att);
	//------------------------------------------------------------------------------------------------------------
	//Creamos una cola para enviar los datos entre tareas de forma segura por medio de FreeRTOS
	Q_Raw_Data = osMessageQueueNew (VECTOR_CIRCULAR_SIZE, sizeof(MEM_BLOCK_t),NULL);
	//Lanzamos el Kernel
    osKernelStart();
}

extern uint16_t ConfigServW2STHandle, ConfigCharHandle;
extern DIR directorio_extraccion;
uint8_t Archivo_seleccionado = 0;
static void maquina_estados(void *argument)
{
  for(;;)
  {
	  	  osSemaphoreAcquire(maquina_estados_semaphore_Id, osWaitForever); //Esperamos semáforo y se apagan tareas
		  osThreadSuspend(leer_sensores_Id);
		  osThreadSuspend(procesar_datos_Id);
		  osThreadSuspend(enviar_BLE_Id);
		  osThreadSuspend(dormir_uc_Id);
		  osThreadSuspend(escaneo_Id);
		  osThreadSuspend(extraer_fichero_Id);
		  switch(estado_uc_actual)
		  {
			  case   ESPERA_COMANDOS:
				  if(estaba_dormido == 1)
				  {
					  wake_up_uc();
				  }
				  //osThreadResume(enviar_BLE_Id);
				  osThreadResume(dormir_uc_Id);
				  osSemaphoreRelease(dormir_uc_semaphore_Id);
			  break;
			  case TOMANDO_DATOS:
				  	if(estaba_dormido == 1)
				  	{
				  		wake_up_uc();
				  	}
				  crear_configuracion_archivos_inicial();

				  abrir_SD();
				  abrir_SD_RAW();

				  osThreadResume(leer_sensores_Id);
				  osThreadResume(procesar_datos_Id);
			  break;
			  case	  BAJO_CONSUMO :

				  osThreadResume(dormir_uc_Id);
				  osSemaphoreRelease(dormir_uc_semaphore_Id);
			  break;
			  case	  STREAMING :
				  /*Actualmente no operativo*/
				  //osThreadResume(leer_sensores_Id);
				  //osThreadResume(procesar_datos_Id);
				  //osThreadResume(enviar_BLE_Id);
			 break;
			  case	 EXTRACCION :
			  {
				  if(estaba_dormido == 1)
				  {
				  	wake_up_uc();
				  }
				  Archivo_seleccionado = 0;
			  }
			  break;
			  case   DORMIDO:
			  {
			  }
			  break;
		  }
  }
}
static void dormir_uc(void *argument)
{
  for(;;)
  {

	  //Espero a que me liberen semáforo desde otra tarea
	  osSemaphoreAcquire(dormir_uc_semaphore_Id,osWaitForever);

	  //Habilito la interrupción asociada al ACC
	  HAL_NVIC_SetPriority(EXTI2_IRQn, 15, 0);
	  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	  DATALOG_SD_DeInit();
	  apagar_zona_3v3();

	  osThreadSuspend(gestionar_comandos_BLE_Id);
	  char numero_ficheros_str[50];
	  int size = sprintf(numero_ficheros_str,"Me duermo");
	  aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, size,numero_ficheros_str);
	  osThreadResume(gestionar_comandos_BLE_Id);

	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM6DSM_0, MOTION_GYRO, FREQ_DURANTE_LP);
	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM6DSM_0, MOTION_ACCELERO,FREQ_DURANTE_LP);
	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM303AGR_MAG_0, MOTION_MAGNETO, FREQ_DURANTE_LP);
	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM303AGR_MAG_0, MOTION_ACCELERO, FREQ_DURANTE_LP);

	  estaba_dormido =1;
	  HAL_PWREx_EnterSTOP0Mode(PWR_STOPENTRY_WFI);

	  if(despertar == 1)
	  {
		  osThreadSuspend(gestionar_comandos_BLE_Id);
		 	  numero_ficheros_str[50];
		 	  size = sprintf(numero_ficheros_str,"Me levanto tomo");
		 	  aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, size,numero_ficheros_str);
		 	  osThreadResume(gestionar_comandos_BLE_Id);

	      estado_uc_actual_ant = TOMANDO_DATOS;
	 	  estado_uc_actual = TOMANDO_DATOS;
	 	  despertar = 0;
	 	  osSemaphoreRelease(maquina_estados_semaphore_Id);
	  }
	  else
	  {
		  HAL_Delay(1000);
		  osThreadSuspend(gestionar_comandos_BLE_Id);
		  		 	  numero_ficheros_str[50];
		  		 	  size = sprintf(numero_ficheros_str,"Me levanto duermo");
		  		 	  aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, size,numero_ficheros_str);
		  		 	  osThreadResume(gestionar_comandos_BLE_Id);
		  		 	  HAL_Delay(1000);
		  osSemaphoreRelease(dormir_uc_semaphore_Id);
	  }

  }

}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_2)
  {
	  /* EXTI interrupt init*/
	 HAL_NVIC_DisableIRQ(EXTI2_IRQn); //Desactivo la Interrupción hasta terminar de guardar el fichero
	 despertar = 1;

  }
}
static void wake_up_uc(void)
{
	  //Para HAL:
		HAL_MspInit();
		iniciar_pin_SWDIO();
		encender_zona_3v3();
		//Para BLE:
		//Pines para SPI BLE:
		HAL_PWREx_EnableVddIO2();
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		//Incio SPI para BLE:
		BSP_SPI1_Init();
		//Para sensores:
		BSP_SPI2_Init();

		DATALOG_SD_Init();
		BSP_MOTION_SENSOR_SetOutputDataRate(LSM6DSM_0, MOTION_GYRO, FREQ_DURANTE_HP);
		BSP_MOTION_SENSOR_SetOutputDataRate(LSM6DSM_0, MOTION_ACCELERO,FREQ_DURANTE_HP);
		BSP_MOTION_SENSOR_SetOutputDataRate(LSM303AGR_MAG_0, MOTION_MAGNETO, FREQ_DURANTE_HP);
		BSP_MOTION_SENSOR_SetOutputDataRate(LSM303AGR_MAG_0, MOTION_ACCELERO, FREQ_DURANTE_HP);
		estaba_dormido =0;
}
static void leer_sensores(void *argument)
{
	 //Leo los sensores del IMU.
	BSP_MOTION_SENSOR_Axes_t Axes_accel;
	BSP_MOTION_SENSOR_Axes_t Axes_gyro;
	BSP_MOTION_SENSOR_Axes_t Axes_magne;
	MEM_BLOCK_t msg;
	uint32_t contador;
  for(;;)
  {

	  BSP_MOTION_SENSOR_GetAxes(LSM6DSM_0,MOTION_ACCELERO ,&Axes_accel);
	  BSP_MOTION_SENSOR_GetAxes(LSM6DSM_0,MOTION_GYRO,&Axes_gyro);
	  BSP_MOTION_SENSOR_GetAxes(LSM303AGR_MAG_0,MOTION_MAGNETO ,&Axes_magne);

	   //Leemos el valor del sensor de presión.
	   //float Value;
	   //BSP_ENV_SENSOR_GetValue(LPS22HB_0, ENV_PRESSURE, &Value);
	  // uint32_t tick = HAL_GetTick(); //Falta por meterlo en el mensaje que se guarda en la cola.
	   msg.Axes_accel = Axes_accel;
	   msg.Axes_gyro = Axes_gyro;
	   msg.Axes_magne = Axes_magne;
	   msg.Idx = contador;
	   contador++;
	   osMessageQueuePut(Q_Raw_Data, &msg,osPriorityNormal7 , osWaitForever); //PONGO LOS DATOS DE LOS SENSORES EN LA COLA
	 osDelay(PERIODO_TOMA_DATOS);
  }
}
char fichero_actual[100];
static void gestionar_comandos_BLE(void *argument) //Esta tarea se encarga de gestionar los eventos BLE
{
  for(;;)
  {
	  osSemaphoreAcquire(ble_semaphore_Id, osWaitForever);
	  if(estaba_dormido == 1)
	  {
		  wake_up_uc();
	  }

	  hci_user_evt_proc();

	  if(estado_uc_actual_ant != estado_uc_actual)
	  {
		  estado_uc_actual_ant = estado_uc_actual; //Importante ya que sino se libera +1 semáforos de maquina de estados
		  osSemaphoreRelease(maquina_estados_semaphore_Id);
	  }
	  if((estado_uc_actual == EXTRACCION) && ( Archivo_seleccionado ))
	  {
		  Archivo_seleccionado = 0;
		  osSemaphoreRelease(extraccion_semaphore_Id);
		  osThreadResume(extraer_fichero_Id);
	  }
  }
}
extern uint8_t connection;
static void enviar_BLE(void *argument)
{
		char t_ptr[30];
		int i = 0;
		MEM_BLOCK_t msg_r;
		char escribir_hora[200];
		char escribir_sd[200];
		uint32_t tick = HAL_GetTick();
		for(;;)
		{
			osDelay(100);

				if(estado_uc_actual == ESPERA_COMANDOS)
				{
					//Se suspende la tarea que procesa evento cuando salta una interrupción para que no se active antes de terminar de ejecutar la actualización de la característica.
					osThreadSuspend(gestionar_comandos_BLE_Id);
					uint32_t my_tick = HAL_GetTick();
					int size = sprintf(t_ptr,"%ld",my_tick);
					aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, size,t_ptr);
					osThreadResume(gestionar_comandos_BLE_Id);
				}
				else if (estado_uc_actual == STREAMING)
				{
					 osMessageQueueGet (Q_Raw_Data, &msg_r, osPriorityNormal7 , osWaitForever);
					 RTC_obtener_hora_str(escribir_hora);
					 //sprintf(escribir_sd,"%s;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld%ld\r\n",escribir_hora,tick,msg_r.Axes_accel.x,  msg_r.Axes_accel.y, msg_r.Axes_accel.z, msg_r.Axes_gyro.x,   msg_r.Axes_gyro.y,  msg_r.Axes_gyro.z, msg_r.Axes_magne.x, msg_r.Axes_magne.y,  msg_r.Axes_magne.z, a_abs_2);
					 //write_SD(escribir_sd);
					 sprintf(escribir_sd,"%s;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld\r\n",escribir_hora,tick,msg_r.Axes_accel.x,  msg_r.Axes_accel.y, msg_r.Axes_accel.z, msg_r.Axes_gyro.x,   msg_r.Axes_gyro.y,  msg_r.Axes_gyro.z, msg_r.Axes_magne.x, msg_r.Axes_magne.y,  msg_r.Axes_magne.z);
				}
		}
}
static FRESULT extraer_fichero(void *argument)
{
  for(;;)
  {
	  osSemaphoreAcquire(extraccion_semaphore_Id, osWaitForever);
	  char ruta[100];
	  char buff[100];
	  sprintf(ruta,"%s/%s_sen.csv", fichero_actual,fichero_actual);
	  //leer_fichero(ruta, buff, 100);
	  FIL fsrc;
	  FRESULT fr;          /* FatFs function common result code */
	  UINT br;         /* File read/write count */

	  fr = f_open(&fsrc, ruta, FA_READ);
	  if(fr == FR_OK)
	  {
		  uint16_t size = f_size(&fsrc);
		  if (fr) return (int)fr;
		  for (;;)
		  {
			  f_read(&fsrc, buff, 20, &br);  /* Read a chunk of data from the source file */

			  osThreadSuspend(gestionar_comandos_BLE_Id);
			  aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, 20,buff);
			  osThreadResume(gestionar_comandos_BLE_Id);

			  if (br == 0) break; /* error or eof */
			  osDelay(TIEMPO_ENTRE_EXTRACCIONES_DE_DATOS);
		  }
	      /* Close open files */
		  aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, SIZE_FIN_TRAMA_EXTRACCION, FIN_TRAMA_EXTRACCION);
		  fr = f_close(&fsrc);
	  }
	  else
	  {
		  aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, sizeof("Not Allowed"),"Not Allowed");
	  }
      Archivo_seleccionado = 0;
  }

}
static void Escaneo(void *argument)
{
  for(;;)
  {

  }
}
static void Iniciar_sensores(void)
{
	  //El pin PA2 sirve para interrupciones del Acelerómetro.
	  // Inicializamos el sensor de LSM6DSM y el sensor LSM303AGR_MAG
	  BSP_MOTION_SENSOR_Init(LSM6DSM_0, MOTION_GYRO|MOTION_ACCELERO);
	  BSP_MOTION_SENSOR_Init(LSM303AGR_MAG_0, MOTION_MAGNETO);

	  //Habilito los sensores, TODO: Mirar si es necesario
	  BSP_MOTION_SENSOR_Enable(LSM6DSM_0, MOTION_GYRO);
	  BSP_MOTION_SENSOR_Enable(LSM6DSM_0, MOTION_ACCELERO);
	  BSP_MOTION_SENSOR_Enable(LSM303AGR_MAG_0, MOTION_MAGNETO);

	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM6DSM_0, MOTION_GYRO, FREQ_DURANTE_HP);
  	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM6DSM_0, MOTION_ACCELERO,FREQ_DURANTE_HP);
  	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM303AGR_MAG_0, MOTION_MAGNETO, FREQ_DURANTE_HP);
  	  BSP_MOTION_SENSOR_SetOutputDataRate(LSM303AGR_MAG_0, MOTION_ACCELERO, FREQ_DURANTE_HP);

  	  BSP_MOTION_SENSOR_SetFullScale(LSM6DSM_0, MOTION_ACCELERO,  FS_ACC);
	  ACCEL_MOTION_SENSOR_wakeup_Threshold(UMBRAL_ACC,UMBRAL_DURATION);
}

static void procesar_datos(void *argument)
{
	   MEM_BLOCK_t msg_r;
	   static contador = 0;
	   char escribir_sd[200];
	   char escribir_hora[100];
	   for(;;)
	   {
	 	 osMessageQueueGet (Q_Raw_Data, &msg_r, osPriorityNormal7 , osWaitForever);
	 	 osSemaphoreAcquire(escaneo_semaphore_Id,osWaitForever);
		 uint32_t tick = HAL_GetTick();
		 //RTC_obtener_hora_str(escribir_hora);

		/* uint16_t datos_sensores[12];
		 datos_sensores[0] =   tick>>16;
		 datos_sensores[1] =   tick & 0xFFFF;
		 datos_sensores[2] =   contador * PERIODO_TOMA_DATOS; //Contador de secuencia
		 datos_sensores[3] =   msg_r.Axes_accel.x; //Accel X
		 datos_sensores[4] =   msg_r.Axes_accel.y; //Accel Y
		 datos_sensores[5] =   msg_r.Axes_accel.z; //Accel Z
		 datos_sensores[6] =   msg_r.Axes_gyro.x; //Gyro X
		 datos_sensores[7] =   msg_r.Axes_gyro.y; //Gyro Y
		 datos_sensores[8] =   msg_r.Axes_gyro.z; //Gyro Z
		 datos_sensores[9] =   msg_r.Axes_magne.x; //Magne X
		 datos_sensores[10] =  msg_r.Axes_magne.y; //Magne Y
		 datos_sensores[11] =  msg_r.Axes_magne.z; //Magne Z*/

		// Año - mes - dia - hora -minuto - segundo   .dat
		//
		 sprintf(escribir_sd,"%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld;%ld\r\n", contador * PERIODO_TOMA_DATOS,tick,msg_r.Axes_accel.x,  msg_r.Axes_accel.y, msg_r.Axes_accel.z, msg_r.Axes_gyro.x,   msg_r.Axes_gyro.y,  msg_r.Axes_gyro.z, msg_r.Axes_magne.x, msg_r.Axes_magne.y,  msg_r.Axes_magne.z);
		 write_SD(escribir_sd);
		 //write_SD_RAW( datos_sensores,24);

		 if(contador ==ITERACIONES_TRAS_PASARSE_UMBRAL) //Guardo en la SD cada ITERACIONES_TRAS_PASARSE_UMBRAL muestras
		 {
			 cerrar_SD();
			 cerrar_SD_RAW();
			 //abrir_SD();
			 osThreadSuspend(gestionar_comandos_BLE_Id);
			 uint32_t my_tick = HAL_GetTick();
			 char t_ptr[30];
			 int size = sprintf(t_ptr,"%ld",my_tick);
			 aci_gatt_update_char_value(ConfigServW2STHandle, ConfigCharHandle, 0, size,t_ptr);
			 osThreadResume(gestionar_comandos_BLE_Id);
			 contador =0 ;

			 //Liberar semáforo:
			 estado_uc_actual_ant = BAJO_CONSUMO;
			 estado_uc_actual = BAJO_CONSUMO;
			 osSemaphoreRelease(maquina_estados_semaphore_Id);
		 }
		 else
		 {
			 contador++;
		 }
    	  osSemaphoreRelease(escaneo_semaphore_Id); //Se libera semáforo para guardar en la SD
		  osDelay(PERIODO_TOMA_DATOS);
  }
}
void iniciar_pin_SWDIO(void)
{
GPIO_InitTypeDef GPIO_InitStruct = {0};
 __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET);//SWDIO APAGO
}

void encender_zona_3v3(void)
{
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET);//SWDIO APAGO
}
void apagar_zona_3v3(void)
{
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET);//SWDIO APAGO
}

static void PA2_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  /*Configure GPIO pin : PA2 */
	  GPIO_InitStruct.Pin = GPIO_PIN_2;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  /* EXTI interrupt init*/
	  HAL_NVIC_SetPriority(EXTI2_IRQn, 15, 0);
	  //HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}
void crear_configuracion_archivos_inicial(void)
{
	char escribir_sd[100];
	RTC_obtener_dia_str(escribir_sd);
	while(f_mkdir(escribir_sd)!=FR_OK)
	{
		RTC_obtener_dia_str(escribir_sd);
		DATALOG_SD_Init();
	}
	sprintf(nombre_fichero_sensores,"%s/%s%s",escribir_sd,escribir_sd,"_sen");
	//Se crea un nuevo fichero en la SD para los sensores:

	abrir_SD_new(nombre_fichero_sensores);
	write_SD("Fecha;Timestamp;Accel_x;Accel_y;Accel_z;Gyro_x;Gyro_y;Gyro_z;Magnet_x;Magnet_y;Magnet_z\r\n");
	cerrar_SD();

	sprintf(nombre_fichero_raw,"%s/%s%s",escribir_sd,escribir_sd,"_dat");
	abrir_SD_new_RAW(nombre_fichero_raw);
	write_SD_RAW("Fecha;Timestamp;Accel_x;Accel_y;Accel_z;Gyro_x;Gyro_y;Gyro_z;Magnet_x;Magnet_y;Magnet_z\r\n",strlen("Fecha;Timestamp;Accel_x;Accel_y;Accel_z;Gyro_x;Gyro_y;Gyro_z;Magnet_x;Magnet_y;Magnet_z\r\n"));
	cerrar_SD_RAW();

	cerrar_SD_BT();
	//Se crea un nuevo fichero en la SD para los dispositivos BLE:
	sprintf(nombre_fichero_ble,"%s/%s%s",escribir_sd,escribir_sd,"_BT");
	abrir_SD_new_BT(nombre_fichero_ble);
	write_SD_BT("Dispositivos_BT\r\n");
	write_SD_BT("Nombre\r\n");
	char BLE_NAME[50];
	sprintf(BLE_NAME,"HOWLA%c",ID_UNIDADES);
	write_SD_BT(BLE_NAME);
	cerrar_SD_BT();
}


