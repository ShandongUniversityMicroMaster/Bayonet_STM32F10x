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
	
#include "Bayonet_TIM.h"
#include "Bayonet_UART.h"
#include "Bayonet_RCC.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_GPIO.h"

uint8_t channel;

void Bayonet_TIM_Active(TIM_TypeDef *TIMx, uint8_t Mode, uint32_t CHx)
{
	//RCC.
	if(TIMx == TIM1)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM1);
		channel = TIM1_UP_IRQn;
	}
	else if(TIMx == TIM2)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM2);
		switch(Mode)
		{
			case Bayonet_TIM_MODE_INT:
				channel = TIM2_IRQn;
				break;
			case Bayonet_TIM_MODE_PWM:
				Bayonet_RCC_Active(Bayonet_RCC_GPIOA);
				Bayonet_RCC_Active(Bayonet_RCC_AFIO);
				if(CHx & Bayonet_TIM_CH0)
					Bayonet_GPIO_Init(GPIOA, 0, Bayonet_GPIO_MODE_GPOAPP);
				if(CHx & Bayonet_TIM_CH0)
					Bayonet_GPIO_Init(GPIOA, 1, Bayonet_GPIO_MODE_GPOAPP);
				if(CHx & Bayonet_TIM_CH0)
					Bayonet_GPIO_Init(GPIOA, 2, Bayonet_GPIO_MODE_GPOAPP);
				if(CHx & Bayonet_TIM_CH0)
					Bayonet_GPIO_Init(GPIOA, 3, Bayonet_GPIO_MODE_GPOAPP);
				break;
		}
	}
	else if(TIMx == TIM3)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM3);
		channel = TIM3_IRQn;
	}
	else if(TIMx == TIM4)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM4);
		channel = TIM4_IRQn;
	}
	/*else if(TIMx == TIM5)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM5);
		channel = TIM5_IRQn;
	}
	else if(TIMx == TIM6)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM6);
		channel = TIM6_IRQn;
	}
	else if(TIMx == TIM7)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM7);
		channel = TIM7_IRQn;
	}
	else if(TIMx == TIM8)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM8);
		channel = TIM8_UP_IRQn;
	}*/
	else
		AssertFailed("TIM not exist.", __FILE__, __LINE__);
}

//TIM2-7
void Bayonet_TIM_INT_Init(TIM_TypeDef *TIMx, uint32_t Prescaler, uint32_t ReloadValue, uint8_t PrePriority, uint8_t SubPriority)
{
	Bayonet_TIM_Active(TIMx, Bayonet_TIM_MODE_INT, 0);
	
	TIMx->PSC = Prescaler;
	TIMx->ARR = ReloadValue;
	TIMx->DIER |= TIM_DIER_UIE;
	TIMx->CR1 |= TIM_CR1_CEN;
	Bayonet_NVIC_Init(channel, PrePriority, SubPriority);
}

void Bayonet_TIM_PWM_Init(TIM_TypeDef *TIMx, uint32_t Prescaler, uint32_t ReloadValue, uint32_t CHx)
{
	Bayonet_TIM_Active(TIMx, Bayonet_TIM_MODE_PWM, CHx);
	
	TIMx->PSC = Prescaler - 1;
	TIMx->ARR = ReloadValue;
	
	TIMx->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;		//PWM Mode 2.
	TIMx->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIMx->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
	TIMx->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
	TIMx->CCMR1 |= TIM_CCMR1_IC1PSC_0;
	TIMx->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIMx->CR1 |= TIM_CR1_ARPE;
	TIMx->CR1 |= TIM_CR1_CEN;
	TIMx->CCR1 = 20;
	TIMx->CCR2 = 20;
	TIMx->CCR3 = 20;
	TIMx->CCR4 = 20;
}
