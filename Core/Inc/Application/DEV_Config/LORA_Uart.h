/*
 * LORA_Uart.h
 *
 *  Created on: Apr 29, 2021
 *      Author: pablo
 */

#ifndef LORA_CONFIG_LORA_UART_H_
#define LORA_CONFIG_LORA_UART_H_

/*****************************************************************************
* | File      	:   LORA_Config.h
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

#include "stm32l4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t




/**
 * delay x ms
**/
#define LORA_Delay_ms(__xms)	HAL_Delay(__xms)

/*-----------------------------------------------------------------------------*/
UBYTE LORA_Uart_ReceiveByte(void);
void LORA_Uart_SendByte(char data);
void LORA_Uart_SendString(char *data);
void LORA_Uart_ReceiveString(char *data, UWORD Num);

void LORA_Set_Baudrate(UDOUBLE Baudrate);
void LORA_Set_GPIOMode(GPIO_TypeDef* GPIO_Port, UWORD Pin, UWORD mode);

#endif /* LORA_CONFIG_LORA_UART_H_ */
