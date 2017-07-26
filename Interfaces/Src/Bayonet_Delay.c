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
	
#include "Bayonet_Delay.h"
#include "Bayonet_UART.h"
#include "Bayonet_RCC.h"
#include <stdbool.h>

static uint8_t  fac_us=0;
static uint16_t fac_ms=0;

bool delayIsInit = false;

/**
  * @brief  Initializing systick for percise delay. 
  * @param  SYSCLK: highest clock frequency in your controller. 
  * @retval None
  */
void Bayonet_Delay_Init(void)
{
	RCC_ClocksTypeDef RCC_ClocksStructure;
	Bayonet_RCC_GetClocksFreq(&RCC_ClocksStructure);
	SysTick->CTRL &=~ SysTick_CTRL_CLKSOURCE;	//External clock. 
	fac_us = (RCC_ClocksStructure.HCLK_Frequency / 1000000) >> 3;			//Note: the default systick clock source is SYSCLK / 8. 
	fac_ms = (uint16_t)fac_us * 1000;
	delayIsInit = true;
}

/**
  * @brief  Delay nms milliseconds. 
  * @param  nms: how many milliseconds to delay. 
  * @retval None
  */
void Bayonet_Delay_Ms(uint16_t nms)
{
	uint32_t load = 0;
	uint32_t temp;
#ifdef Bayonet_Assert
	if(delayIsInit == false)
		AssertFailed("Delay module not initialized. Function Bayonet_Delay_Us", __FILE__, __LINE__); 
#endif
	while(nms)
	{
		if(nms > 1864)
		{
			load = 1864;
			nms -= 1864;
		}
		else
		{
			load = nms;
			nms = 0;
		}
		SysTick->LOAD = (uint32_t)load * fac_ms;
		SysTick->VAL = 0x00;
		SysTick->CTRL = SysTick_CTRL_ENABLE;
		do
		{
			temp = SysTick->CTRL; //CTRL may change after every cycle, put it in a buffer. 
		}
		while(temp&SysTick_CTRL_ENABLE && !(temp&SysTick_CTRL_COUNTFLAG));
		SysTick->CTRL=0x00;
		SysTick->VAL =0X00; 
	}
}   
	    								   
/**
  * @brief  Delay nus microseconds. 
  * @param  nms: how many microseconds to delay. 
  * @retval None
  */
void Bayonet_Delay_Us(uint16_t nus)
{
	uint32_t load = 0, temp = 0;
#ifdef Bayonet_Assert
	if(delayIsInit == false)
		AssertFailed("Delay module not initialized. Function Bayonet_Delay_Us()", __FILE__, __LINE__); 
#endif
	while(nus)
	{
		if(nus > 1864)
		{
			load = 1864;
			nus -= 1864;
		}
		else
		{
			load = nus;
			nus = 0;
		}
		SysTick->LOAD = load * fac_us;
		SysTick->VAL = 0x00;
		SysTick->CTRL = SysTick_CTRL_ENABLE;
		do
		{
			temp = SysTick->CTRL;
		}
		while(temp&SysTick_CTRL_ENABLE && !(temp&SysTick_CTRL_COUNTFLAG));
		SysTick->CTRL=0x00;
		SysTick->VAL =0X00;
	}
}
