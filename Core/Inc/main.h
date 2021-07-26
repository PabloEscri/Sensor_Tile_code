/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


//####################################################################
//DEFINES: Parámetros de configuración
//####################################################################
#define PERIODO_TOMA_DATOS     10			 		//Muestreo cada X ms
#define PERIODO_ENTRE_ESCANEOS 60000			 	//60 segundos
#define TIEMPO_ESCANEO_BLE         3000			    //3  segundos de escaneo

#define FS_ACC LSM6DSM_2g							//FS del Acc
#define UMBRAL_ACC 0x02								//Threshold Acc  segundos de escaneo
#define UMBRAL_DURATION 0x02						//Duration Acc  segundos de escaneo
#define ITERACIONES_TRAS_PASARSE_UMBRAL 100		//Numero de muestras tras pasarse Threshold Acc  segundos de escaneo
#define FREQ_DURANTE_LP 12.0f						//Frecuencia muestreo durante dormir
#define FREQ_DURANTE_HP 52.0f						//Frecuencia muestreo durante adquisición
#define TIEMPO_ENTRE_EXTRACCIONES_DE_DATOS 	0		//Tiempo espera entre envío de 20 bytes de ficheros
#define ID_UNIDADES '4'								//Nombre_dispositivo HOWLAX  ----> Opciones: HOWLA1..HOWLA9..HOWLAA...HOWLAZ
#define FIN_TRAMA_EXTRACCION	"FIN"	//Trama cierre fichero enviado
#define SIZE_FIN_TRAMA_EXTRACCION	4	//Tamaño de la trama cierre fichero enviado
//####################################################################


#include "stm32l4xx_hal.h"
#define DEVICE_ID 1
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */



/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
