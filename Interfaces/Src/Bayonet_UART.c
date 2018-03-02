/**
	********************************************************************************
	* 
	* MIT License (MIT)
	* 
	* Copyright (c) 2017 Shandong University at Weihai Î¼Master team
	* @email songqiang.1304521@163.com
	* @github https://github.com/ShandongUniversityMicroMaster/Bayonet_STM32F10x
	*
	* All rights reserved. 
	* 
	* Permission is hereby granted, free of charge, to any person obtaining a copy
	* of this software and associated documentation files (the "Software"), to deal
	* in the Software without restriction, including without limitation the rights
	* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	* copies of the Software, and to permit persons to whom the Software is
	* furnished to do so, subject to the following conditions:
	* 
  ********************************************************************************
	* The above copyright notice and this permission notice shall be included in all
	* copies or substantial portions of the Software.
	* 
	********************************************************************************
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	* SOFTWARE.
	*
	********************************************************************************
	*/
	
#include "Bayonet_UART.h"
#include <stdio.h>
#include <stdbool.h>
#include "Bayonet_NVIC.h"
#include "Bayonet_RCC.h"
#include "Bayonet_Delay.h"

bool Bayonet_UART_isInit[5] = {false};

//#pragma import(__use_no_semihosting)
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
	while(!(USART2->SR & USART_SR_TC));
	USART2->DR = (uint8_t) ch;
	return ch;
}

/**
  * @brief  Assertion failed and waiting for DBG. 
  * @param  str: error message. 
  * @param  file: source file. 
  * @param  line: line number of code. 
  * @retval Index of the port. 
  */
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

/**
  * @brief  Translating UART port to index. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @retval Index of the port. 
  */
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

/**
  * @brief  Initializing NVIC channel of the specific UART. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @param  prePriority: prePriority for interrupt. 
  * @param  subPriority: subPriority for interrupt. 
  * @retval None
  */
void UART_NVIC_Configuration(USART_TypeDef *USARTx, uint8_t PrePriority, uint8_t SubPriority)
{
	uint8_t channel;
	
	if(USARTx == USART1)
		channel = USART1_IRQn;
	else if(USARTx == USART2)
		channel = USART2_IRQn;
	else if(USARTx == USART3)
		channel = USART3_IRQn;
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
	else if(USARTx == UART4)
		channel = UART4_IRQn;
	else if(USARTx == UART5)
		channel = UART5_IRQn;
#endif
	
	Bayonet_NVIC_Init(channel, PrePriority, SubPriority);
}

/**
  * @brief  Initializing the specific UART. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @param  baudrate: baudrate. 
  * @retval None
  */
void Bayonet_UART_Init(USART_TypeDef *USARTx, uint32_t baudrate)
{
	float temp;
	uint16_t mantissa;
	uint16_t fraction;
	RCC_ClocksTypeDef Clocks;
	Bayonet_RCC_GetClocksFreq(&Clocks);
	
	/*   Only the clock of USART1 derives from PCLK2.   */
	if(USARTx == USART1)
		temp = (float)(Clocks.PCLK2_Frequency)/(baudrate*16.0);
	else
		temp = (float)(Clocks.PCLK1_Frequency)/(baudrate*16.0);
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
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
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
#endif
	else
	{
		AssertFailed("USART port not exist.\r\n", __FILE__, __LINE__);
	}
	
 	USARTx->BRR=mantissa;
	USARTx->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	Bayonet_UART_isInit[Bayonet_UART_GetIndex(USARTx)] = true;
}

/**
  * @brief  Enable transmission complete interrupt of the specific UART. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @param  prePriority: prePriority for interrupt. 
  * @param  subPriority: subPriority for interrupt. 
  * @retval None
  */
void Bayonet_UART_EnableInterrupt_TC(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority)
{
	if(!Bayonet_UART_isInit[Bayonet_UART_GetIndex(USARTx)])
		AssertFailed("The specific UART port has not been initialized. ", __FILE__, __LINE__);
	
	USARTx->CR1 |= USART_CR1_TCIE;
	UART_NVIC_Configuration(USARTx, prePriority, subPriority);
}

/*****************************************************
	*
	*		Interrupt Request Handler should be like below: 
	*
	*		<UART Index>  -->  port index of your uart. 
	*
	****************************************************
	*
	*	for USART 1-3:
	*
		void USART<UART_Index>_IRQHandler()
		{
			if(USART<UART Index>->SR & USART_SR_TC)
			{
				//Your code. 
				USART<UART Index>->DR = data; //Put next data to send. 
			}
		}
	****************************************************
	*	for UART 4-5:
	*
		void UART<UART Index>_IRQHandler()
		{
			if(UART<UART Index>->SR & USART_SR_TC)
			{
				//Your code. 
				UART<UART Index>->DR = data; //Put next data to send. 
			}
		}
	*
******************************************************/

/**
  * @brief  Enable receive register not empty interrupt of the specific UART. 
  * @param  USARTx: where x can be (1..6) to select the peripheral.
  * @param  prePriority: prePriority for interrupt. 
  * @param  subPriority: subPriority for interrupt. 
  * @retval None
  */
void Bayonet_UART_EnableInterrupt_RXNE(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority)
{
	if(!Bayonet_UART_isInit[Bayonet_UART_GetIndex(USARTx)])
		AssertFailed("The specific UART port has not been initialized. ", __FILE__, __LINE__);
	
	USARTx->CR1 |= USART_CR1_RXNEIE;
	UART_NVIC_Configuration(USARTx, prePriority, subPriority);
}

/*****************************************************
	*
	*		Interrupt Request Handler should be like below: 
	*
	*		<UART Index>  -->  port index of your uart. 
	*
	****************************************************
	*
	*	for USART 1-3:
	*
		void USART<UART_Index>_IRQHandler()
		{
			if(USART<UART Index>->SR & USART_SR_RXNE)
			{
				data = USART<UART Index>->DR;; //Put next data to send. 
			}
		}
	****************************************************
	*	for UART 4-5:
	*
		void UART<UART Index>_IRQHandler()
		{
			if(UART<UART Index>->SR & USART_SR_RXNE)
			{
				data = UART<UART Index>->DR;; //Put next data to send. 
			}
		}
	*
******************************************************/

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
	if(!Bayonet_UART_isInit[Bayonet_UART_GetIndex(USARTx)])
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
	if(!Bayonet_UART_isInit[Bayonet_UART_GetIndex(USARTx)])
		AssertFailed("Port not Initialized. ", __FILE__, __LINE__); 
#endif
	while(*str != '\0')
	{
		while(!(USARTx->SR & USART_SR_TC));
		USARTx->DR = *str;
		str++;
	}
}
