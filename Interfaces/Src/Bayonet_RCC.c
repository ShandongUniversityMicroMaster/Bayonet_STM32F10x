#include "Bayonet_RCC.h"
#include "Bayonet_UART.h"

/**
  * @brief  RCC peripheral mapping. 
  * @param  GPIOx) where x can be (A..F) to select the GPIO port.
  * @retval None 
  */
void Bayonet_RCC_Active(Bayonet_RCC device)
{
		if(device == Bayonet_RCC_AFIO)
			RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		else if(device == Bayonet_RCC_GPIOA)
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		else if(Bayonet_RCC_GPIOB)
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		else if(Bayonet_RCC_GPIOC)
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		else if(Bayonet_RCC_GPIOD)
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
		else if(Bayonet_RCC_GPIOE)
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
		else if(Bayonet_RCC_ADC1)
			RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		else if(Bayonet_RCC_ADC2)
			RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
		else if(Bayonet_RCC_TIM1)
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		else if(Bayonet_RCC_SPI1)
			RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		else if(Bayonet_RCC_UART1)
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		else if(Bayonet_RCC_DMA1)
			RCC->AHBENR |= RCC_AHBENR_DMA1EN;
		else if(Bayonet_RCC_DMA2)
			RCC->AHBENR |= RCC_AHBENR_DMA2EN;
		else if(Bayonet_RCC_SRAM)
			RCC->AHBENR |= RCC_AHBENR_SRAMEN;
		else if(Bayonet_RCC_FLITF)
			RCC->AHBENR |= RCC_AHBENR_FLITFEN;
		else if(Bayonet_RCC_CRC)
			RCC->AHBENR |= RCC_AHBENR_CRCEN;
		else if(Bayonet_RCC_TIM2)
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		else if(Bayonet_RCC_TIM3)
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		else if(Bayonet_RCC_TIM4)
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		else if(Bayonet_RCC_TIM5)
			RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
		else if(Bayonet_RCC_TIM6)
			RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
		else if(Bayonet_RCC_TIM7)
			RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
		else if(Bayonet_RCC_WWDG)
			RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;
		else if(Bayonet_RCC_SPI2)
			RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
		else if(Bayonet_RCC_SPI3)
			RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
		else if(Bayonet_RCC_UART2)
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		else if(Bayonet_RCC_UART3)
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		else if(Bayonet_RCC_UART4)
			RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
		else if(Bayonet_RCC_UART5)
			RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
		else if(Bayonet_RCC_I2C1)
			RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		else if(Bayonet_RCC_I2C2)
			RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		else if(Bayonet_RCC_CAN1)
			RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
		else if(Bayonet_RCC_BKP)
			RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
		else if(Bayonet_RCC_PWR)
			RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		else if(Bayonet_RCC_DAC)
			RCC->APB1ENR |= RCC_APB1ENR_DACEN;
		else
			AssertFailed("Device not exit. Bayonet_RCC_Active");
}
