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

//Bayonet_TIM_MODE bayonetTIMMode[14][4] = {0};

uint32_t Bayonet_TIM_CLOCK_IO_Init(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, Bayonet_TIM_MODE Mode)
{
	GPIO_TypeDef *port;
	uint8_t pin;
	uint32_t freq;
	
	if(TIMx == TIM1)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM1);
	}
	else if(TIMx == TIM2)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM2);
		if(Mode != Bayonet_TIM_MODE_INT)
		{
			port = GPIOA;
			if(CHx == Bayonet_TIM_CH0)
				pin = 0;
			else if(CHx == Bayonet_TIM_CH1)
				pin = 1;
			else if(CHx == Bayonet_TIM_CH2)
				pin = 2;
			else if(CHx == Bayonet_TIM_CH3)
				pin = 3;
		}
	}
	else if(TIMx == TIM3)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM3);
		if(Mode != Bayonet_TIM_MODE_INT)
		{
			if(CHx == Bayonet_TIM_CH0)
			{
				port = GPIOA;
				pin = 6;
			}
			else if(CHx == Bayonet_TIM_CH1)
			{
				port = GPIOA;
				pin = 7;
			}
			else if(CHx == Bayonet_TIM_CH2)
			{
				port = GPIOB;
				pin = 0;
			}
			else if(CHx == Bayonet_TIM_CH3)
			{
				port = GPIOB;
				pin = 1;
			}
		}
	}
	else if(TIMx == TIM4)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM4);
		if(Mode != Bayonet_TIM_MODE_INT)
		{
			port = GPIOB;
			if(CHx == Bayonet_TIM_CH0)
				pin = 6;
			else if(CHx == Bayonet_TIM_CH1)
				pin = 7;
			else if(CHx == Bayonet_TIM_CH2)
				pin = 8;
			else if(CHx == Bayonet_TIM_CH3)
				pin = 9;
		}
	}
	else if(TIMx == TIM5)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM5);
		if(Mode != Bayonet_TIM_MODE_INT)
		{
			port = GPIOA;
			if(CHx == Bayonet_TIM_CH0)
				pin = 0;
			else if(CHx == Bayonet_TIM_CH1)
				pin = 1;
			else if(CHx == Bayonet_TIM_CH2)
				pin = 2;
			else if(CHx == Bayonet_TIM_CH3)
				pin = 3;
		}
	}
	else if(TIMx == TIM6)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM6);
		if(Mode != Bayonet_TIM_MODE_INT)
			AssertFailed("Timer mode error. ", __FILE__, __LINE__);
		Bayonet_RCC_Active(Bayonet_RCC_TIM6);
	}
	else if(TIMx == TIM7)
	{
		freq = Bayonet_RCC_Active(Bayonet_RCC_TIM7);
		if(Mode != Bayonet_TIM_MODE_INT)
			AssertFailed("Timer mode error. ", __FILE__, __LINE__);
		Bayonet_RCC_Active(Bayonet_RCC_TIM7);
	}
	else if(TIMx == TIM8)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM8);
	}
	else
		AssertFailed("TIM not exist.", __FILE__, __LINE__);
	
	if(Mode == Bayonet_TIM_MODE_ICAP)
		Bayonet_GPIO_Init(port, pin, Bayonet_GPIO_MODE_GPIU);
	else if(Mode == Bayonet_TIM_MODE_INT)
	{//dummy operation. 
	}
	else if(Mode == Bayonet_TIM_MODE_PWM)
		Bayonet_GPIO_Init(port, pin, Bayonet_GPIO_MODE_GPOAPP); 
	else
		AssertFailed("TIM mode not exist. ", __FILE__, __LINE__);
	
	return freq;
}

//TIM2-7
uint8_t Bayonet_TIM_INT_Init(TIM_TypeDef *TIMx, uint32_t Prescaler, uint32_t ReloadValue, uint8_t PrePriority, uint8_t SubPriority)
{
	Bayonet_TIM_CLOCK_IO_Init(TIMx, Bayonet_TIM_CH0, Bayonet_TIM_MODE_INT); //Dummy channel. 
	
	TIMx->PSC = Prescaler;
	TIMx->ARR = ReloadValue;
	TIMx->DIER |= TIM_DIER_UIE;
	TIMx->CR1 |= TIM_CR1_CEN;
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_TIM(TIMx, Bayonet_TIM_MODE_INT), PrePriority, SubPriority);
	
	return 0;
}

uint8_t Bayonet_TIM_PWM_Channel_Init(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, uint32_t cycleTime)
{
	RCC_ClocksTypeDef Clock_Structure;
	Bayonet_RCC_GetClocksFreq(&Clock_Structure);
	Bayonet_TIM_CLOCK_IO_Init(TIMx, CHx, Bayonet_TIM_MODE_PWM);
	
	TIMx->PSC = Clock_Structure.SYSCLK_Frequency / 1000000 - 1;		//Prescale time count to 1 microsecond. Timer counts SYS_CLOCK. 
	if(cycleTime < 1000000)
		TIMx->ARR = cycleTime - 1;																		//How many micro seconds per cycle. 
	else
		AssertFailed("Cycle time overflow. ", __FILE__, __LINE__);
	
	if(CHx == Bayonet_TIM_CH0)
	{
		TIMx->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;	//PWM 1 mode. 
		TIMx->CCER  |= TIM_CCER_CC1E;
	}
	else if(CHx == Bayonet_TIM_CH1)
	{
		TIMx->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
		TIMx->CCER  |= TIM_CCER_CC2E;
	}
	else if(CHx == Bayonet_TIM_CH2)
	{
		TIMx->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
		TIMx->CCER  |= TIM_CCER_CC3E;
	}
	else if(CHx == Bayonet_TIM_CH3)
	{
		TIMx->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
		TIMx->CCER  |= TIM_CCER_CC4E;
	}
	else
		AssertFailed("CHx does not exist. ", __FILE__, __LINE__);
	
	TIMx->CR1 |= TIM_CR1_ARPE;
	TIMx->CR1 |= TIM_CR1_CEN;
	
	//TIMx
	
	return 0;
}
