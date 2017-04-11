#ifndef __BAYONET_FLASH_H
#define __BAYONET_FLASH_H

#include "stm32f10x.h"

#define Bayonet_FLASH_KEY1 0x45670123
#define Bayonet_FLASH_KEY2 0xCDEF89AB

extern uint16_t Bayonet_FLASH_Buffer[1024];

void Bayonet_FLASH_ReadHalfWord(uint32_t address, uint16_t *buffer, uint16_t count);
void Bayonet_FLASH_Write(uint32_t address, uint16_t *buffer, uint16_t count);

#endif
