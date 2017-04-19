#include "Bayonet_NVIC.h"
#include "Bayonet_UART.h"

uint8_t isGrouped = 0;

/**
  * @brief  Configures priority group of NVIC. 
  * @param  NVIC_PriorityGroup: such as the name. 
  * @retval None
  */
void Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup NVIC_PriorityGroup)
{
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
	isGrouped = 1;
}

/**
  * @brief  Mapping DMA peripheral and IRQ channel. 
  * @param  CHx: DMA channel needed to map.
  * @retval the IRQ channel of the DMA device. 
  */
uint8_t Bayonet_NVIC_GetIRQChannel_DMA(DMA_Channel_TypeDef *CHx)
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
	else if(CHx == DMA2_Channel1)
		return DMA2_Channel1_IRQn;
	else if(CHx == DMA2_Channel2)
		return DMA2_Channel2_IRQn;
	else if(CHx == DMA2_Channel3)
		return DMA2_Channel3_IRQn;
	else if(CHx == DMA2_Channel4)
		return DMA2_Channel4_5_IRQn;
	else if(CHx == DMA2_Channel5)
		return DMA2_Channel4_5_IRQn;
	else
		AssertFailed("DMA channel not exist.", __FILE__, __LINE__);
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
	if(isGrouped)
	{
		uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
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
