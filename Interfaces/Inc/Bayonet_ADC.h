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
	
#ifndef __BAYONET_ADC_H
#define __BAYONET_ADC_H

#include "stm32f10x.h"
#include "Bayonet_Config.h"

typedef enum
{
	Bayonet_ADC_Channel_0,
	Bayonet_ADC_Channel_1,
	Bayonet_ADC_Channel_2,
	Bayonet_ADC_Channel_3,
	Bayonet_ADC_Channel_4,
	Bayonet_ADC_Channel_5,
	Bayonet_ADC_Channel_6,
	Bayonet_ADC_Channel_7,
	Bayonet_ADC_Channel_8,
	Bayonet_ADC_Channel_9,
	Bayonet_ADC_Channel_10,
	Bayonet_ADC_Channel_11,
	Bayonet_ADC_Channel_12,
	Bayonet_ADC_Channel_13,
	Bayonet_ADC_Channel_14,
	Bayonet_ADC_Channel_15
}Bayonet_ADC_Channel;

typedef enum
{
	Bayonet_ADC_SampleTime_1Cycles5,
	Bayonet_ADC_SampleTime_7Cycles5,
	Bayonet_ADC_SampleTime_13Cycles5,
	Bayonet_ADC_SampleTime_28Cycles5,
	Bayonet_ADC_SampleTime_41Cycles5,
	Bayonet_ADC_SampleTime_55Cycles5,
	Bayonet_ADC_SampleTime_71Cycles5,
	Bayonet_ADC_SampleTime_239Cycles5
}Bayonet_ADC_SampleTime;

extern uint32_t ADC_Buff[3][20];
extern Bayonet_ADC_Channel tableSequence[3][16];

void Bayonet_ADC_Init_OneTimeConversion(ADC_TypeDef *ADCx, Bayonet_ADC_Channel ADC_CHx);
void Bayonet_ADC_Init_ContinuousConversion(ADC_TypeDef *ADCx, uint8_t length, Bayonet_ADC_Channel ADC_CHxs[], Bayonet_ADC_SampleTime SampleTime);
uint16_t Bayonet_ADC_OneTime(ADC_TypeDef *ADCx, Bayonet_ADC_Channel channel);
void Bayonet_ADC_EnableInterrupt_EOC(ADC_TypeDef *ADCx, uint8_t prePriority, uint8_t subPriority);

#endif
