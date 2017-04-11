#ifndef __BAYONET_TIM_H
#define __BAYONET_TIM_H

#include "stm32f10x.h"
#include "Bayonet_Config.h"

//TIM Mode
#define Bayonet_TIM_MODE_INT		0x00000000
#define Bayonet_TIM_MODE_PWM		0x00000001
#define Bayonet_TIM_MODE_ICAP		0x00000002

#define Bayonet_TIM_CH0					0x00000001
#define Bayonet_TIM_CH1					0x00000002
#define Bayonet_TIM_CH2					0x00000004
#define Bayonet_TIM_CH3					0x00000008

void Bayonet_TIM_INT_Init(TIM_TypeDef *TIMx, uint32_t Prescaler, uint32_t ReloadValue, uint8_t PrePriority, uint8_t SubPriority);
void Bayonet_TIM_PWM_Init(TIM_TypeDef *TIMx, uint32_t Prescaler, uint32_t ReloadValue, uint32_t CHx);

#endif
