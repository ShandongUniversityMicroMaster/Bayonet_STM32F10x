#include "Bayonet_RCC.h"

void Bayonet_RCC_Active(uint32_t device)
{
	switch(device)
	{
		case Bayonet_RCC_AFIO:
			RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
			break;
		case Bayonet_RCC_GPIOA:
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			break;
		case Bayonet_RCC_GPIOB:
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
			break;
		case Bayonet_RCC_GPIOC:
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
			break;
		case Bayonet_RCC_GPIOD:
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
			break;
		case Bayonet_RCC_GPIOE:
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
			break;
		case Bayonet_RCC_ADC1:
			RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			break;
		case Bayonet_RCC_ADC2:
			RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
			break;
		case Bayonet_RCC_TIM1:
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			break;
		case Bayonet_RCC_SPI1:
			RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
			break;
		case Bayonet_RCC_UART1:
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			break;
		case Bayonet_RCC_DMA1:
			RCC->AHBENR |= RCC_AHBENR_DMA1EN;
			break;
		case Bayonet_RCC_DMA2:
			RCC->AHBENR |= RCC_AHBENR_DMA2EN;
			break;
		case Bayonet_RCC_SRAM:
			RCC->AHBENR |= RCC_AHBENR_SRAMEN;
			break;
		case Bayonet_RCC_FLITF:
			RCC->AHBENR |= RCC_AHBENR_FLITFEN;
			break;
		case Bayonet_RCC_CRC:
			RCC->AHBENR |= RCC_AHBENR_CRCEN;
			break;
		case Bayonet_RCC_TIM2:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			break;
		case Bayonet_RCC_TIM3:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			break;
		case Bayonet_RCC_TIM4:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			break;
		case Bayonet_RCC_TIM5:
			RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
			break;
		case Bayonet_RCC_TIM6:
			RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
			break;
		case Bayonet_RCC_TIM7:
			RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
			break;
		case Bayonet_RCC_WWDG:
			RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;
			break;
		case Bayonet_RCC_SPI2:
			RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
			break;
		case Bayonet_RCC_SPI3:
			RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
			break;
		case Bayonet_RCC_UART2:
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			break;
		case Bayonet_RCC_UART3:
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
			break;
		case Bayonet_RCC_UART4:
			RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
			break;
		case Bayonet_RCC_UART5:
			RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
			break;
		case Bayonet_RCC_I2C1:
			RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
			break;
		case Bayonet_RCC_I2C2:
			RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
			break;
		case Bayonet_RCC_CAN1:
			RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
			break;
		case Bayonet_RCC_BKP:
			RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
			break;
		case Bayonet_RCC_PWR:
			RCC->APB1ENR |= RCC_APB1ENR_PWREN;
			break;
		case Bayonet_RCC_DAC:
			RCC->APB1ENR |= RCC_APB1ENR_DACEN;
			break;
	}
}
