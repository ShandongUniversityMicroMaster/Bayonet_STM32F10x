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
	
#ifndef __BAYONET_GPIO_H
#define __BAYONET_GPIO_H

#include "stm32f10x.h"
#include <stdbool.h>

typedef enum{
	Bayonet_GPIO_MODE_GPIA,
	Bayonet_GPIO_MODE_GPIF,
  Bayonet_GPIO_MODE_GPIU,
  Bayonet_GPIO_MODE_GPID, 
  Bayonet_GPIO_MODE_GPOGPP, 
  Bayonet_GPIO_MODE_GPOGOD, 
  Bayonet_GPIO_MODE_GPOAPP, 
  Bayonet_GPIO_MODE_GPOAOD
}Bayonet_GPIO_Mode;

uint8_t Bayonet_GPIO_GetPortIndex(GPIO_TypeDef *GPIOx);

void Bayonet_GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t Pinx, Bayonet_GPIO_Mode Mode);
bool Bayonet_GPIO_Get(GPIO_TypeDef *GPIOx, uint8_t Pinx);
void Bayonet_GPIO_Set(GPIO_TypeDef *GPIOx, uint8_t Pinx, bool state);
void Bayonet_GPIO_Turn(GPIO_TypeDef *GPIOx, uint8_t Pinx);

#endif
