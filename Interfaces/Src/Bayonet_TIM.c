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

/**
  * @brief  Configuring clocks and IO port for the specific timer channel. 
  * @param  TIMx: where x can be (1..14) to select timer. 
  * @param  CHx: where x can be (1..4) to select channel. 
  * @param  mode: timer working mode. 
  * @retval 0 for success. 
  */
uint32_t Bayonet_TIM_Clock_IO_Init(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, Bayonet_TIM_MODE Mode)
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
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
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
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(TIMx == TIM8)
	{
		Bayonet_RCC_Active(Bayonet_RCC_TIM8);
	}
#endif
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

/**
  * @brief  Initializing timer with interrupt mode. 
  * @param  TIMx: where x can be (1..14) to select timer. 
  * @param  microseconds: how many microseconds between two interrupts. 
  * @param  prePriority: PreemptionPriority. 
  * @param  subPriority: SubPriority. 
  * @retval 0 for success. 
  */
uint8_t Bayonet_TIM_Init_Interrupt(TIM_TypeDef *TIMx, uint32_t microseconds, uint8_t prePriority, uint8_t subPriority)
{
	RCC_ClocksTypeDef Clock_Structure;
	Bayonet_RCC_GetClocksFreq(&Clock_Structure);
	Bayonet_TIM_Clock_IO_Init(TIMx, Bayonet_TIM_CH0, Bayonet_TIM_MODE_INT); //Dummy channel. 
	
	TIMx->PSC = Clock_Structure.SYSCLK_Frequency / 1000000 - 1;		//Prescale time count to 1 microsecond. Timer counts SYS_CLOCK. 
	TIMx->ARR = microseconds;
	TIMx->DIER |= TIM_DIER_UIE;
	TIMx->CR1 |= TIM_CR1_CEN;
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_TIM(TIMx, Bayonet_TIM_MODE_INT), prePriority, subPriority);
	TIMx->CR2 |= TIM_CR2_MMS_1;
	
	return 0;
}

/**
  * @brief  Initializing specific channel with PWM mode. 
  * @param  TIMx: where x can be (1..14) to select timer. 
  * @param  CHx: where x can be (1..4) to select channel. 
  * @param  cycleTime: time of the PWM cycle, in microseconds. 
  * @retval 0 for success. 
  */
uint8_t Bayonet_TIM_Init_PWMChannel(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, uint32_t cycleTime)
{
	RCC_ClocksTypeDef Clock_Structure;
	uint32_t preScaler = 0;
	Bayonet_RCC_GetClocksFreq(&Clock_Structure);
	Bayonet_TIM_Clock_IO_Init(TIMx, CHx, Bayonet_TIM_MODE_PWM);
	
	if(cycleTime < 1000000)
	{
		if(cycleTime > 0xffff)		//If one cycle overflows 0xffff, using millisecond as time atom. 
		{
			preScaler = 1000;
			TIMx->ARR = cycleTime / 1000 - 1;															//How many milliseconds per cycle. 
		}
		else
		{
			preScaler = 1000000;
			TIMx->ARR = cycleTime - 1;																		//How many microseconds per cycle. 
		}
	}
	else
		AssertFailed("Cycle time overflow. ", __FILE__, __LINE__);
	
	if(TIMx == TIM1 || TIMx == TIM8)
		TIMx->PSC = Clock_Structure.PCLK2_Frequency / preScaler - 1;		//Prescale time count to 1 microsecond. Timer counts SYS_CLOCK. 
	else
		TIMx->PSC = Clock_Structure.PCLK1_Frequency / preScaler - 1;
	
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
	
	return 0;
}

/**
  * @brief  Reconfiguring duty cycle of the specific channel. 
  * @param  TIMx: where x can be (1..14) to select timer. 
  * @param  CHx: where x can be (1..4) to select channel. 
  * @param  dutyValue: time of the PWM cycle, in microseconds. 
  * @retval 0 for success. 
  */
uint8_t Bayonet_TIM_PWM_Duty(TIM_TypeDef *TIMx, Bayonet_TIM_CHANNEL CHx, uint16_t dutyTime)
{
	if(CHx == Bayonet_TIM_CH0)
		TIMx->CCR1 = dutyTime;
	else if(CHx == Bayonet_TIM_CH1)
		TIMx->CCR2 = dutyTime;
	else if(CHx == Bayonet_TIM_CH2)
		TIMx->CCR3 = dutyTime;
	else if(CHx == Bayonet_TIM_CH3)
		TIMx->CCR4 = dutyTime;
	else
		AssertFailed("Timer channel not exist..", __FILE__, __LINE__);
		
	return 0;
}
