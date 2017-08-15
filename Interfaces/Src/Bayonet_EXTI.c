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

#include "Bayonet_EXTI.h"
#include "Bayonet_UART.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_RCC.h"
#include "Bayonet_GPIO.h"

bool Bayonet_EXIT_isInit[16] = {false};

/**
  * @brief  Initializing clocks and io the specific EXTI line to use. 
	* @param  GPIOx: the port of the pin to initialized.
	* @param  Pinx: the index of the pin to initialized.
  * @retval 0
  */
int Bayonet_EXTI_CLOCK_IO_Init(GPIO_TypeDef* GPIOx, uint8_t Pinx)
{
	Bayonet_RCC_Active(Bayonet_RCC_AFIO);
	
	Bayonet_GPIO_Init(GPIOx, Pinx, Bayonet_GPIO_MODE_GPIU);
	
	return 0;
}

/**
  * @brief  Initializing a EXTI line to a GPIO pin as an exernal interrupt event. 
	* @param  GPIOx: the port of the pin to initialized.
	* @param  Pinx: the index of the pin to initialized.
  * @param  PrePriority: prepriority of the channel.
  * @param  SubPriority: subpriority of the channel.
  * @retval 0
  */
int Bayonet_EXTI_Interrupt_Init(GPIO_TypeDef* GPIOx, uint8_t Pinx, Bayonet_EXTI_TRIGGER trigger, uint8_t PrePriority, uint8_t SubPriority)
{
	if(Pinx > 15)
		AssertFailed("The index of pin exceeded. ", __FILE__, __LINE__);
	
	Bayonet_EXTI_CLOCK_IO_Init(GPIOx, Pinx);
	
	EXTI->IMR |= 1 << Pinx;
	
	if(trigger == Bayonet_EXTI_TRIGGER_RISING)
		EXTI->RTSR |= 1 << Pinx;
	else if(trigger == Bayonet_EXTI_TRIGGER_FALLING)
		EXTI->FTSR |= 1 << Pinx;
	else if(trigger == Bayonet_EXTI_TRIGGER_BOTH)
	{
		EXTI->RTSR |= 1 << Pinx;
		EXTI->FTSR |= 1 << Pinx;
	}
	else
		AssertFailed("The selected trigger is not found...", __FILE__, __LINE__);
	
	if(Bayonet_EXIT_isInit[Pinx] == false)
	{
		AFIO->EXTICR[Pinx / 4] = Bayonet_GPIO_GetPortIndex(GPIOx) << ((Pinx % 4) * 4);
		Bayonet_EXIT_isInit[Pinx] = true;
	}
	else
		AssertFailed("EXTI Line Configured, can not override...", __FILE__, __LINE__);
		
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_EXTI(Pinx), PrePriority, SubPriority);
	
	return 0;
}

/*****************************************************
	*
	*		Interrupt Request Handler should be like below: 
	*
	*		<Line Index>  -->  your EXTI line index. 
	*
	****************************************************
	*
	*	for EXTI line 0-4:
	*
	*	void EXTI<Line Index>_IRQHandler()
	*	{
	*		if(EXTI->PR & (1 << <Line Index>))
	*		{
	*			//Your code here. 
	*			EXTI->PR |= 1 << <Line Index>;
	*		}
	*	}
	*
	*	for EXTI line 5-9:
	*
	*	void EXTI9_5_IRQHanlder()
	*	{
	*		if(EXTI->PR & (1 << <Line Index>))
	*		{
	*			//Your code here. 
	*			EXTI->PR |= 1 << <Line Index>;
	*		}
	*	}
	*
	*	for EXTI line 10-15:
	*
	*	void EXTI15_10_IRQHandler()
	*	{
	*		if(EXTI->PR & (1 << <Line Index>))
	*		{
	*			//Your code here. 
	*			EXTI->PR |= 1 << <Line Index>;
	*		}
	*	}
	*
******************************************************/
