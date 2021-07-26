/*
 * my_FreeRTOS_app.h
 *
 *  Created on: Apr 27, 2021
 *      Author: pablo
 */

#ifndef MY_FREERTOS_APP_H_
#define MY_FREERTOS_APP_H_
/*
 * my_FreeRTOS_app.c
 *
 *  Created on: 5 dic. 2020
 *      Author: pablo
 */

#include "main.h"

#include <string.h>
#include "stm32l4xx_hal.h"

//Librería para el control de los sensores
#include "SensorTile_env_sensors.h"
#include "SensorTile_motion_sensors.h"
//Librería para el control del BLE
#include "BLE_APP.h"

//Librería para el control de la SD
#include "datalog_application.h"
#include "ff.h"

//Librería para el reloj RTC
#include "../Core/RTC_APP/RTC_APP.h"



void Init_my_tasks(void);

typedef enum
{
  ESPERA_COMANDOS = 0,
  TOMANDO_DATOS = 1,
  STREAMING = 3,
  DORMIDO = 2,
  EXTRACCION = 4,
  BAJO_CONSUMO = 5

} Estados_Uc_t;

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */

#endif /* MY_FREERTOS_APP_H_ */
