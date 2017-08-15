#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_EXTI.h"
#include "Bayonet_DAC.h"
#include <stdint.h>

int main(void)
{
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	Bayonet_DAC_Init_WithoutWave(Bayonet_DAC_CHANNEL1, 512);
	Bayonet_DAC_Init_WithoutWave(Bayonet_DAC_CHANNEL2, 2048);
	
	Bayonet_Delay_Ms(1000);
	
	Bayonet_DAC_SetOuputLevel(Bayonet_DAC_CHANNEL1, 2048);
	Bayonet_DAC_SetOuputLevel(Bayonet_DAC_CHANNEL2, 512);
	
	while(1)
	{
	}
}
