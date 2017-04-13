#include "Bayonet_GPIO.h"
#include "Bayonet_UART.h"
#include <math.h>

void Bayonet_GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t Pinx, uint8_t IO)
{
	uint8_t config = 0x00;
	
	if(GPIOx == GPIOA)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if(GPIOx == GPIOB)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if(GPIOx == GPIOC)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else if(GPIOx == GPIOD)
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	else if(GPIOx == GPIOE)
		RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
	else
		AssertFailed("Port not exist. Bayonet_GPIO_Init. ");
	
	if(IO == Bayonet_GPIO_MODE_GPIA)
		config = 0x00;
	else if(IO == Bayonet_GPIO_MODE_GPIF)
		config = 0x04;
	else if(IO == Bayonet_GPIO_MODE_GPIU)
	{
		config = 0x08;
		GPIOx->ODR |= (1 << Pinx);
	}
	else if(IO == Bayonet_GPIO_MODE_GPID)
	{
		config = 0x08;
		GPIOx->ODR &=~ (1 << Pinx);
	}
	else if(IO == Bayonet_GPIO_MODE_GPOGPP)
		config = 0x03;
	else if(IO == Bayonet_GPIO_MODE_GPOGOD)
		config = 0x07;
	else if(IO == Bayonet_GPIO_MODE_GPOAPP)
		config = 0x0B;
	else if(IO == Bayonet_GPIO_MODE_GPOAOD)
		config = 0x0F;
	else
		AssertFailed("Mode not exist. Bayonet_GPIO_Init");
	
	if(Pinx < 8)
	{
		GPIOx->CRL &=~ (0x0f << (Pinx * 4));
		GPIOx->CRL |=  (config << (Pinx * 4));
	}
	else
	{
		GPIOx->CRH &=~ (0x0f << ((Pinx-8) * 4));
		GPIOx->CRH |=  (config << ((Pinx-8) * 4));
	}
}

uint8_t Bayonet_GPIO_Get(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	return (GPIOx->IDR & (0x1 << Pinx));
}

void Bayonet_GPIO_Set(GPIO_TypeDef *GPIOx, uint8_t Pinx, uint8_t state)
{
	if(state)
		GPIOx->ODR |= (0x1 << Pinx);
	else
		GPIOx->ODR &=~ (0x1 << Pinx);
}

void Bayonet_GPIO_Turn(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	if(GPIOx->ODR & (0x1 << Pinx))
		Bayonet_GPIO_Set(GPIOx, Pinx, 0);
	else
		Bayonet_GPIO_Set(GPIOx, Pinx, 1);
}
