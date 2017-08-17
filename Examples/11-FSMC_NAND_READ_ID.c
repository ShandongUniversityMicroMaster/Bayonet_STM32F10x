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

struct
{
  uint8_t Maker_ID;
  uint8_t Device_ID;
  uint8_t Third_ID;
  uint8_t Fourth_ID;
}Maker;

uint16_t i;
uint16_t bufferToWrite[32], bufferToRead[32];

#define ADDRESS_CMD		Bayonet_ADDRESS_BANK_NAND_2 | (1 << 16)
#define ADDRESS_ADDR	Bayonet_ADDRESS_BANK_NAND_2 | (1 << 17)

int main(void)
{
	uint16_t i;
	Bayonet_FSMC_TIMING_NAND_PCCARD_PARAMETER timingParameter;
	
	for(i = 0; i < 32; i++)
		bufferToWrite[i] = 0x00001234 + i;
	
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	timingParameter.SetupTime = 1;
	timingParameter.WaitSetupTime = 3;
	timingParameter.HoldSetupTime = 2;
	timingParameter.HiZSetupTime = 1;
	Bayonet_FSMC_Init_NAND(Bayonet_FSMC_DATA_LINE_WIDTH_8, 16, 2, 0, &timingParameter, &timingParameter);
	
	Bayonet_FSMC_WriteByte(ADDRESS_CMD, 0x90);
	Bayonet_FSMC_WriteByte(ADDRESS_ADDR, 0x00);
	
	Bayonet_FSMC_ReadBytesToBuffer((uint8_t *)&Maker, Bayonet_ADDRESS_BANK_NAND_2, 4);
	
	while(1)
	{
	}
}
