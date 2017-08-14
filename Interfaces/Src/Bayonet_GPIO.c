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
	
#include "Bayonet_GPIO.h"
#include "Bayonet_UART.h"
#include <math.h>

//All GPIO port mode will be stored in here. 
uint8_t bayonetGPIOPortMode[6][16];

/**
  * @brief  Translating port name to number. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @retval Port index. 
  */
uint8_t Bayonet_GPIO_GetPortIndex(GPIO_TypeDef *GPIOx)
{
	if(GPIOx == GPIOA)
		return 0;
	else if(GPIOx == GPIOB)
		return 1;
	else if(GPIOx == GPIOC)
		return 2;
	else if(GPIOx == GPIOD)
		return 3;
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
	else if(GPIOx == GPIOE)
		return 4;
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(GPIOx == GPIOF)
		return 5;
	else if(GPIOx == GPIOG)
		return 6;
#endif
	else
		AssertFailed("Port not exist. File:%s, Line:%d ", __FILE__, __LINE__);
	
	return 255;
}

/**
  * @brief  Checking if the port is in right mode. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel.
  * @retval None
  */
void Bayonet_AssertInputPort(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	uint8_t mode = bayonetGPIOPortMode[Bayonet_GPIO_GetPortIndex(GPIOx)][Pinx];
	if(mode > 3)
		AssertFailed("This IO port is not in input mode. ", __FILE__, __LINE__);
}

/**
  * @brief  Checking if the port is in right mode. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel.
  * @retval None
  */
void Bayonet_AssertOutputPort(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
		uint8_t mode = bayonetGPIOPortMode[Bayonet_GPIO_GetPortIndex(GPIOx)][Pinx];
		if(mode < 4)
			AssertFailed("This IO port is not in output mode. ", __FILE__, __LINE__); 
}

/**
  * @brief  Configuring GPIO IO port with desired mode. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel.
  * @param  Mode: GPIO mode, defined in Bayonet_GPIO_Mode enumeration. 
  * @retval None
  */
void Bayonet_GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t Pinx, Bayonet_GPIO_Mode Mode)
{
	uint8_t config = 0x00;
	if(GPIOx == GPIOA)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if(GPIOx == GPIOB)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if(GPIOx == GPIOC)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else if(GPIOx == GPIOD)
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	else if(GPIOx == GPIOE)
		RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
	else
		AssertFailed("Port not exist. ", __FILE__, __LINE__);
	
	if(Mode == Bayonet_GPIO_MODE_GPIA)
		config = 0x00;
	else if(Mode == Bayonet_GPIO_MODE_GPIF)
		config = 0x04;
	else if(Mode == Bayonet_GPIO_MODE_GPIU)
	{
		config = 0x08;
		GPIOx->ODR |= (1 << Pinx);
	}
	else if(Mode == Bayonet_GPIO_MODE_GPID)
	{
		config = 0x08;
		GPIOx->ODR &=~ (1 << Pinx);
	}
	else if(Mode == Bayonet_GPIO_MODE_GPOGPP)
		config = 0x03;
	else if(Mode == Bayonet_GPIO_MODE_GPOGOD)
		config = 0x07;
	else if(Mode == Bayonet_GPIO_MODE_GPOAPP)
		config = 0x0B;
	else if(Mode == Bayonet_GPIO_MODE_GPOAOD)
		config = 0x0F;
	else
		AssertFailed("Mode not exist. ", __FILE__, __LINE__);
	
	if(Pinx < 8)
	{
		GPIOx->CRL &=~ (0x0f << (Pinx * 4));
		GPIOx->CRL |=  (config << (Pinx * 4));
	}
	else
	{
		GPIOx->CRH &=~ (0x0f << ((Pinx-8) * 4));
		GPIOx->CRH |=  (config << ((Pinx-8) * 4));
	}
	#ifdef Bayonet_Assert
		bayonetGPIOPortMode[Bayonet_GPIO_GetPortIndex(GPIOx)][Pinx] = Mode;
	#endif
}

/**
  * @brief  Get the voltage level of specific port. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel. 
  * @retval 0 or 1, representing the voltage level of the port. 
  */
bool Bayonet_GPIO_Get(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
#ifdef Bayonet_Assert
	Bayonet_AssertInputPort(GPIOx, Pinx);
#endif
	if((GPIOx->IDR & (1 << Pinx)) != 0)
		return true;
	else
		return false;
}

/**
  * @brief  Set the output voltage level of specific port. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel. 
  * @param  state: state to set. 
  * @retval None. 
  */
void Bayonet_GPIO_Set(GPIO_TypeDef *GPIOx, uint8_t Pinx, bool state)
{
	#ifdef Bayonet_Assert
		Bayonet_AssertOutputPort(GPIOx, Pinx);
	#endif
	if(state)
		GPIOx->ODR |= (0x1 << Pinx);
	else
		GPIOx->ODR &=~ (0x1 << Pinx);
}

/**
  * @brief  Turn the output voltage level of specific port. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel. 
  * @retval None. 
  */
void Bayonet_GPIO_Turn(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	#ifdef Bayonet_Assert
		Bayonet_AssertOutputPort(GPIOx, Pinx);
	#endif
	if(GPIOx->ODR & (0x1 << Pinx))
		Bayonet_GPIO_Set(GPIOx, Pinx, 0);
	else
		Bayonet_GPIO_Set(GPIOx, Pinx, 1);
}
