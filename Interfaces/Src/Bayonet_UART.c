#include "Bayonet_UART.h"
#include <stdio.h>
#include <stdbool.h>
#include "Bayonet_NVIC.h"
#include "Bayonet_RCC.h"
#include "Bayonet_Delay.h"

bool bayonetUsartIsInit[5] = {false};

#if 1
#pragma import(__use_no_semihosting)
struct __FILE 
{
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef¡¯ d in stdio.h. */ 
FILE __stdout;

void _sys_exit(int x) 
{ 
	x = x; 
}

int fputc(int ch, FILE *f)
{
	while((USART2->SR & USART_SR_TC) == 0);
	USART2->DR = (uint8_t) ch;
	return ch;
}
#endif 

void AssertFailed(char *str, char *file, int line)
{
	char strBuffer[200] = {0};
	while(1)
	{
		Bayonet_Delay_Ms(100);
		sprintf(strBuffer, "%s, file: %s, line: %d", str, file, line); 
		//printf("Assert Failed!:%s\r\n", str);
	}
}

uint8_t Bayonet_UART_GetIndex(USART_TypeDef *USARTx)
{
	if(USARTx == USART1)
		return 0;
	else if(USARTx == USART2)
		return 1;
	else if(USARTx == USART3)
		return 2;
	else if(USARTx == UART4)
		return 3;
	else if(USARTx == UART5)
		return 4;
	else
		return 255;
}

void UART_NVIC_Configuration(USART_TypeDef *USARTx, uint8_t PrePriority, uint8_t SubPriority)
{
	uint8_t channel;
	
	if(USARTx == USART1)
		channel = USART1_IRQn;
	else if(USARTx == USART2)
		channel = USART2_IRQn;
	else if(USARTx == USART3)
		channel = USART3_IRQn;
	else if(USARTx == UART4)
		channel = UART4_IRQn;
	else if(USARTx == UART5)
		channel = UART5_IRQn;
	
	Bayonet_NVIC_Init(channel, PrePriority, SubPriority);
}

void Bayonet_UART_Init(USART_TypeDef *USARTx, u32 pclk2,u32 bound, uint8_t prePriority, uint8_t subPriority)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float)(pclk2*1000000.0)/(bound*16.0);
	mantissa = temp;
	fraction = (temp-mantissa)*16;
  mantissa <<= 4;
	mantissa += fraction; 
	
	if(USARTx == USART1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRH &=~ (GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10); 
		GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1;
		RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_USART1RST;
	}
	else if(USARTx == USART2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_MODE2 | GPIO_CRL_CNF2 | GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
		GPIOA->CRL |= GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF3_1;
		RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
		RCC->APB1RSTR &=~ RCC_APB1RSTR_USART2RST;
	}
	else if(USARTx == USART3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		GPIOB->CRH &=~ (GPIO_CRH_MODE10 | GPIO_CRH_CNF10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
		GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1;
		RCC->APB1RSTR |= RCC_APB1RSTR_USART3RST;
		RCC->APB1RSTR &=~ RCC_APB1RSTR_USART3RST;
	}
	else if(USARTx == UART4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOC->CRH &=~ (GPIO_CRH_MODE10 | GPIO_CRH_CNF10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
		GPIOC->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1;
		RCC->APB1RSTR |= RCC_APB1RSTR_UART4RST;
		RCC->APB1RSTR &=~ RCC_APB1RSTR_UART4RST;
	}
	else if(USARTx == UART5)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
		GPIOC->CRH &=~ (GPIO_CRH_MODE12 | GPIO_CRH_CNF12);
		GPIOC->CRH |= GPIO_CRH_MODE12 | GPIO_CRH_CNF12_1;
		GPIOD->CRL &=~ (GPIO_CRL_MODE2 | GPIO_CRL_CNF2);  
		GPIOD->CRL |= GPIO_CRL_CNF2_1;
		RCC->APB1RSTR |= RCC_APB1RSTR_UART5RST;
		RCC->APB1RSTR &=~ RCC_APB1RSTR_UART5RST;
	}
	else
	{
		AssertFailed("USART port not exist.\r\n", __FILE__, __LINE__);
	}
	
 	USARTx->BRR=mantissa;
	USARTx->CR1 |= USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
  UART_NVIC_Configuration(USARTx, prePriority, subPriority);
	bayonetUsartIsInit[Bayonet_UART_GetIndex(USARTx)] = true;
}

/**
  * @brief  Sending buffer using USARTx. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @param  buff: pointing to the buffer to send. 
  * @param  count: the number of data we are going to send. 
  * @retval None
  */
void Bayonet_UART_SendBuff(USART_TypeDef *USARTx, uint8_t *buff, uint16_t count)
{
	uint16_t i = 0;
#ifdef Bayonet_Assert
	if(!bayonetUsartIsInit[Bayonet_UART_GetIndex(USARTx)])
		AssertFailed("Port not Initialized. ", __FILE__, __LINE__); 
#endif
	for(i = 0; i < count; i++)
	{
		while(!(USARTx->SR & USART_SR_TC));
		USARTx->DR = *buff;
		buff++;
	}
}

/**
  * @brief  Sending string using USARTx. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @param  str: pointing to the str to send.
  * @retval None
  */
void Bayonet_UART_SendString(USART_TypeDef *USARTx, char *str)
{
#ifdef Bayonet_Assert
	if(!bayonetUsartIsInit[Bayonet_UART_GetIndex(USARTx)])
		AssertFailed("Port not Initialized. ", __FILE__, __LINE__); 
#endif
	while(*str != '\0')
	{
		while(!(USARTx->SR & USART_SR_TC));
		USARTx->DR = *str;
		str++;
	}
}
