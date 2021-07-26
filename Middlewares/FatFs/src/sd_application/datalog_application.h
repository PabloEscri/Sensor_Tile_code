/**
  ******************************************************************************
  * @file    datalog_application.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version V4.1.0
  * @date    26-May-2020
  * @brief   Header for datalog_application.c module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020  STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DATALOG_APPLICATION_H
#define __DATALOG_APPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "../ff.h"
#define MAX_TRIALS_OPENS_SD 10

void DATALOG_SD_Init(void);
void DATALOG_SD_DeInit(void);

uint8_t DATALOG_SD_Log_Enable(uint8_t AccessControl);
extern void DATALOG_SD_Log_Disable(void);

uint8_t DATALOG_SD_LogAudio_Enable(void);
void DATALOG_SD_LogAudio_Disable(void);

void writeAudio_on_sd(void);

void DATALOG_SD_NewLine(void);
void uSdWriteSpeedTest(char* myData); // AST

void write_SD(char * cadena);
FRESULT cerrar_SD(void);
void abrir_SD_new(char * cadena);
void abrir_SD(void);

void write_SD_BT(char * cadena);
void cerrar_SD_BT(void);

void abrir_SD_BT(void);
void abrir_SD_new_BT(char * cadena);

FRESULT get_first_file_path (
    char* path,        /* Start node to be scanned (***also used as work area***) */
	DIR * dir_out
);
void get_next_file_path (
    char* path,       /* Start node to be scanned (***also used as work area***) */
	DIR * dir_in
);
uint32_t contador_ficheros(void);
void leer_fichero(char * path, char* buff, int buf_size);
uint16_t size_fichero(char * path);
#ifdef __cplusplus
}
#endif

#endif /* __DATALOG_APPLICATION_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
