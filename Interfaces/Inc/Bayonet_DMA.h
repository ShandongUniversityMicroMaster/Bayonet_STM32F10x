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
	
#ifndef __BAYONET_DMA_H
#define __BAYONET_DMA_H

#include "stm32f10x.h"

typedef enum{
	Bayonet_DMA_DataWidth_8bit,
	Bayonet_DMA_DataWidth_16bit,
	Bayonet_DMA_DataWidth_32bit
}Bayonet_DMA_DataWidth;

void Bayonet_DMA_P2M_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, Bayonet_DMA_DataWidth DataWidth, uint16_t DataLength);
void Bayonet_DMA_M2P_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, Bayonet_DMA_DataWidth DataWidth, uint16_t DataLength);
void Bayonet_DMA_M2M_Start(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t SourceAdress, uint32_t DestinationAdress, Bayonet_DMA_DataWidth SourceDataWidth, Bayonet_DMA_DataWidth DestinationDataWidth, uint16_t DataLength);


#endif
