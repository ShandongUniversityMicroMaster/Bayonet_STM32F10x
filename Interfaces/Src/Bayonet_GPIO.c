#include "Bayonet_GPIO.h"
#include "Bayonet_UART.h"
#include <math.h>

//All GPIO port mode will be stored in here. 
uint8_t portMode[6][16];

/**
  * @brief  Translating port name to number. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @retval Port index. 
  */
uint8_t Bayonet_GetPortIndex(GPIO_TypeDef *GPIOx)
{
	if(GPIOx == GPIOA)
		return 0;
	else if(GPIOx == GPIOB)
		return 1;
	else if(GPIOx == GPIOC)
		return 2;
	else if(GPIOx == GPIOD)
		return 3;
	else if(GPIOx == GPIOE)
		return 4;
	else
		AssertFailed("Port not exist. Bayonet_GetPortIndex. ");
	
	return 255;
}

/**
  * @brief  Checking if the port is in right mode. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel.
  * @retval None
  */
void Bayonet_AssertInputPort(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	uint8_t mode = portMode[Bayonet_GetPortIndex(GPIOx)][Pinx];
	if(mode > 3)
		AssertFailed("This IO port is not in input mode. function: Bayonet_GPIO_Get");
}

/**
  * @brief  Checking if the port is in right mode. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel.
  * @retval None
  */
void Bayonet_AssertOutputPort(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
		uint8_t mode = portMode[Bayonet_GetPortIndex(GPIOx)][Pinx];
		if(mode < 4)
			AssertFailed("This IO port is not in output mode. function: Bayonet_GPIO_Set"); 
}

/**
  * @brief  Configuring GPIO IO port with desired mode. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel.
  * @param  Mode: GPIO mode, defined in Bayonet_GPIO_Mode enumeration. 
  * @retval None
  */
void Bayonet_GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t Pinx, Bayonet_GPIO_Mode Mode)
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
	
	if(Mode == Bayonet_GPIO_MODE_GPIA)
		config = 0x00;
	else if(Mode == Bayonet_GPIO_MODE_GPIF)
		config = 0x04;
	else if(Mode == Bayonet_GPIO_MODE_GPIU)
	{
		config = 0x08;
		GPIOx->ODR |= (1 << Pinx);
	}
	else if(Mode == Bayonet_GPIO_MODE_GPID)
	{
		config = 0x08;
		GPIOx->ODR &=~ (1 << Pinx);
	}
	else if(Mode == Bayonet_GPIO_MODE_GPOGPP)
		config = 0x03;
	else if(Mode == Bayonet_GPIO_MODE_GPOGOD)
		config = 0x07;
	else if(Mode == Bayonet_GPIO_MODE_GPOAPP)
		config = 0x0B;
	else if(Mode == Bayonet_GPIO_MODE_GPOAOD)
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
	#ifdef Bayonet_Assert
		portMode[Bayonet_GetPortIndex][Pinx] = Mode;
	#endif
}

/**
  * @brief  Get the voltage level of specific port. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel. 
  * @retval 0 or 1, representing the voltage level of the port. 
  */
uint8_t Bayonet_GPIO_Get(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	#ifdef Bayonet_Assert
		Bayonet_AssertInputPort(GPIOx, Pinx);
	#endif
	return (GPIOx->IDR & (0x1 << Pinx));
}

/**
  * @brief  Set the output voltage level of specific port. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel. 
  * @param  state: state to set. 
  * @retval None. 
  */
void Bayonet_GPIO_Set(GPIO_TypeDef *GPIOx, uint8_t Pinx, uint8_t state)
{
	#ifdef Bayonet_Assert
		Bayonet_AssertOutputPort(GPIOx, Pinx);
	#endif
	if(state)
		GPIOx->ODR |= (0x1 << Pinx);
	else
		GPIOx->ODR &=~ (0x1 << Pinx);
}

/**
  * @brief  Turn the output voltage level of specific port. 
  * @param  GPIOx: where x can be (A..F) to select the GPIO port.
  * @param  Pinx: where x can be (0..15) to select the port channel. 
  * @retval None. 
  */
void Bayonet_GPIO_Turn(GPIO_TypeDef *GPIOx, uint8_t Pinx)
{
	#ifdef Bayonet_Assert
		Bayonet_AssertOutputPort(GPIOx, Pinx);
	#endif
	if(GPIOx->ODR & (0x1 << Pinx))
		Bayonet_GPIO_Set(GPIOx, Pinx, 0);
	else
		Bayonet_GPIO_Set(GPIOx, Pinx, 1);
}
