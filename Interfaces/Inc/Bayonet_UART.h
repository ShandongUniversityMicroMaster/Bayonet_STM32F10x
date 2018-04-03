/**
	********************************************************************************
	* 
	* MIT License (MIT)
	* 
	* Copyright (c) 2017 Shandong University at Weihai μMaster team
	* @email songqiang.1304521@163.com
	* @github https://github.com/ShandongUniversityMicroMaster/Bayonet_STM32F10x
	*
	* All rights reserved. 
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	* 
  ********************************************************************************
	* The above copyright notice and this permission notice shall be included in all
	* copies or substantial portions of the Software.
	* 
	********************************************************************************
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	* SOFTWARE.
	*
	********************************************************************************
	*/
	
#ifndef __BAYONET_UART_H_
#define __BAYONET_UART_H_

#include "stm32f10x.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

void UART_NVIC_Configuration(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority);
void Bayonet_UART_Init(USART_TypeDef *USARTx, uint32_t bound);
void Bayonet_UART_SendBuff(USART_TypeDef *USARTx, uint8_t *buff, uint16_t count);
void UART_Put_Char(unsigned char DataToSend);
uint8_t UART_Get_Char(void);
void AssertFailed(char *str, char *file, int line);
void Bayonet_UART_SendString(USART_TypeDef *USARTx, char *str);
void Bayonet_UART_EnableInterrupt_RXNE(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority);
void Bayonet_UART_EnableInterrupt_TC(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority);
void Bayonet_UART_EnableInterrupt_TXE(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority);
#endif
