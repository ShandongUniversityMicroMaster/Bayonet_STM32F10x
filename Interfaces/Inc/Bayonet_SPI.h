#ifndef __BAYONET_SPI_H
#define __BAYONET_SPI_H

#include "stm32f10x.h"

typedef enum{
	Bayonet_SPI_MODE_MASTER,
	Bayonet_SPI_MODE_SLAVE
}Bayonet_SPI_MODE;

typedef enum{
	Bayonet_SPI_SPEED_18M,
	Bayonet_SPI_SPEED_9M,
	Bayonet_SPI_SPEED_4M5,
	Bayonet_SPI_SPEED_2M25,
	Bayonet_SPI_SPEED_1M125,
	Bayonet_SPI_SPEED_562K5,
	Bayonet_SPI_SPEED_281K25,
	Bayonet_SPI_SPEED_140K625
}Bayonet_SPI_SPEED;

uint8_t Bayonet_SPI_Init_Master(SPI_TypeDef *SPIx, Bayonet_SPI_SPEED speed);
uint8_t Bayonet_SPI_Init_Slave(SPI_TypeDef *SPIx, uint8_t prePriority, uint8_t subPriority);
uint8_t Bayonet_SPI_ReadWriteByte(SPI_TypeDef *SPIx, uint8_t data);

#endif
