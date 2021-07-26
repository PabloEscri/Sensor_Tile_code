/*
 * LORA_Uart.c
 *
 *  Created on: Apr 29, 2021
 *      Author: pablo
 */


/*****************************************************************************
* | File      	:   LORA_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LORA_Uart.h"

/******************************************************************************
function:
	Uart receiving and sending
******************************************************************************/
UART_HandleTypeDef huart5;
static void LORA_UART_Error_Handler(void);
UBYTE LORA_Uart_ReceiveByte()
{
	UBYTE i[2];
	HAL_UART_Receive(&huart5, i, 1, 0XFFFF);
	return i[0];
}

void LORA_Uart_SendByte(char data)
{
	UBYTE i[2] = {data};
	HAL_UART_Transmit(&huart5, i, 1, 0xFFFF);
}

void LORA_Uart_SendString(char *data)
{
	UWORD i;

	for(i=0; data[i] != '\0'; i++){
		HAL_UART_Transmit(&huart5, data+i, 1, 0xFFFF);
	}
}

void LORA_Uart_ReceiveString(char *data, UWORD Num)
{
  HAL_UART_Receive(&huart5, data, Num, 0XFFFF);
	data[Num-1] = '\0';
}

void LORA_Set_GPIOMode(GPIO_TypeDef* GPIO_Port, UWORD Pin, UWORD mode)
{
//Habilitamos todo el puerto
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
}


void LORA_Set_Baudrate(UDOUBLE Baudrate)
{


	//Habilitamos el puerto

	huart5.Instance = UART5;
	  huart5.Init.BaudRate = Baudrate;
	  huart5.Init.WordLength = UART_WORDLENGTH_8B;
	  huart5.Init.StopBits = UART_STOPBITS_1;
	  huart5.Init.Parity = UART_PARITY_NONE;
	  huart5.Init.Mode = UART_MODE_TX_RX;
	  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if (HAL_UART_Init(&huart5) != HAL_OK)
	  {
		  LORA_UART_Error_Handler();
	  }
}
static void LORA_UART_Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
