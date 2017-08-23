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
	
#include "Bayonet_NVIC.h"
#include "Bayonet_UART.h"

Bayonet_NVIC_PriorityGroup Bayonet_NVIC_groupNumber = Bayonet_NVIC_PriorityGroup_None;

/**
  * @brief  Translate group number to index, 1, 2, 4, 8, 16. 
  * @param  NVIC_PriorityGroup: such as the name. 
  * @retval None
  */
uint8_t Bayonet_NVIC_GetGroupIndex(Bayonet_NVIC_PriorityGroup group)
{
	if(group == Bayonet_NVIC_PriorityGroup_0)
		return 1;
	else
		return (4 - ((group >> 8) - 3));
}

/**
  * @brief  Configures priority group of NVIC. 
  * @param  NVIC_PriorityGroup: such as the name. 
  * @retval None
  */
void Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup NVIC_PriorityGroup)
{
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
	Bayonet_NVIC_groupNumber = NVIC_PriorityGroup;
}

/**
  * @brief  Mapping ADC peripheral and IRQ channel. 
  * @param  ADCx: The ADC device needed to map.
  * @retval the IRQ channel of the ADC device. 
  */
uint8_t Bayonet_NVIC_GetIRQChannel_ADC(ADC_TypeDef* ADCx)
{
	if(ADCx == ADC1)
		return ADC1_2_IRQn;
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
	else if(ADCx == ADC2)
		return ADC1_2_IRQn;
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(ADCx == ADC3)
		return ADC3_IRQn;
#endif
	else
		AssertFailed("ADC device does not exist in this device. ", __FILE__, __LINE__);
	
	return 1;
}

/**
  * @brief  Mapping Timer peripheral and IRQ channel. 
  * @param  TIMx: Timer needed to map.
  * @retval the IRQ channel of the Timer device. 
  */
uint8_t Bayonet_NVIC_GetIRQChannel_TIM(TIM_TypeDef* TIMx, Bayonet_TIM_MODE mode)
{
	if(TIMx == TIM1)
	{
		if(mode == Bayonet_TIM_MODE_INT)
			return TIM1_UP_IRQn;
	}
	else if(TIMx == TIM2)
		return TIM2_IRQn;
	else if(TIMx == TIM3)
		return TIM3_IRQn;
	else if(TIMx == TIM4)
		return TIM4_IRQn;
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
	else if(TIMx == TIM5)
		return TIM5_IRQn;
	else if(TIMx == TIM6)
		return TIM6_IRQn;
	else if(TIMx == TIM7)
		return TIM7_IRQn;
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(TIMx == TIM8)
	{
		if(mode == Bayonet_TIM_MODE_INT)
			return TIM8_UP_IRQn;
	}
#endif
	
	return 1;
}

/**
  * @brief  Mapping DMA peripheral and IRQ channel. 
  * @param  CHx: DMA channel needed to map.
  * @retval the IRQ channel of the DMA device. 
  */
uint8_t Bayonet_NVIC_GetIRQChannel_DMA(DMA_Channel_TypeDef* CHx)
{
	if(CHx == DMA1_Channel1)
		return DMA1_Channel1_IRQn;
	else if(CHx == DMA1_Channel2)
		return DMA1_Channel2_IRQn;
	else if(CHx == DMA1_Channel3)
		return DMA1_Channel3_IRQn;
	else if(CHx == DMA1_Channel4)
		return DMA1_Channel4_IRQn;
	else if(CHx == DMA1_Channel5)
		return DMA1_Channel5_IRQn;
	else if(CHx == DMA1_Channel6)
		return DMA1_Channel6_IRQn;
	else if(CHx == DMA1_Channel7)
		return DMA1_Channel7_IRQn;
#if defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
	else if(CHx == DMA2_Channel1)
		return DMA2_Channel1_IRQn;
	else if(CHx == DMA2_Channel2)
		return DMA2_Channel2_IRQn;
	else if(CHx == DMA2_Channel3)
		return DMA2_Channel3_IRQn;
#endif
#if defined(STM32F10X_HD) || defined(STM32F10X_XL)
	else if(CHx == DMA2_Channel4)
		return DMA2_Channel4_5_IRQn;
	else if(CHx == DMA2_Channel5)
		return DMA2_Channel4_5_IRQn;
#elif defined(STM32F10X_CL)
	else if(CHx == DMA2_Channel4)
		return DMA2_Channel4_IRQn;
	else if(CHx == DMA2_Channel5)
		return DMA2_Channel4_IRQn;
#endif
	else
		AssertFailed("DMA channel not exist.", __FILE__, __LINE__);
	
	return 1;
}

