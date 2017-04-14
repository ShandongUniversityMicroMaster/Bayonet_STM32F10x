#ifndef __Bayonet_RCC_H
#define __Bayonet_RCC_H

#include "stm32f10x.h"

typedef enum{
	//APB2 Periph.
	Bayonet_RCC_AFIO, 			
	Bayonet_RCC_GPIOA,			
	Bayonet_RCC_GPIOB,			
	Bayonet_RCC_GPIOC,			
	Bayonet_RCC_GPIOD,			
	Bayonet_RCC_GPIOE,			
	Bayonet_RCC_ADC1,			
	Bayonet_RCC_ADC2,			
	Bayonet_RCC_TIM1,			
	Bayonet_RCC_SPI1,		
	Bayonet_RCC_UART1,			
	Bayonet_RCC_TIM8,			

	//AHB Periph.
	Bayonet_RCC_DMA1,			
	Bayonet_RCC_DMA2,			
	Bayonet_RCC_SRAM,			
	Bayonet_RCC_FLITF,		
	Bayonet_RCC_CRC,				
	//Bayonet_RCC_OTGFS			
	//Bayonet_RCC_ETHMAC		
	//Bayonet_RCC_ETHMACTX 	
	//Bayonet_RCC_ETHMACRX 	

	//APB1 Periph.
	Bayonet_RCC_TIM2,			
	Bayonet_RCC_TIM3,			
	Bayonet_RCC_TIM4,			
	Bayonet_RCC_TIM5,			
	Bayonet_RCC_TIM6,			
	Bayonet_RCC_TIM7,			
	Bayonet_RCC_WWDG,		
	Bayonet_RCC_SPI2,			
	Bayonet_RCC_SPI3,		
	Bayonet_RCC_UART2,			
	Bayonet_RCC_UART3,			
	Bayonet_RCC_UART4,			
	Bayonet_RCC_UART5,			
	Bayonet_RCC_I2C1,			
	Bayonet_RCC_I2C2,			
	Bayonet_RCC_CAN1,			
	//Bayonet_RCC_CAN2			
	Bayonet_RCC_BKP,				
	Bayonet_RCC_PWR,				
	Bayonet_RCC_DAC			
}Bayonet_RCC;

void Bayonet_RCC_Active(Bayonet_RCC device);

#endif
