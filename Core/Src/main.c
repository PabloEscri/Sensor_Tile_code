
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Librerías para los sensores de enviromental (Presión, he desactivado el de temperatura) y para acelerómetro y giroscopio.*/

#include  "my_FreeRTOS_app.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern RTC_HandleTypeDef hrtc;
static void MX_GPIO_Init(void);
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */



/**
  * @brief  The application entry point.
  * @retval int
  */
FIL MyFile;
const TCHAR path[] = "ST.txt";
BYTE mode = FA_CREATE_NEW ;
extern FATFS SDFatFs;
extern char SDPath[4];   /* SD logical drive path */


typedef struct
{
	int segundos;
	int minutos;
	int horas;
} my_time;
#define DATA_NUMBER 60
BLE_Estados_t ESTADO_BLE = CENTRAL;
BLE_Estados_t ESTADO_BLE_ant = PERIPHERAL;



UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart5;

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  	HAL_Init();
    SystemClock_Config();
    Init_my_tasks();
  /* USER CODE BEGIN Init */
	   /*Configure GPIO pin : PA13 */

  /* USER CODE END Init */


}


/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */

  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}


/**
  * @brief System Clock Configuration
  * @retval None
  */

//SD + BLE todo funcionando
 //BLE
 void SystemClock_Config(void)
 {
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_PWR_CLK_ENABLE();
   HAL_PWR_EnableBkUpAccess();
   __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);



   /* Enable the LSE Oscilator */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
   RCC_OscInitStruct.LSEState = RCC_LSE_ON;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
     while(1);
   }

   /* Enable the CSS interrupt in case LSE signal is corrupted or not present */
   HAL_RCCEx_DisableLSECSS();

   /* Enable MSI Oscillator and activate PLL with MSI as source */
   RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
   RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
   RCC_OscInitStruct.HSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_11;
   RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_MSI;
   RCC_OscInitStruct.PLL.PLLM            = 6;
   RCC_OscInitStruct.PLL.PLLN            = 40;
   RCC_OscInitStruct.PLL.PLLP            = 7;
   RCC_OscInitStruct.PLL.PLLQ            = 4;
   RCC_OscInitStruct.PLL.PLLR            = 4;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
     while(1);
   }

   /* Enable MSI Auto-calibration through LSE */
   HAL_RCCEx_EnableMSIPLLMode();

   RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
   PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
   PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
   {
     Error_Handler();
   }


   /* Select MSI output as USB clock source */
   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
   PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
   HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
   clocks dividers */
   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
   {
     while(1);
   }
   PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
     PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
     if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
     {
       Error_Handler();
     }
     /** Configure the main internal regulator output voltage
     */
     if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
     {
       Error_Handler();
     }



 }





/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }

  /* USER CODE END Callback 1 */
}







static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET); //SWCLK el de abajo

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin : PA14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}




/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
 void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
 void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

