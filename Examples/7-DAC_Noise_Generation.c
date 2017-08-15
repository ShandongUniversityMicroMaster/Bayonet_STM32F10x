#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_EXTI.h"
#include "Bayonet_DAC.h"
#include "Bayonet_RCC.h"
#include <stdint.h>

int main(void)
{
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	Bayonet_TIM_Init_Interrupt(TIM6, 1, 0, 0);
	Bayonet_DAC_Init_NoiseGeneration(Bayonet_DAC_CHANNEL1, 10, Bayonet_DAC_AMPLITUDE_1023, Bayonet_DAC_TRIGGER_TIM6);
	while(1)
	{
	}
}

void TIM6_IRQHandler()
{
	if(TIM6->SR & TIM_SR_UIF)
	{
		TIM6->SR &=~ TIM_SR_UIF;
	}
}
