#ifndef __BAYONET_GPIO_H
#define __BAYONET_GPIO_H

#include "stm32f10x.h"

typedef enum{
	Bayonet_GPIO_MODE_GPIA,
	Bayonet_GPIO_MODE_GPIF,
  Bayonet_GPIO_MODE_GPIU,
  Bayonet_GPIO_MODE_GPID, 
  Bayonet_GPIO_MODE_GPOGPP, 
  Bayonet_GPIO_MODE_GPOGOD, 
  Bayonet_GPIO_MODE_GPOAPP, 
  Bayonet_GPIO_MODE_GPOAOD
}Bayonet_GPIO_Mode;

void Bayonet_GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t Pinx, Bayonet_GPIO_Mode Mode);
uint8_t Bayonet_GPIO_Get(GPIO_TypeDef *GPIOx, uint8_t Pinx);
void Bayonet_GPIO_Set(GPIO_TypeDef *GPIOx, uint8_t Pinx, uint8_t state);
void Bayonet_GPIO_Turn(GPIO_TypeDef *GPIOx, uint8_t Pinx);

#endif
