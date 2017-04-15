#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"

int main(void)
{
	//Initialize delay module with function Bayonet_Delay_Init. 
	Bayonet_Delay_Init();
	//Initialize PA2 in general purpose mode. It is best if it is connected to a LED as control. 
	Bayonet_GPIO_Init(GPIOA, 2, Bayonet_GPIO_MODE_GPOGPP);
	while(1)
	{
		Bayonet_GPIO_Set(GPIOA, 2, 0); //Most LED port is low active. 
		//Delay 1000 microseconds, which equals to 1 milliseconds. 
		Bayonet_Delay_Us(1000);
		Bayonet_GPIO_Set(GPIOA, 2, 1);
		//Delay 1000 millisecons.
		Bayonet_Delay_Ms(1000);
	}
}
