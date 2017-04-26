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
	
#include "Bayonet_DMA.h"
#include "Bayonet_RCC.h"
#include "Bayonet_Delay.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_UART.h"

/**
  * @brief  Configures rcc clock and IO port of specific DMA channel.
  * @param  DMAx: where x can be (1..3) to select the DMA peripheral.
  * @param  CHx: specific DMA channel.
  * @param  PeripheralAdress: adress of peripheral.
  * @param  MemoryAdress: adress of memory.
  * @param  DataLength: time that DMA transfers.
  * @retval None
  */
void Bayonet_DMA_CLOCK_IO_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, uint16_t DataLength)
{
	if(DMAx == DMA1)
	{
		Bayonet_RCC_Active(Bayonet_RCC_DMA1);
	}
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL) || defined  (STM32F10X_HD_VL) || defined  (STM32F10X_XL)	
	else
	{
		Bayonet_RCC_Active(Bayonet_RCC_DMA2);
	}
#endif
	delay_ms(5);
	
	CHx->CPAR = PeripheralAdress;
	CHx->CMAR = MemoryAdress;
	//dataLength = DataLength;
	CHx->CNDTR = DataLength;
}

/**
  * @brief  Configures data width of peripheral and memory.
  * @param  CHx: specific DMA channel.
  * @param  PeripheralDataWidth: data width of peripheral.
  * @param  MemoryDataWidth: data width of memory.
  * @retval None
  */
void Bayonet_DMA_SetDataWidth(DMA_Channel_TypeDef *CHx, uint8_t PeripheralDataWidth, uint8_t MemoryDataWidth)
{
	if(PeripheralDataWidth == Bayonet_DMA_DataWidth_8bit)
		CHx->CCR &=~ DMA_CCR1_PSIZE;
	else if(PeripheralDataWidth == Bayonet_DMA_DataWidth_16bit)
		CHx->CCR |= DMA_CCR1_PSIZE_0;
	else if(PeripheralDataWidth == Bayonet_DMA_DataWidth_32bit)
		CHx->CCR |= DMA_CCR1_PSIZE_1;
	else
		AssertFailed("DMA peripheral data width error.", __FILE__, __LINE__);
	
	if(MemoryDataWidth == Bayonet_DMA_DataWidth_8bit)
		CHx->CCR &=~ DMA_CCR1_MSIZE;
	else if(MemoryDataWidth == Bayonet_DMA_DataWidth_16bit)
		CHx->CCR |= DMA_CCR1_MSIZE_0;
	else if(MemoryDataWidth == Bayonet_DMA_DataWidth_32bit)
		CHx->CCR |= DMA_CCR1_MSIZE_1;
	else
		AssertFailed("DMA memory data width error.", __FILE__, __LINE__);
}

/**
  * @brief  Configures rcc clock and IO port of specific DMA channel.
  * @param  DMAx: where x can be (1..3) to select the DMA peripheral.
  * @param  CHx: specific DMA channel.
  * @param  PeripheralAdress: adress of peripheral.
  * @param  MemoryAdress: adress of memory.
  * @param  DataWidth: data width.
  * @param  DataLength: time that DMA transfers.
  * @retval None
  */
void Bayonet_DMA_P2M_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, uint8_t DataWidth, uint16_t DataLength)
{
	Bayonet_DMA_CLOCK_IO_Init(DMAx, CHx, PeripheralAdress, MemoryAdress, DataLength);
	CHx->CCR &=~ DMA_CCR1_DIR;			//Read from peripheral.
	CHx->CCR |= DMA_CCR1_CIRC;
	CHx->CCR |= DMA_CCR1_MINC;
	CHx->CCR &=~ DMA_CCR1_PINC;
	Bayonet_DMA_SetDataWidth(CHx, DataWidth, DataWidth);
	CHx->CCR |= DMA_CCR1_TCIE;
	CHx->CCR |= DMA_CCR1_PL;				//Very high priority.
	CHx->CCR &=~ DMA_CCR1_MEM2MEM;
	
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_DMA(CHx), 1, 1);
	CHx->CCR |= DMA_CCR1_EN;
}

/**
  * @brief  Configures rcc clock and IO port of specific DMA channel.
  * @param  DMAx: where x can be (1..3) to select the DMA peripheral.
  * @param  CHx: specific DMA channel.
  * @param  PeripheralAdress: adress of peripheral.
  * @param  MemoryAdress: adress of memory.
  * @param  DataWidth: data width.
  * @param  DataLength: time that DMA transfers.
  * @retval None
  */
void Bayonet_DMA_M2P_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, uint8_t DataWidth, uint16_t DataLength)
{
	Bayonet_DMA_CLOCK_IO_Init(DMAx, CHx, PeripheralAdress, MemoryAdress, DataLength);
	CHx->CCR |= DMA_CCR1_DIR;			//Read from memory.
	CHx->CCR &=~ DMA_CCR1_CIRC;
	CHx->CCR |= DMA_CCR1_MINC;
	CHx->CCR &=~ DMA_CCR1_PINC;
	Bayonet_DMA_SetDataWidth(CHx, DataWidth, DataWidth);
	CHx->CCR |= DMA_CCR1_TCIE;
	CHx->CCR |= DMA_CCR1_PL;
	CHx->CCR &=~ DMA_CCR1_MEM2MEM;
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_DMA(CHx), 1, 1);
}

/**
  * @brief  Configures rcc clock and IO port of specific DMA channel.
  * @param  DMAx: where x can be (1..3) to select the DMA peripheral.
  * @param  CHx: specific DMA channel.
  * @param  SourceAdress: source adress of memory.
  * @param  MemoryAdress: destination adress of memory.
  * @param  SourceDataWidth: source memory data width.
  * @param  DestinayionDataWidth: destination memory data width.
  * @param  DataLength: time that DMA transfers.
  * @retval None
  */
void Bayonet_DMA_M2M_Start(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t SourceAdress, uint32_t DestinationAdress, uint8_t SourceDataWidth,uint8_t DestinationDataWidth, uint16_t DataLength)
{
	Bayonet_DMA_CLOCK_IO_Init(DMAx, CHx, SourceAdress, DestinationAdress, DataLength);
	CHx->CCR &=~ DMA_CCR1_DIR; //Read from peripheral, which in this case, is SourceAdress.
	CHx->CCR &=~ DMA_CCR1_CIRC;
	CHx->CCR |= DMA_CCR1_MINC;
	CHx->CCR |= DMA_CCR1_PINC;
	Bayonet_DMA_SetDataWidth(CHx, SourceDataWidth, DestinationDataWidth);
	CHx->CCR |= DMA_CCR1_TCIE;
	CHx->CCR |= DMA_CCR1_PL;
	CHx->CCR |= DMA_CCR1_MEM2MEM;
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_DMA(CHx), 1, 1);
	CHx->CCR |= DMA_CCR1_EN;
}

void Bayonet_DMA_Restart(DMA_Channel_TypeDef *CHx, uint16_t count)
{
	CHx->CCR &=~ DMA_CCR1_EN;
	CHx->CNDTR = count;
	CHx->CCR |=  DMA_CCR1_EN;
}
