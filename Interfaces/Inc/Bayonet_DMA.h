/**
  ******************************************************************************
  * @file    Bayonet_DMA.h
  * @author  Song Qiang
  * @version V1.0.0
  * @date    10-March-2017
  * @brief   Function Prototypes of DMA. 
  *
  ******************************************************************************
  */
	
#ifndef __BAYONET_DMA_H
#define __BAYONET_DMA_H

#include "stm32f10x.h"

#define Bayonet_DMA_DataWidth_8bit		0x00000000
#define Bayonet_DMA_DataWidth_16bit		0x00000001
#define Bayonet_DMA_DataWidth_32bit		0x00000002

void Bayonet_DMA_P2M_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, uint8_t DataWidth, uint16_t DataLength);
void Bayonet_DMA_M2P_Init(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t PeripheralAdress, uint32_t MemoryAdress, uint8_t DataWidth, uint16_t DataLength);
void Bayonet_DMA_M2M_Start(DMA_TypeDef *DMAx, DMA_Channel_TypeDef *CHx, uint32_t SourceAdress, uint32_t DestinationAdress, uint8_t SourceDataWidth,uint8_t DestinationDataWidth, uint16_t DataLength);


#endif
