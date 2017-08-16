#ifndef __BAYONET_FSMC_H
#define __BAYONET_FSMC_H

#include "stm32f10x.h"

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
void Bayonet_FSMC_WriteFromBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length);
void Bayonet_FSMC_ReadToBuffer(uint16_t* pBuffer, uint32_t addressStart, uint16_t length);
void Bayonet_FSMC_WriteHalfWord(uint32_t address, uint16_t data);

#endif
