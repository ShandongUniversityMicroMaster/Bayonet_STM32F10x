#include "Bayonet_FSMC.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_RCC.h"
#include "Bayonet_UART.h"

#if defined (STM32F10X_HD) || defined (STM32F10X_XL)

bool Bayonet_FSMC_isInit[7] = {false};

//FSMC_A[25..0]
const Bayonet_GPIO_Pin addressPins[26] = {
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
	if(Bayonet_FSMC_isInit[bankNumber])
		AssertFailed("Memory bank has already been using. ", __FILE__, __LINE__);
	else
		Bayonet_FSMC_isInit[bankNumber] = true;
	
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

/**
  * @brief  Initializing FSMC bank 1 to NAND flash control mode. 
  * @param  dataLineWidth: 8 bits or 16 bits. 
  * @param  addressLineStart: start index of the address bus. 
  * @param  addressLineWidth: width of the address bus. 
  * @param  bankNumber: 0..1 for this mode. 
  * @param  timingParametersCommon: common timing parameters for manipulating NAND flash. 
  * @param  timingParametersAttribute: attribute timing parameters for manipulating NAND flash. 
  * @retval None. 
  */
void Bayonet_FSMC_Init_NAND(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth,
															uint8_t addressLineStart,
															uint8_t addressLineWidth,
															uint8_t bankNumber,
															Bayonet_FSMC_TIMING_NAND_PCCARD_PARAMETER* timingParametersCommon, 
															Bayonet_FSMC_TIMING_NAND_PCCARD_PARAMETER* timingParametersAttribute)
{
	uint32_t tempPCR, tempPCRN, tempMEM, tempATT;
	
	if(Bayonet_FSMC_isInit[bankNumber + 4])
		AssertFailed("Memory bank has already been using. ", __FILE__, __LINE__);
	else
		(Bayonet_FSMC_isInit[bankNumber + 4] = true);
	
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
		AssertFailed("Bank number exceeds. ", __FILE__, __LINE__);
	
	Bayonet_GPIO_Init(GPIOD, 6, Bayonet_GPIO_MODE_GPIU);				//NWAIT
	
	tempPCRN = FSMC_PCR2_PWID;
	tempPCR = FSMC_PCR2_PWAITEN | FSMC_PCR2_ECCEN | FSMC_PCR2_ECCPS_1 | FSMC_PCR2_ECCPS_0;
	
	tempMEM = timingParametersCommon->HiZSetupTime << 24 | 
						timingParametersCommon->HoldSetupTime << 16 | 
						timingParametersCommon->WaitSetupTime << 8 |
						timingParametersCommon->SetupTime;
	
	tempATT = timingParametersAttribute->HiZSetupTime << 24 |
						timingParametersAttribute->HoldSetupTime << 16 |
						timingParametersAttribute->WaitSetupTime << 8 |
						timingParametersAttribute->SetupTime;
	
	if(bankNumber == 0)
	{
		FSMC_Bank2->PCR2 &=~ tempPCRN;
		FSMC_Bank2->PCR2 |= tempPCR;
		FSMC_Bank2->PMEM2 = tempMEM;
		FSMC_Bank2->PATT2 = tempATT;
		
		FSMC_Bank2->PCR2 |= FSMC_PCR2_PBKEN;
	}
	else
	{
		FSMC_Bank3->PCR3 &=~ tempPCR;
		FSMC_Bank3->PCR3 |= tempPCR;
		FSMC_Bank3->PMEM3 = tempMEM;
		FSMC_Bank3->PATT3 = tempATT;
		
		FSMC_Bank3->PCR3 |= FSMC_PCR3_PBKEN;
	}
}

#ifdef Bayonet_Assert
//These code is to check if the address is valid in case of hardfault. 
uint32_t Bayonet_FSMC_Address[] = {	
	0x60000000,
	0x64000000,
	0x68000000,
	0x6C000000,
	0x70000000,
	0x80000000,
	0x90000000
};

/**
  * @brief  Check if the address using is legal. 
  * @param  address: the address you are using. 
  * @retval None. 
  */
void Bayonet_FSMC_CheckAddressValid(uint32_t address)
{
	uint8_t i;
	if(address < Bayonet_FSMC_Address[0] || address > Bayonet_FSMC_Address[6])
		AssertFailed("Address illeagle, which is not in FSMC manipulation range. ", __FILE__, __LINE__);
	
	for(i = 0; i < 6; i++)
	{
		if(address > Bayonet_FSMC_Address[i] && address < Bayonet_FSMC_Address[i + 1])
		{
			if(!Bayonet_FSMC_isInit[i])
				AssertFailed("Memory bank you are reading/writing has not been initilized. ", __FILE__, __LINE__);
		}
	}
}
#endif

/**
  * @brief  Write a byte data to address through FSMC. 
  * @param  address: address to write. 
  * @param  data: data to write. 
  * @retval None. 
  */
void Bayonet_FSMC_WriteByte(uint32_t address, uint8_t data)
{
#ifdef Bayonet_Assert
	Bayonet_FSMC_CheckAddressValid(address);
#endif
	*(__IO uint8_t *)address = data;
}

/**
  * @brief  Read a byte data from address through FSMC. 
  * @param  address: address to read. 
  * @retval data read. 
  */
uint8_t Bayonet_FSMC_ReadByte(uint32_t address)
{
#ifdef Bayonet_Assert
	Bayonet_FSMC_CheckAddressValid(address);
#endif
	return *(__IO uint8_t *)address;
}

/**
  * @brief  Write a halfword data to address through FSMC. 
  * @param  address: address to write. 
  * @param  data: data to write. 
  * @retval None. 
  */
void Bayonet_FSMC_WriteHalfWord(uint32_t address, uint16_t data)
{
#ifdef Bayonet_Assert
	Bayonet_FSMC_CheckAddressValid(address);
#endif
	*(__IO uint16_t *) address = data;
}

/**
  * @brief  Read a halfword data from address through FSMC. 
  * @param  address: address to read. 
  * @retval data read. 
  */
uint16_t Bayonet_FSMC_ReadHalfWord(uint32_t address, uint16_t data)
{
#ifdef Bayonet_Assert
	Bayonet_FSMC_CheckAddressValid(address);
#endif
	return *(__IO uint16_t *) address;
}

/**
  * @brief  Write buffer of halfword data to address through FSMC. 
  * @param  pBuffer: buffer to write. 
  * @param  addressStart: the start address to write. 
  * @param  length: number of data to write. 
  * @retval None. 
  */
void Bayonet_FSMC_WriteHalfwordsFromBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length * 2; i+=2)
	{
#ifdef Bayonet_Assert
		Bayonet_FSMC_CheckAddressValid(addressStart + i);
#endif
		*(__IO uint16_t *) (addressStart + i) = *(pBuffer + i);
	}
}

