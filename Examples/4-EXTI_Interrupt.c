#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_EXTI.h"
#include <stdint.h>

uint8_t data;

int main(void)
{
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	Bayonet_EXTI_Interrupt_Init(GPIOA, 1, Bayonet_EXTI_TRIGGER_FALLING, 0, 0);
	Bayonet_GPIO_Init(GPIOA, 0, Bayonet_GPIO_MODE_GPOGPP);
	
	while(1)
	{
		Bayonet_Delay_Ms(1000);
		GPIOA->ODR |= 1 << 0;
		Bayonet_Delay_Ms(1000);
		GPIOA->ODR &=~ (1 << 0);
	}
}

void EXTI1_IRQHandler()
{
	static uint8_t data;
	if(EXTI->PR & (1 << 1))
	{
		data++;
		EXTI->PR |= 1 << 1;
	}
}
