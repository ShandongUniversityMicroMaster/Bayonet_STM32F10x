#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"

int main(void)
{
	//Initialize delay module with function Bayonet_Delay_Init(), 72 is clock frequency of systick. 
	//For stm32f10x series, this value is 72 or 36 regard as your chip reference manual or you can find it in ST's selection guide. 
	Bayonet_Delay_Init(72);
	//Initialize PA2 in general purpose mode. It is best if it is connected to a LED as control. 
	Bayonet_GPIO_Init(GPIOA, 2, Bayonet_GPIO_MODE_GPOGPP);
	while(1)
	{
		Bayonet_GPIO_Set(GPIOA, 2, 0); //Most LED port is low active. 
		//Delay 1000 micro seconds, which equals to 1 milliseconds. 
		Bayonet_Delay_Us(1000);
		Bayonet_GPIO_Set(GPIOA, 2, 1);
		//One thing to mention, the parameter in this function can not be over 1864. 
		//If you are looking for a longer delay, use multiple for now, we should perfected this function soon. 
		Bayonet_Delay_Ms(1000);
	}
}
