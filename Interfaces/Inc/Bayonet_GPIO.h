#ifndef __BAYONET_GPIO_H
#define __BAYONET_GPIO_H

#include "stm32f10x.h"

#define Bayonet_GPIO_MODE_GPIA			0x00000000
#define Bayonet_GPIO_MODE_GPIF			0x00000001
#define Bayonet_GPIO_MODE_GPIU			0x00000002
#define Bayonet_GPIO_MODE_GPID			0x00000003
#define Bayonet_GPIO_MODE_GPOGPP		0x00000004
#define Bayonet_GPIO_MODE_GPOGOD		0x00000005
#define Bayonet_GPIO_MODE_GPOAPP		0x00000006
#define Bayonet_GPIO_MODE_GPOAOD		0x00000007

void Bayonet_GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t Pinx, uint8_t IO);
uint8_t Bayonet_GPIO_Get(GPIO_TypeDef *GPIOx, uint8_t Pinx);
void Bayonet_GPIO_Set(GPIO_TypeDef *GPIOx, uint8_t Pinx, uint8_t state);
void Bayonet_GPIO_Turn(GPIO_TypeDef *GPIOx, uint8_t Pinx);

#endif
