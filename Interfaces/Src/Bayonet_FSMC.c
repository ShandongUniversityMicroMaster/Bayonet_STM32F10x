#include "Bayonet_FSMC.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_RCC.h"
#include "Bayonet_UART.h"

#if defined (STM32F10X_HD) || defined (STM32F10X_XL)

//FSMC_A[25..0]
Bayonet_GPIO_Pin addressPins[26] = {
	{GPIOF,  0},					//0
	{GPIOF,  1},					//1
	{GPIOF,  2},					//2
	{GPIOF,  3},					//3
	{GPIOF,  4},					//4
	{GPIOF,  5},					//5
	{GPIOF, 12},					//6
	{GPIOF, 13},					//7
	{GPIOF, 14},					//8
	{GPIOF, 15},					//9
	{GPIOG,  0},					//10
	{GPIOG,  1},					//11
	{GPIOG,  2},					//12
	{GPIOG,  3},					//13
	{GPIOG,  4},					//14
	{GPIOG,  5},					//15
	{GPIOD, 11},					//16
	{GPIOD, 12},					//17
	{GPIOD, 13},					//18
	{GPIOE,  3},					//19
	{GPIOE,  4},					//20
	{GPIOE,  5},					//21
	{GPIOE,  6},					//22
	{GPIOE,  2},					//23
	{GPIOG, 13},					//24
	{GPIOG, 14},					//25
};

/**
  * @brief  Clock and IO configuration for FSMC. 
  * @param  dataLineWidth: 8 bits or 16 bits. 
  * @param  addressLineStart: start index of the address bus. 
  * @param  addressLineWidth: width of the address bus. 
  * @retval None. 
  */
void Bayonet_FSMC_Clock_IO_Init(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth, 
																	uint8_t addressLineStart, 
																	uint8_t addressLineWidth )
{
	uint8_t i = 0;
	
	Bayonet_RCC_Active(Bayonet_RCC_FSMC);
	
	//FSMC_D[7..0] or FSMC_D[15..0]
	Bayonet_GPIO_Init(GPIOD, 14, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOD, 15, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOD,  0, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOD,  1, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOE,  7, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOE,  8, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOE,  9, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOE, 10, Bayonet_GPIO_MODE_GPOAPP);
	if(dataLineWidth == Bayonet_FSMC_DATA_LINE_WIDTH_16)
	{
		Bayonet_GPIO_Init(GPIOE, 11, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOE, 12, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOE, 13, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOE, 14, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOE, 15, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOD,  8, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOD,  9, Bayonet_GPIO_MODE_GPOAPP);
		Bayonet_GPIO_Init(GPIOD, 10, Bayonet_GPIO_MODE_GPOAPP);
	}
	
	//FSMC_A[x..0]
	for(i = addressLineStart; i < addressLineStart + addressLineWidth; i++)
		Bayonet_GPIO_Init(addressPins[i].GPIOx, addressPins[i].Pinx, Bayonet_GPIO_MODE_GPOAPP);
	
	Bayonet_GPIO_Init(GPIOD, 4, Bayonet_GPIO_MODE_GPOAPP);		//NOE
	Bayonet_GPIO_Init(GPIOD, 5, Bayonet_GPIO_MODE_GPOAPP);		//NWE
}

/**
  * @brief  Basic configuration for NOR/SRAM mode initialization. 
  * @param  dataLineWidth: 8 bits or 16 bits. 
  * @param  addressLineStart: start index of the address bus. 
  * @param  addressLineWidth: width of the address bus. 
  * @param  bankNumber: 0..4 for this mode. 
  * @param  timingParameters: timing parameters for manipulating nor flash. 
  * @retval None. 
  */
void Bayonet_FSMC_RAM_NOR_Clock_IO_Init(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth, 
																					uint8_t addressLineStart, 
																					uint8_t addressLineWidth, 
																					uint8_t bankNumber, 
																					Bayonet_FSMC_TIMING_NORSRAM_PARAMETER* timingParameter)
{
	Bayonet_FSMC_Clock_IO_Init(dataLineWidth, addressLineStart, addressLineWidth);
	
	switch(bankNumber)
	{
		case 0:
			Bayonet_GPIO_Init(GPIOD,  7, Bayonet_GPIO_MODE_GPOAPP);
			break;
		case 1:
			Bayonet_GPIO_Init(GPIOG,  9, Bayonet_GPIO_MODE_GPOAPP);
			break;
		case 2:
			Bayonet_GPIO_Init(GPIOG, 10, Bayonet_GPIO_MODE_GPOAPP);
			break;
		case 3:
			Bayonet_GPIO_Init(GPIOG, 12, Bayonet_GPIO_MODE_GPOAPP);
			break;
		default:
			AssertFailed("Memory Bank Index Error. ", __FILE__, __LINE__); 
	}
	
	Bayonet_GPIO_Init(GPIOE, 0, Bayonet_GPIO_MODE_GPOAPP);
	Bayonet_GPIO_Init(GPIOE, 1, Bayonet_GPIO_MODE_GPOAPP);
	
	FSMC_Bank1->BTCR[bankNumber * 2 + 1] = (	timingParameter->AccessMode << 28 |
																						timingParameter->DataLatency << 24 |
																						timingParameter->ClockDivideRatio << 20 |
																						timingParameter->BusTurnAroundPhaseDuration << 16 |
																						timingParameter->Data_PhaseDuration << 8 |
																						timingParameter->Address_HoldPhaseDuration << 4 |
																						timingParameter->AddressSetupPhaseDuration);
}

