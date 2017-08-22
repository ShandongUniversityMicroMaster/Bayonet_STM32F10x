/**
	********************************************************************************
	* 
	* MIT License (MIT)
	* 
	* Copyright (c) 2017 Shandong University at Weihai µMaster team
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

#ifndef __BAYONET_FSMC_H
#define __BAYONET_FSMC_H

#include "stm32f10x.h"

//This function is only valid when using a chip with this peripheral. 
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)

typedef enum{
	Bayonet_FSMC_DATA_LINE_WIDTH_8,
	Bayonet_FSMC_DATA_LINE_WIDTH_16
}Bayonet_FSMC_DATA_LINE_WIDTH;

typedef enum{
	Bayonet_FSMC_ACCESSMODE_A,
	Bayonet_FSMC_ACCESSMODE_B,
	Bayonet_FSMC_ACCESSMODE_C,
	Bayonet_FSMC_ACCESSMODE_D
}Bayonet_FSMC_ACCESSMODE;

typedef struct{
	Bayonet_FSMC_ACCESSMODE AccessMode;
	uint8_t DataLatency;
	uint8_t ClockDivideRatio;
	uint8_t BusTurnAroundPhaseDuration;
	uint8_t Data_PhaseDuration;
	uint8_t Address_HoldPhaseDuration;
	uint8_t AddressSetupPhaseDuration;
}Bayonet_FSMC_TIMING_NORSRAM_PARAMETER;

typedef struct{
	uint8_t SetupTime;
	uint8_t WaitSetupTime;
	uint8_t HoldSetupTime;
	uint8_t HiZSetupTime;
}Bayonet_FSMC_TIMING_NAND_PCCARD_PARAMETER;

typedef struct
{
  uint8_t Maker_ID;
  uint8_t Device_ID;
  uint8_t Third_ID;
  uint8_t Fourth_ID;
}Bayonet_FSMC_NAND_ID;

#define Bayonet_ADDRESS_BANK_NORSRAM_1	0x60000000
#define Bayonet_ADDRESS_BANK_NORSRAM_2	0x64000000
#define Bayonet_ADDRESS_BANK_NORSRAM_3	0x68000000
#define Bayonet_ADDRESS_BANK_NORSRAM_4	0x6C000000
#define Bayonet_ADDRESS_BANK_NAND_2		0x70000000
#define Bayonet_ADDRESS_BANK_NAND_3		0x80000000
#define Bayonet_ADDRESS_BANK_PCCARD		0x90000000

void Bayonet_FSMC_Init_RAM(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth, 
														uint8_t addressLineStart, 
														uint8_t addressLineWidth, 
														uint8_t bankNumber, 
														Bayonet_FSMC_TIMING_NORSRAM_PARAMETER* timingParameter);
void Bayonet_FSMC_Init_NOR(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth, 
														uint8_t addressLineStart, 
														uint8_t addressLineWidth, 
														uint8_t bankNumber, 
														Bayonet_FSMC_TIMING_NORSRAM_PARAMETER* timingParameter);
void Bayonet_FSMC_Init_NAND(	Bayonet_FSMC_DATA_LINE_WIDTH dataLineWidth,
															uint8_t addressLineStart,
															uint8_t addressLineWidth,
															uint8_t bankNumber,
															Bayonet_FSMC_TIMING_NAND_PCCARD_PARAMETER* timingParametersCommon, 
															Bayonet_FSMC_TIMING_NAND_PCCARD_PARAMETER* timingParametersAttribute);
void Bayonet_FSMC_WriteHalfwordsFromBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length);
void Bayonet_FSMC_ReadHalfwordsToBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length);
void Bayonet_FSMC_WriteBytesFromBuffer(uint8_t* pBuffer, uint32_t addressStart, uint16_t length);
void Bayonet_FSMC_ReadBytesToBuffer(uint8_t* pBuffer, uint32_t addressStart, uint16_t length);
void Bayonet_FSMC_WriteHalfWord(uint32_t address, uint16_t data);
void Bayonet_FSMC_WriteByte(uint32_t addressCommand, uint8_t command);
uint8_t Bayonet_FSMC_ReadByte(uint32_t addressData);

#endif

#endif
