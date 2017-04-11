#ifndef __Bayonet_RCC_H
#define __Bayonet_RCC_H

#include "stm32f10x.h"

//APB2 Periph.
#define Bayonet_RCC_AFIO 			0x00000000
#define Bayonet_RCC_GPIOA			0x00000001
#define Bayonet_RCC_GPIOB			0x00000002
#define Bayonet_RCC_GPIOC			0x00000003
#define Bayonet_RCC_GPIOD			0x00000004
#define Bayonet_RCC_GPIOE			0x00000005
#define Bayonet_RCC_ADC1			0x00000006
#define Bayonet_RCC_ADC2			0x00000007
#define Bayonet_RCC_TIM1			0x00000008
#define Bayonet_RCC_SPI1			0x00000009
#define Bayonet_RCC_UART1			0x0000000A
#define Bayonet_RCC_TIM8			0x00000010

//AHB Periph.
#define Bayonet_RCC_DMA1			0x0000000B
#define Bayonet_RCC_DMA2			0x0000000C
#define Bayonet_RCC_SRAM			0x0000000D
#define Bayonet_RCC_FLITF			0x0000000E
#define Bayonet_RCC_CRC				0x0000000F
//#define Bayonet_RCC_OTGFS			0x00000010
//#define Bayonet_RCC_ETHMAC		0x00000020
//#define Bayonet_RCC_ETHMACTX 	0x00000030
//#define Bayonet_RCC_ETHMACRX 	0x00000040

//APB1 Periph.
#define Bayonet_RCC_TIM2			0x00000050
#define Bayonet_RCC_TIM3			0x00000060
#define Bayonet_RCC_TIM4			0x00000070
#define Bayonet_RCC_TIM5			0x00000080
#define Bayonet_RCC_TIM6			0x00000090
#define Bayonet_RCC_TIM7			0x000000A0
#define Bayonet_RCC_WWDG			0x000000B0
#define Bayonet_RCC_SPI2			0x000000C0
#define Bayonet_RCC_SPI3			0x000000D0
#define Bayonet_RCC_UART2			0x000000E0
#define Bayonet_RCC_UART3			0x000000F0
#define Bayonet_RCC_UART4			0x00000100
#define Bayonet_RCC_UART5			0x00000200
#define Bayonet_RCC_I2C1			0x00000300
#define Bayonet_RCC_I2C2			0x00000400
#define Bayonet_RCC_CAN1			0x00000401
//#define Bayonet_RCC_CAN2			0x00000402
#define Bayonet_RCC_BKP				0x00000403
#define Bayonet_RCC_PWR				0x00000404
#define Bayonet_RCC_DAC				0x00000405

void Bayonet_RCC_Active(uint32_t device);

#endif
