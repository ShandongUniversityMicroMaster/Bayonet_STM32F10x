#ifndef __BAYONET_IIC_H
#define __BAYONET_IIC_H

#include "stm32f10x.h"

typedef struct{
	uint8_t deviceID; 
	
	GPIO_TypeDef *SDA_Port;
	uint8_t SDA_Pin;
	GPIO_TypeDef *SCL_Port;
	uint8_t SCL_Pin;
}Bayonet_IIC_Device;

Bayonet_IIC_Device Bayonet_IIC_Init(GPIO_TypeDef *SDA_Port, uint8_t SDA_Pin, GPIO_TypeDef *SCL_Port, uint8_t SCL_Pin);
uint8_t Bayonet_IIC_ReadBytes(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t Bayonet_IIC_WriteBytes(Bayonet_IIC_Device device, uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);
uint8_t Bayonet_IIC_WriteBit(Bayonet_IIC_Device device, uint8_t dev, uint8_t reg, uint8_t bitNum, uint8_t data);

#endif
