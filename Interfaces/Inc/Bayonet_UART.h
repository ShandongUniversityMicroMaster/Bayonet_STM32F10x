#ifndef __BAYONET_UART_H_
#define __BAYONET_UART_H_

#include "stm32f10x.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

void UART_NVIC_Configuration(USART_TypeDef *USARTx, uint8_t prePriority, uint8_t subPriority);
void Bayonet_UART_Init(USART_TypeDef *USARTx, u32 pclk2,u32 bound, uint8_t prePriority, uint8_t subPriority);
void Bayonet_UART_SendBuff(USART_TypeDef *USARTx, uint8_t *buff, uint16_t count);
void UART_Put_Char(unsigned char DataToSend);
uint8_t UART_Get_Char(void);
void AssertFailed(char *str);
void Bayonet_UART_SendString(USART_TypeDef *USARTx, char *str);
#endif
