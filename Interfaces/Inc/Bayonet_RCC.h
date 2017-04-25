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
	
#ifndef __Bayonet_RCC_H
#define __Bayonet_RCC_H

#include "stm32f10x.h"

#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_SW_Mask              ((uint32_t)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Reset_Mask    ((uint32_t)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)

typedef struct
{
  uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
  uint32_t PCLK1_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
  uint32_t PCLK2_Frequency;   /*!< returns PCLK2 clock frequency expressed in Hz */
  uint32_t ADCCLK_Frequency;  /*!< returns ADCCLK clock frequency expressed in Hz */
}RCC_ClocksTypeDef;

typedef enum{
	//APB2 Periph.
	Bayonet_RCC_AFIO, 			
	Bayonet_RCC_GPIOA,			
	Bayonet_RCC_GPIOB,			
	Bayonet_RCC_GPIOC,			
	Bayonet_RCC_GPIOD,			
	Bayonet_RCC_GPIOE,			
	Bayonet_RCC_ADC1,			
	Bayonet_RCC_ADC2,			
	Bayonet_RCC_TIM1,			
	Bayonet_RCC_SPI1,		
	Bayonet_RCC_UART1,			
	Bayonet_RCC_TIM8,			

	//AHB Periph.
	Bayonet_RCC_DMA1,			
	Bayonet_RCC_DMA2,			
	Bayonet_RCC_SRAM,			
	Bayonet_RCC_FLITF,		
	Bayonet_RCC_CRC,				
	//Bayonet_RCC_OTGFS			
	//Bayonet_RCC_ETHMAC		
	//Bayonet_RCC_ETHMACTX 	
	//Bayonet_RCC_ETHMACRX 	

	//APB1 Periph.
	Bayonet_RCC_TIM2,			
	Bayonet_RCC_TIM3,			
	Bayonet_RCC_TIM4,			
	Bayonet_RCC_TIM5,			
	Bayonet_RCC_TIM6,			
	Bayonet_RCC_TIM7,			
	Bayonet_RCC_WWDG,		
	Bayonet_RCC_SPI2,			
	Bayonet_RCC_SPI3,		
	Bayonet_RCC_UART2,			
	Bayonet_RCC_UART3,			
	Bayonet_RCC_UART4,			
	Bayonet_RCC_UART5,			
	Bayonet_RCC_I2C1,			
	Bayonet_RCC_I2C2,			
	Bayonet_RCC_CAN1,			
	//Bayonet_RCC_CAN2			
	Bayonet_RCC_BKP,				
	Bayonet_RCC_PWR,				
	Bayonet_RCC_DAC			
}Bayonet_RCC;

void Bayonet_RCC_Active(Bayonet_RCC device);
void Bayonet_RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

#endif
