#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_EXTI.h"
#include "Bayonet_DAC.h"
#include "Bayonet_RCC.h"
#include <stdint.h>
#include <stdio.h>
#include "Bayonet_FSMC.h"

uint16_t i;
uint16_t bufferToWrite[32], bufferToRead[32];

int main(void)
{
	uint16_t i;
	Bayonet_FSMC_TIMING_NORSRAM_PARAMETER timingParameter;
	
	for(i = 0; i < 32; i++)
		bufferToWrite[i] = 0x00001234 + i;
	
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	timingParameter.AccessMode = Bayonet_FSMC_ACCESSMODE_A;
	timingParameter.AddressSetupPhaseDuration = 0;
	timingParameter.Address_HoldPhaseDuration = 0;
	timingParameter.Data_PhaseDuration = 2;
	timingParameter.BusTurnAroundPhaseDuration = 0;
	timingParameter.ClockDivideRatio = 0;
	timingParameter.DataLatency = 0;
	Bayonet_FSMC_Init_RAM(Bayonet_FSMC_DATA_LINE_WIDTH_16, 0, 18, 2, &timingParameter);
	
	Bayonet_FSMC_WriteHalfwordsFromBuffer(bufferToWrite, 0x68000000, 32);
	Bayonet_FSMC_ReadHalfwordsToBuffer(bufferToRead, 0x68000000, 32);
	
	while(1)
	{
	}
}