/**
  * @brief  Initializing FSMC bank 1 to SRAM control mode. 
  * @param  dataLineWidth: 8 bits or 16 bits. 
  * @param  addressLineStart: start index of the address bus. 
  * @param  addressLineWidth: width of the address bus. 
  * @param  bankNumber: 0..4 for this mode. 
  * @param  timingParameters: timing parameters for manipulating SRAM. 
  * @retval None. 
  */
void Bayonet_FSMC_Init_RAM(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth, 
														uint8_t addressLineStart, 
														uint8_t addressLineWidth, 
														uint8_t bankNumber, 
														Bayonet_FSMC_TIMING_NORSRAM_PARAMETER* timingParameter)
{
	Bayonet_FSMC_RAM_NOR_Clock_IO_Init(dataLineWidth, addressLineStart, addressLineWidth, bankNumber, timingParameter);
	
	FSMC_Bank1->BTCR[bankNumber * 2] &=~ (FSMC_BCR1_MUXEN |
																				FSMC_BCR1_MTYP | 
																				FSMC_BCR1_FACCEN | 
																				FSMC_BCR1_BURSTEN | 
																				FSMC_BCR1_WAITEN);
	FSMC_Bank1->BTCR[bankNumber * 2] |= dataLineWidth;
	
	FSMC_Bank1->BTCR[bankNumber * 2] |= FSMC_BCR1_MBKEN; 
}

/**
  * @brief  Initializing FSMC bank 1 to NOR flash control mode. 
  * @param  dataLineWidth: 8 bits or 16 bits. 
  * @param  addressLineStart: start index of the address bus. 
  * @param  addressLineWidth: width of the address bus. 
  * @param  bankNumber: 0..4 for this mode. 
  * @param  timingParameters: timing parameters for manipulating NOR flash. 
  * @retval None. 
  */
void Bayonet_FSMC_Init_NOR(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth, 
														uint8_t addressLineStart, 
														uint8_t addressLineWidth, 
														uint8_t bankNumber, 
														Bayonet_FSMC_TIMING_NORSRAM_PARAMETER* timingParameter)
{
	Bayonet_FSMC_RAM_NOR_Clock_IO_Init(dataLineWidth, addressLineStart, addressLineWidth, bankNumber, timingParameter);
	
	FSMC_Bank1->BTCR[bankNumber * 2] &=~ (FSMC_BCR1_MUXEN | 
																				FSMC_BCR1_BURSTEN | 
																				FSMC_BCR1_WAITEN);
	FSMC_Bank1->BTCR[bankNumber * 2] |= dataLineWidth | FSMC_BCR1_MTYP_1;
	FSMC_Bank1->BTCR[bankNumber * 2] &=~ (1 << 7);
	
	FSMC_Bank1->BTCR[bankNumber * 2] |= FSMC_BCR1_MBKEN; 
}

void Bayonet_FSMC_Init_NAND(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth,
															uint8_t addressLineStart,
															uint8_t addressLineWidth,
															uint8_t bankNumber)
{
	Bayonet_FSMC_Clock_IO_Init(dataLineWidth, addressLineStart, addressLineWidth);
	
	if(bankNumber == 0)
	{
		Bayonet_GPIO_Init(GPIOD, 7, Bayonet_GPIO_MODE_GPOAPP);		//NCE2
		Bayonet_GPIO_Init(GPIOG, 6, Bayonet_GPIO_MODE_GPIU);			//INT2
	}
	else if(bankNumber == 1)
	{
		Bayonet_GPIO_Init(GPIOG, 9, Bayonet_GPIO_MODE_GPOAPP);		//NCE3
		Bayonet_GPIO_Init(GPIOG, 7, Bayonet_GPIO_MODE_GPIU);			//INT3
	}
	else
		AssertFailed("bankNumber error. ", __FILE__, __LINE__);
		
	Bayonet_GPIO_Init(GPIOD, 6, Bayonet_GPIO_MODE_GPIU);				//NWAIT
	
}

/**
  * @brief  Write a half word data to address through FSMC. 
  * @param  dataLineWidth: 8 bits or 16 bits. 
  * @param  addressLineStart: start index of the address bus. 
  * @retval None. 
  */
void Bayonet_FSMC_WriteHalfWord(uint32_t address, uint16_t data)
{
	*(uint16_t *) address = data;
}

void Bayonet_FSMC_WriteFromBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length * 2; i+=2)
		*(uint16_t *) (addressStart + i) = *pBuffer++;
}

void Bayonet_FSMC_ReadToBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length * 2; i+=2)
		*pBuffer++ = *(uint16_t *) (addressStart + i);
}

#endif
