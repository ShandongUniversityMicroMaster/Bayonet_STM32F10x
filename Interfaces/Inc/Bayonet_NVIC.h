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
	
#ifndef __BAYONET_NVIC_H
#define __BAYONET_NVIC_H

#include "stm32f10x.h"
#include "Bayonet_TIM.h"
#include "Bayonet_Config.h"

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

typedef enum{
	Bayonet_NVIC_PriorityGroup_None = 0x0000,
	Bayonet_NVIC_PriorityGroup_0 		= 0x0700,
	Bayonet_NVIC_PriorityGroup_1 		= 0x0600,
	Bayonet_NVIC_PriorityGroup_2 		= 0x0500,
	Bayonet_NVIC_PriorityGroup_3 		= 0x0400,
	Bayonet_NVIC_PriorityGroup_4 		= 0x0300
}Bayonet_NVIC_PriorityGroup;

void Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup NVIC_PriorityGroup);
void Bayonet_NVIC_Init(uint8_t IRQChannel, uint8_t PrePriority, uint8_t SubPriority);
uint8_t Bayonet_NVIC_GetIRQChannel_ADC(ADC_TypeDef* ADCx);
uint8_t Bayonet_NVIC_GetIRQChannel_TIM(TIM_TypeDef *TIMx, Bayonet_TIM_MODE mode);
uint8_t Bayonet_NVIC_GetIRQChannel_DMA(DMA_Channel_TypeDef *CHx);
uint8_t Bayonet_NVIC_GetIRQChannel_SPI(SPI_TypeDef *SPIx);
uint8_t Bayonet_NVIC_GetIRQChannel_EXTI(uint8_t Pinx);
void Bayonet_NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);

#endif