/**
  * @brief  Mapping SPI peripheral and IRQ channel. 
  * @param  SPIx: SPI device needed to map.
  * @retval the IRQ channel of the SPI device. 
  */
uint8_t Bayonet_NVIC_GetIRQChannel_SPI(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
		return SPI1_IRQn;
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
	else if(SPIx == SPI2)
		return SPI2_IRQn;
#endif
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
	else if(SPIx == SPI3)
		return SPI3_IRQn;
#endif
	
	return 1;
}

/**
  * @brief  Mapping EXTI peripheral and IRQ channel. 
  * @param  Pinx: GPIO pin needed to map.
  * @retval the IRQ channel of the specific pin. 
  */
uint8_t Bayonet_NVIC_GetIRQChannel_EXTI(uint8_t Pinx)
{
	if(Pinx < 5)
	{
		switch(Pinx)
		{
			case 0:
				return EXTI0_IRQn;
			case 1:
				return EXTI1_IRQn;
			case 2:
				return EXTI2_IRQn;
			case 3:
				return EXTI3_IRQn;
			case 4:
				return EXTI4_IRQn;
		}
	}
	else if(Pinx < 10)
		return EXTI9_5_IRQn;
	else
		return EXTI15_10_IRQn;
	
	return 0;
}

//This table was copied from ST standard peripheral lib, for non-commercial usage. 
/**
@code  
 The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
@endcode
*/

/**
  * @brief  Initializing the NVIC IRQ channel of the specific peripheral.
  * @param  IRQChannel: the corresponding IRQ channel of the peripheral.
  * @param  PrePriority: prepriority of the channel.
  * @param  SubPriority: subpriority of the channel.
  * @retval None
  */
void Bayonet_NVIC_Init(uint8_t IRQChannel, uint8_t PrePriority, uint8_t SubPriority)
{
	uint8_t tempMax;
	uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
	if(Bayonet_NVIC_groupNumber != Bayonet_NVIC_PriorityGroup_None)
	{
		tempMax = (1 << Bayonet_NVIC_GetGroupIndex(Bayonet_NVIC_groupNumber));
		if(PrePriority >= tempMax)
			AssertFailed("prePriority exceeds. ", __FILE__, __LINE__);
		tempMax = (1 << (4 - Bayonet_NVIC_GetGroupIndex(Bayonet_NVIC_groupNumber)));
		if(SubPriority >= tempMax)
			AssertFailed("subPriority exceeds. ", __FILE__, __LINE__);
		
		/* Compute the Corresponding IRQ Priority --------------------------------*/    
		tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
		tmppre = (0x4 - tmppriority);
		tmpsub = tmpsub >> tmppriority;

		tmppriority = (uint32_t)PrePriority << tmppre;
		tmppriority |=  SubPriority & tmpsub;
		tmppriority = tmppriority << 0x04;
				
		NVIC->IP[IRQChannel] = tmppriority;
		
		/* Enable the Selected IRQ Channels --------------------------------------*/
		NVIC->ISER[IRQChannel >> 0x05] =
			(uint32_t)0x01 << (IRQChannel & (uint8_t)0x1F);
	}
	else
		AssertFailed("NVIC not grouped.", __FILE__, __LINE__); //only show "N", whyyyyyyyyyyyyyyyy?
	//May need to assert if the prepriority and subpriority is leagal. 
}

/**
  * @brief  Setting interrput vector table, usually used in IAP. 
  * @param  NVIC_VectTab: NVIC_VectTab address.
  * @param  Offset: address starts at NVIC_Vectab + Offset.
  * @retval None
  */
void Bayonet_NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);
}
