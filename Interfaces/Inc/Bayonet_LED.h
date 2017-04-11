#ifndef __BAYONET_LED_H
#define __BAYONET_LED_H

#include "stm32f10x.h"
#include "Bayonet_Bitband.h"

#define Bayonet_LED0 0x00000001
#define Bayonet_LED1 0x00000002
#define Bayonet_LED2 0x00000004
#define Bayonet_LED3 0x00000008

#define Bayonet_LED_ON 		0x00000000
#define Bayonet_LED_OFF 	0x00000001

void Bayonet_LED_Init(uint32_t LEDx);
void Bayonet_LED_Set(uint32_t LEDx, uint8_t LED_State);
void Bayonet_LED_Turn(uint32_t LEDx);

#endif
