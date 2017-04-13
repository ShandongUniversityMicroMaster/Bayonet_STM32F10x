#include "stm32f10x.h"
#include "Bayonet_GPIO.h"

int main(void)
{
	//Simplely initialize your IO port with function Bayonet_GPIO_Init().
	//Initialize PA2 in general purpose mode. 
	Bayonet_GPIO_Init(GPIOA, 2, Bayonet_GPIO_MODE_GPOGPP);
	//Initialize PA1 in general purpose input mode with pull-up. 
	Bayonet_GPIO_Init(GPIOA, 1, Bayonet_GPIO_MODE_GPIU);
	
	//Set PA2 to high. 
	Bayonet_GPIO_Set(GPIOA, 2, 1);
	//Set PA2 to low. 
	Bayonet_GPIO_Set(GPIOA, 2, 0);
	//Turn PA2 output level. 
	Bayonet_GPIO_Turn(GPIOA, 2);
	//Get the voltage level of PA1. 
	Bayonet_GPIO_Get(GPIOA, 1);
	while(1)
	{
	}
}
