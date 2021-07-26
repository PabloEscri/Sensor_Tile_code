/*****************************************************************************
* | File      	:   DEV_Config.c
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
#include "DEV_Config.h"

/******************************************************************************
function:
	Uart receiving and sending
******************************************************************************/
UART_HandleTypeDef hlpuart1;

static void GPS_UART_Error_Handler(void);

UBYTE DEV_Uart_ReceiveByte()
{
	UBYTE i[2];
	HAL_UART_Receive(&hlpuart1, i, 1, 0XFFFF);
	return i[0];
}

void DEV_Uart_SendByte(char data)
{
	UBYTE i[2] = {data};
	HAL_UART_Transmit(&hlpuart1, i, 1, 0xFFFF);
}

void DEV_Uart_SendString(char *data)
{
	UWORD i;

	for(i=0; data[i] != '\0'; i++){
		HAL_UART_Transmit(&hlpuart1, data+i, 1, 0xFFFF);
	}
}

void DEV_Uart_ReceiveString(char *data, UWORD Num)
{
  HAL_UART_Receive(&hlpuart1, data, Num, 0XFFFF);
	data[Num-1] = '\0';
}

void DEV_Set_GPIOMode(GPIO_TypeDef* GPIO_Port, UWORD Pin, UWORD mode)
{
//Habilitamos todo el puerto
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
}


void DEV_Set_Baudrate(UDOUBLE Baudrate)
{


	//Habilitamos todo el puerto
	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
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
	  /* USER CODE BEGIN L
}
static void GPS_UART_Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

static void GPS_UART_Error_Handler(void){};
