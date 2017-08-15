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
	
#ifndef __BAYONET_TIM_H
#define __BAYONET_TIM_H

#include "stm32f10x.h"
#include "Bayonet_Config.h"

typedef enum{
	Bayonet_TIM_MODE_INT, 
	Bayonet_TIM_MODE_PWM, 
	Bayonet_TIM_MODE_ICAP, 
}Bayonet_TIM_MODE;

typedef enum{
	Bayonet_TIM_CH0, 
	Bayonet_TIM_CH1, 
	Bayonet_TIM_CH2, 
	Bayonet_TIM_CH3
}Bayonet_TIM_CHANNEL;

uint8_t Bayonet_TIM_Init_Interrupt(TIM_TypeDef *TIMx, uint32_t microseconds, uint8_t prePriority, uint8_t subPriority);
uint8_t Bayonet_TIM_Init_PWMChannel(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, uint32_t cycleTime);
uint8_t Bayonet_TIM_PWM_Duty(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, uint16_t dutyTime);

#endif
