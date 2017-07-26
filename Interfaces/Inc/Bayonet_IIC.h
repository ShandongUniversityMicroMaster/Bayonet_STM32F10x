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
	
#ifndef __BAYONET_IIC_H
#define __BAYONET_IIC_H

#include "stm32f10x.h"

typedef struct{
	uint8_t deviceID; 
	
	GPIO_TypeDef *SDA_Port;
	uint8_t SDA_Pin;
	GPIO_TypeDef *SCL_Port;
	uint8_t SCL_Pin;
}Bayonet_IIC_Device;

Bayonet_IIC_Device Bayonet_IIC_Init(GPIO_TypeDef *SDA_Port, uint8_t SDA_Pin, GPIO_TypeDef *SCL_Port, uint8_t SCL_Pin);
uint8_t Bayonet_IIC_ReadBytes(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t Bayonet_IIC_WriteBytes(Bayonet_IIC_Device device, uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);
uint8_t Bayonet_IIC_WriteBit(Bayonet_IIC_Device device, uint8_t dev, uint8_t reg, uint8_t bitNum, uint8_t data);
uint8_t Bayonet_IIC_WriteBits(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t data);

#endif