/**
  * @brief  Consecutively read halfword data from address to a buffer through FSMC. 
  * @param  pBuffer: buffer to store data. 
  * @param  addressStart: the start address to read. 
  * @param  length: number of data to read. 
  * @retval None. 
  */
void Bayonet_FSMC_ReadHalfwordsToBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length * 2; i+=2)
	{
#ifdef Bayonet_Assert
		Bayonet_FSMC_CheckAddressValid(addressStart + i);
#endif
		*(pBuffer + i) = *(__IO uint16_t *) (addressStart + i);
	}
}

/**
  * @brief  Write buffer of byte data to address through FSMC. 
  * @param  pBuffer: buffer to write. 
  * @param  addressStart: the start address to write. 
  * @param  length: number of data to write. 
  * @retval None. 
  */
void Bayonet_FSMC_WriteBytesFromBuffer(uint8_t* pBuffer, uint32_t addressStart, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length; i++)
	{
#ifdef Bayonet_Assert
		Bayonet_FSMC_CheckAddressValid(addressStart + i);
#endif
		*(__IO uint8_t *) (addressStart + i) = *(pBuffer + i);
	}
}

/**
  * @brief  Consecutively read byte data from address to a buffer through FSMC. 
  * @param  pBuffer: buffer to store data. 
  * @param  addressStart: the start address to read. 
  * @param  length: number of data to read. 
  * @retval None. 
  */
void Bayonet_FSMC_ReadBytesToBuffer(uint8_t* pBuffer, uint32_t addressStart, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length; i++)
	{
#ifdef Bayonet_Assert
		Bayonet_FSMC_CheckAddressValid(addressStart + i);
#endif
		*(pBuffer + i) = *(__IO uint8_t *) (addressStart + i);
	}
}
#endif
