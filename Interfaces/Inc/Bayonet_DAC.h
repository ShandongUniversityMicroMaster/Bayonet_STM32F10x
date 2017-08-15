/**
	********************************************************************************
	* 
	* MIT License (MIT)
	* 
	* Copyright (c) 2017 Shandong University at Weihai µMaster team
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
	
#ifndef __BAYONET_DAC_H
#define __BAYONET_DAC_H

#include "stm32f10x.h"
#include <stdbool.h>

typedef enum{
	Bayonet_DAC_CHANNEL1,
	Bayonet_DAC_CHANNEL2
}Bayonet_DAC_CHANNEL;

typedef enum{
	Bayonet_DAC_DATA_WIDTH12,
	Bayonet_DAC_DATA_WIDTH8
}Bayonet_DAC_DATA_WIDTH;

typedef enum{
	Bayonet_DAC_AMPLITUDE_1,
	Bayonet_DAC_AMPLITUDE_3,
	Bayonet_DAC_AMPLITUDE_7,
	Bayonet_DAC_AMPLITUDE_15,
	Bayonet_DAC_AMPLITUDE_31,
	Bayonet_DAC_AMPLITUDE_63,
	Bayonet_DAC_AMPLITUDE_127,
	Bayonet_DAC_AMPLITUDE_255,
	Bayonet_DAC_AMPLITUDE_511,
	Bayonet_DAC_AMPLITUDE_1023,
	Bayonet_DAC_AMPLITUDE_2047,
	Bayonet_DAC_AMPLITUDE_4095
}Bayonet_DAC_AMPLITUDE;

typedef enum{
	Bayonet_DAC_TRIGGER_TIM6,
#ifdef STM32F10X_CL
	Bayonet_DAC_TRIGGER_TIM3,
#else
	Bayonet_DAC_TRIGGER_TIM8,
#endif
	Bayonet_DAC_TRIGGER_TIM7,
	Bayonet_DAC_TRIGGER_TIM5,
	Bayonet_DAC_TRIGGER_TIM2,
	Bayonet_DAC_TRIGGER_TIM4,
	Bayonet_DAC_TRIGGER_EXTI9,
	Bayonet_DAC_TRIGGER_SOFT
}Bayonet_DAC_TRIGGER;

void Bayonet_DAC_Init_WithoutWave(Bayonet_DAC_CHANNEL channeln, uint16_t initValue);
void Bayonet_DAC_Init_NoiseGeneration(Bayonet_DAC_CHANNEL channeln, uint16_t offset, Bayonet_DAC_AMPLITUDE amplitude, Bayonet_DAC_TRIGGER trigger);
void Bayonet_DAC_Init_TriangleGeneration(Bayonet_DAC_CHANNEL channeln, uint16_t offset, Bayonet_DAC_AMPLITUDE amplitude, Bayonet_DAC_TRIGGER trigger);
void Bayonet_DAC_SetOuputLevel(Bayonet_DAC_CHANNEL channeln, uint16_t value);

#endif
