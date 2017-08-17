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

//Test model: SST39VF160, connected to the second bank. 

int main(void)
{
	uint16_t i;
	Bayonet_FSMC_TIMING_NORSRAM_PARAMETER timingParameter;
	
	for(i = 0; i < 32; i++)
		bufferToWrite[i] = 0x00001234 + i;
	
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	timingParameter.AccessMode = Bayonet_FSMC_ACCESSMODE_B;
	timingParameter.AddressSetupPhaseDuration = 5;
	timingParameter.Address_HoldPhaseDuration = 0;
	timingParameter.Data_PhaseDuration = 7;
	timingParameter.BusTurnAroundPhaseDuration = 0;
	timingParameter.ClockDivideRatio = 0;
	timingParameter.DataLatency = 0;
	Bayonet_FSMC_Init_NOR(Bayonet_FSMC_DATA_LINE_WIDTH_16, 0, 23, 1, &timingParameter);
	
	Bayonet_FSMC_WriteHalfWord(0x6400AAAA, 0xAA);
	Bayonet_FSMC_WriteHalfWord(0x64005554, 0x55);
	Bayonet_FSMC_WriteHalfWord(0x6400AAAA, 0x80);
	Bayonet_FSMC_WriteHalfWord(0x6400AAAA, 0xAA);
	Bayonet_FSMC_WriteHalfWord(0x64005554, 0x55);
	Bayonet_FSMC_WriteHalfWord(0x64008000, 0x30);
	Bayonet_Delay_Ms(1000);
	
	Bayonet_FSMC_WriteHalfWord(0x6400AAAA, 0xAA);
	Bayonet_FSMC_WriteHalfWord(0x64005554, 0x55);
	Bayonet_FSMC_WriteHalfWord(0x6400AAAA, 0xA0);
	Bayonet_FSMC_WriteHalfWord(0x64008000, 0x4567);
	Bayonet_Delay_Ms(1000);
	
	Bayonet_FSMC_WriteHalfWord(0x6400AAAA, 0xAA);
	Bayonet_FSMC_WriteHalfWord(0x64005554, 0x55);
	Bayonet_FSMC_WriteHalfWord(0x64008000, 0xF0);
	bufferToRead[0] = *(uint16_t *) 0x64008000;
	bufferToRead[1] = *(uint16_t *) 0x64008002;
	bufferToRead[2] = *(uint16_t *) 0x64008004;
	
	while(1)
	{
	}
}
