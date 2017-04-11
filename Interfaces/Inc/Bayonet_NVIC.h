#ifndef __BAYONET_NVIC_H
#define __BAYONET_NVIC_H

#include "stm32f10x.h"
#include "Bayonet_Config.h"

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

#define Bayonet_NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define Bayonet_NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define Bayonet_NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define Bayonet_NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define Bayonet_NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */

void Bayonet_NVIC_SetGroup(uint32_t NVIC_PriorityGroup);
void Bayonet_NVIC_Init(uint8_t IRQChannel, uint8_t PrePriority, uint8_t SubPriority);
uint8_t Bayonet_NVIC_GetIRQChannel_DMA(DMA_Channel_TypeDef *CHx);
void Bayonet_NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);

#endif
