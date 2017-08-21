#include "stm32f10x.h"
#include <stdio.h>
#include "Bayonet_CRC.h"

uint32_t bufferToWrite[32] = {
	0x12345678,
	0x14566874,
	0x32158481,
	0x58978945
};

uint32_t temp;

int main(void)
{
	uint16_t i;
	
	Bayonet_CRC_Init();
	
	//Calculating buffer will auto reset CRC. 
	temp = Bayonet_CRC_CaculateBuffer(bufferToWrite, 4);
	
	//Calculating word dose not support auto reset is for a more flexibal utilization. 
	Bayonet_CRC_Reset();
	for(i = 0; i < 4; i++)
		temp = Bayonet_CRC_CalculateWord(bufferToWrite[i]);
	
	//Result after calculation of CalculatieBuffer and CalculateWord should be equal. 
	printf("%d", temp);
	
	while(1)
	{
	}
}
