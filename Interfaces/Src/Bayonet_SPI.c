/**
	********************************************************************************
	* 
	* MIT License (MIT)
	* 
	* Copyright (c) 2017 Shandong University at Weihai μMaster team
	* @email songqiang.1304521@163.com
	* @github https://github.com/ShandongUniversityMicroMaster/Bayonet_STM32F10x
	*
	* All rights reserved. 
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	* 
  ********************************************************************************
	* The above copyright notice and this permission notice shall be included in all
	* copies or substantial portions of the Software.
	* 
	********************************************************************************
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	* SOFTWARE.
	*
	********************************************************************************
	*/
	
#include "Bayonet_SPI.h"
#include "Bayonet_RCC.h"
#include "Bayonet_UART.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_NVIC.h"

//uint8_t bayonetSPIMode[3] = {0};

/**
  * @brief  Configuring clocks and IO port for SPI interface. 
  * @param  SPIx: where x can be (1..3) to select SPI interface.
  * @param  mode: SPI working in master mode or slave mode. 
  * @retval None
  */
void Bayonet_SPI_Clock_IO_Init(SPI_TypeDef *SPIx, uint8_t mode)
{
	Bayonet_GPIO_Mode modeIO[3];
	if(mode == Bayonet_SPI_MODE_MASTER)
	{
		modeIO[0] = Bayonet_GPIO_MODE_GPOAPP;
		modeIO[1] = Bayonet_GPIO_MODE_GPIU;
		modeIO[2] = Bayonet_GPIO_MODE_GPOAPP;
	}
	else if(mode == Bayonet_SPI_MODE_SLAVE)
	{
		modeIO[0] = Bayonet_GPIO_MODE_GPIU;
		modeIO[1] = Bayonet_GPIO_MODE_GPOAPP;
		modeIO[2] = Bayonet_GPIO_MODE_GPIU;
	}
	else
		AssertFailed("SPI mode not exist. ", __FILE__, __LINE__);
	if(SPIx == SPI1)
	{
		Bayonet_RCC_Active(Bayonet_RCC_SPI1);
		Bayonet_RCC_Active(Bayonet_RCC_GPIOA);
		
		Bayonet_GPIO_Init(GPIOA, 5, modeIO[0]);				//SCK
		Bayonet_GPIO_Init(GPIOA, 6, modeIO[1]);				//MISO
		Bayonet_GPIO_Init(GPIOA, 7, modeIO[2]);				//MOSI
	}
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
	else if(SPIx == SPI2)
	{
		Bayonet_RCC_Active(Bayonet_RCC_SPI2);
		Bayonet_RCC_Active(Bayonet_RCC_GPIOB);
		
		Bayonet_GPIO_Init(GPIOB, 13, modeIO[0]);			//SCK. 
		Bayonet_GPIO_Init(GPIOB, 14, modeIO[1]);			//MISO.
		Bayonet_GPIO_Init(GPIOB, 15, modeIO[2]);			//MOSI
	}
#endif
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
	else if(SPIx == SPI3)
	{
		Bayonet_RCC_Active(Bayonet_RCC_SPI3);
	}
#endif
	else
		AssertFailed("SPI devices not found. ", __FILE__, __LINE__);
}

/**
  * @brief  Initializing SPI interface with master mode. 
  * @param  SPIx: where x can be (1..3) to select SPI interface.
  * @param  spped: SPI working badurate. 
  * @retval None. 
  */
void	Bayonet_SPI_Init_Master(SPI_TypeDef *SPIx, Bayonet_SPI_SPEED speed)
{
	RCC_ClocksTypeDef frequency;
	uint8_t fraction;
	Bayonet_SPI_Clock_IO_Init(SPIx, Bayonet_SPI_MODE_MASTER);
	Bayonet_RCC_GetClocksFreq(&frequency);
	
	fraction = 36000000 / frequency.PCLK2_Frequency;
	SPIx->CR1 |= (speed << 3) >> fraction;
	
	SPIx->CR1 |= SPI_CR1_CPOL;
	SPIx->CR1 |= SPI_CR1_CPHA;
	SPIx->CR1 &=~ SPI_CR1_DFF;
	SPIx->CR1 &=~ SPI_CR1_LSBFIRST;
	SPIx->CR1 |= SPI_CR1_SSM;
	SPIx->CR1 |= SPI_CR1_SSI;
	SPIx->CR1 |= SPI_CR1_MSTR;
	SPIx->CR1 |= SPI_CR1_SPE;
	
	Bayonet_SPI_ReadWriteByte(SPIx, 0xff);
}

/**
  * @brief  Initializing SPI interface with slave mode. 
  * @param  SPIx: where x can be (1..3) to select SPI interface.
  * @param  prePriority: preemptionPriority for SPI receive interrupt. 
  * @param  subPriority: subPriority for SPI receive interrupt. 
  * @retval None. 
  */
void Bayonet_SPI_Init_Slave(SPI_TypeDef *SPIx, uint8_t prePriority, uint8_t subPriority)
{
	Bayonet_SPI_Clock_IO_Init(SPIx, Bayonet_SPI_MODE_SLAVE);
	
	SPIx->CR1 &=~ SPI_CR1_DFF;				//8 bit data mode. 
	SPIx->CR1 |= SPI_CR1_CPOL;
	SPIx->CR1 |= SPI_CR1_CPHA;				//
	SPIx->CR1 &=~ SPI_CR1_LSBFIRST;		//MSB first. 
	SPIx->CR1 &=~ SPI_CR1_MSTR;				//Slave mode. 
	SPIx->CR1 &=~ SPI_CR1_SSM;				//Hardware slave configuration.  
	SPIx->CR2 &=~ SPI_CR2_SSOE;
	SPIx->CR1 |= SPI_CR1_SPE;					//ENABLE SPIx
	SPIx->CR2 |= SPI_CR2_RXNEIE;			//Enable receive buffer not empty intterupt. 
	
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_SPI(SPIx), prePriority, subPriority);
}

/**
  * @brief  Start one data transfer. 
  * @param  SPIx: where x can be (1..3) to select SPI interface.
  * @param  data: data to send. 
  * @retval data received. 
  */
uint8_t Bayonet_SPI_ReadWriteByte(SPI_TypeDef *SPIx, uint8_t data)
{
	while(!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = data;
	while(!(SPIx->SR & SPI_SR_RXNE));
	return SPIx->DR;
}

/**
  * @brief  Transfer <count> bytes data, receiving data will overwrite sending buffer. 
  * @param  SPIx: where x can be (1..3) to select SPI interface.
  * @param  data: pointing to the buffer of data to send. 
  * @param  count: how many bytes data to transfer. 
  * @retval 0 for success. 
  */
void Bayonet_SPI_ReadWriteBuff(SPI_TypeDef *SPIx, uint8_t *data, uint8_t count)
{
	uint8_t i = 0;
	for(i = 0; i < count; i++)
		data[count] = Bayonet_SPI_ReadWriteByte(SPIx, data[count]);
}
