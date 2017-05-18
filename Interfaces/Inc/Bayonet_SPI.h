#ifndef __BAYONET_SPI_H
#define __BAYONET_SPI_H

#include "stm32f10x.h"

typedef enum{
	Bayonet_SPI_MODE_MASTER,
	Bayonet_SPI_MODE_SLAVE
}Bayonet_SPI_MODE;

void Bayonet_SPI_Init_Master(SPI_TypeDef *SPIx, uint16_t speed);
void Bayonet_SPI_Init_Slave(SPI_TypeDef *SPIx, uint8_t prePriority, uint8_t subPriority);
uint8_t Bayonet_SPI_ReadWriteByte(SPI_TypeDef *SPIx, uint8_t data);

#endif
