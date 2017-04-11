#include "Bayonet_LED.h"
#include "Bayonet_GPIO.h"

void Bayonet_LED_Init(uint32_t LEDx)
{
	if(LEDx & Bayonet_LED0)
		Bayonet_GPIO_Init(GPIOB, 11, Bayonet_GPIO_MODE_GPOGPP);
	if(LEDx & Bayonet_LED1)
		Bayonet_GPIO_Init(GPIOB, 10, Bayonet_GPIO_MODE_GPOGPP);
	if(LEDx & Bayonet_LED2)
		Bayonet_GPIO_Init(GPIOE, 15, Bayonet_GPIO_MODE_GPOGPP);
	if(LEDx & Bayonet_LED3)
		Bayonet_GPIO_Init(GPIOE, 14, Bayonet_GPIO_MODE_GPOGPP);
}

void Bayonet_LED_Set(uint32_t LEDx, uint8_t LED_State)
{
	if(LEDx & Bayonet_LED0)
		Bayonet_GPIO_Set(GPIOB, 11, LED_State);
	if(LEDx & Bayonet_LED1)
		Bayonet_GPIO_Set(GPIOB, 10, LED_State);
	if(LEDx & Bayonet_LED2)
		Bayonet_GPIO_Set(GPIOE, 15, LED_State);
	if(LEDx & Bayonet_LED3)
		Bayonet_GPIO_Set(GPIOE, 14, LED_State);
}

void Bayonet_LED_Turn(uint32_t LEDx)
{
	if(LEDx & Bayonet_LED0)
		Bayonet_GPIO_Turn(GPIOB, 11);
	if(LEDx & Bayonet_LED1)
		Bayonet_GPIO_Turn(GPIOB, 10);
	if(LEDx & Bayonet_LED2)
		Bayonet_GPIO_Turn(GPIOE, 15);
	if(LEDx & Bayonet_LED3)
		Bayonet_GPIO_Turn(GPIOE, 14);
}
