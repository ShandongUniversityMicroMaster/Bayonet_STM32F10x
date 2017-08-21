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

#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)	

#include "Bayonet_DAC.h"
#include "Bayonet_UART.h"
#include "Bayonet_RCC.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_TIM.h"

bool Bayonet_DAC_isInit[2] = {false};

/**
  * @brief  Initializing the basic configuration of specific channel. 
  * @param  channeln: DAC channel to initialize. 
  * @param  initValue: Initial value to use. 
  * @retval None. 
  */
void Bayonet_DAC_Clock_IO_Init(Bayonet_DAC_CHANNEL channeln, uint16_t initValue)
{
	if(channeln > 1)
		AssertFailed("DAC channel not exist...", __FILE__, __LINE__);
	
	Bayonet_RCC_Active(Bayonet_RCC_DAC);
	
	if(channeln == Bayonet_DAC_CHANNEL1)
		Bayonet_GPIO_Init(GPIOA, 4, Bayonet_GPIO_MODE_GPIA);
	else
		Bayonet_GPIO_Init(GPIOA, 5, Bayonet_GPIO_MODE_GPIA);
	
	DAC->CR |= (DAC_CR_EN1 | DAC_CR_BOFF1) << (channeln << 4);
	
	if(channeln == Bayonet_DAC_CHANNEL1)
		DAC->DHR12R1 = initValue;
	else
		DAC->DHR12R2 = initValue;
	
	Bayonet_DAC_isInit[channeln] = true;
}

/**
  * @brief  Initializing specific DAC channel in general mode. 
  * @param  channeln: DAC channel to initialize. 
  * @param  initValue: Initial value to use. 
  * @retval None. 
  */
void Bayonet_DAC_Init_WithoutWave(Bayonet_DAC_CHANNEL channeln, uint16_t initValue)
{
	Bayonet_DAC_Clock_IO_Init(channeln, initValue);
}

/**
  * @brief  Initializing specific DAC channel in noise generation mode. 
  * @param  channeln: DAC channel to initialize. 
  * @param  offset: Wave offset. 
  * @param  amplitude: Wave anplitude. 
  * @param  trigger: trigger to make output change. 
  * @retval None. 
  */
void Bayonet_DAC_Init_NoiseGeneration(Bayonet_DAC_CHANNEL channeln, uint16_t offset, Bayonet_DAC_AMPLITUDE amplitude, Bayonet_DAC_TRIGGER trigger)
{
	Bayonet_DAC_Clock_IO_Init(channeln, offset);
	DAC->CR |= (DAC_CR_WAVE1_0 | DAC_CR_TEN1 | (trigger << 3) | (amplitude << 8)) << (channeln << 4);
}

/**
  * @brief  Initializing specific DAC channel in triangle generation mode, this is much like the configuration in noise generation mode. 
  * @param  channeln: DAC channel to initialize. 
  * @param  offset: Wave offset. 
  * @param  amplitude: Wave anplitude. 
  * @param  trigger: trigger to make output change. 
  * @retval None. 
  */
void Bayonet_DAC_Init_TriangleGeneration(Bayonet_DAC_CHANNEL channeln, uint16_t offset, Bayonet_DAC_AMPLITUDE amplitude, Bayonet_DAC_TRIGGER trigger)
{
	Bayonet_DAC_Clock_IO_Init(channeln, offset);
	DAC->CR |= (DAC_CR_WAVE1_1 | DAC_CR_TEN1 | (trigger << 3) | (amplitude << 8)) << (channeln << 4);
}

/**
  * @brief  Setting DAC output value or offset. 
  * @param  channeln: DAC channel to initialize. 
  * @param  value: Output value for general mode, base offset for wave generation mode. 
  * @retval None. 
  */
void Bayonet_DAC_SetOuputLevel(Bayonet_DAC_CHANNEL channeln, uint16_t value)
{
#ifdef Bayonet_Assert
	if(Bayonet_DAC_isInit[channeln] == false)
		AssertFailed("This channel has not been initialized. ", __FILE__, __LINE__);
	
	if(value > 4095)
		AssertFailed("DAC expected value exceeded. ", __FILE__, __LINE__);
#endif
	if(channeln == Bayonet_DAC_CHANNEL1)
		DAC->DHR12R1 = value;
	else
		DAC->DHR12R2 = value;
}

#endif
