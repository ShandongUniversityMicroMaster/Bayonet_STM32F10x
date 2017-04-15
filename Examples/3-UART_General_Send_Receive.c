#include "stm32f10x.h"
#include "Bayonet_Delay.h"
#include "Bayonet_UART.h"
#include "Bayonet_NVIC.h"

uint8_t bufferSend[4] = {0};
uint8_t counterBuffer = 0;

int main(void)
{
	Bayonet_Delay_Init();
	//USART receive interrupt need NVIC to be grouped. 
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	//Initializing UART with a baudrate of 115200, 72 is Pclk frequency. PrePriority 0, subPriority 1. 
	Bayonet_UART_Init(USART1, 72, 115200, 0, 1); 
	while(1)
	{
		//Example shows how to send a protocal frame. 
		counterBuffer = 0;
		bufferSend[counterBuffer++] = 0x01;
		bufferSend[counterBuffer++] = 0x02;
		bufferSend[counterBuffer++] = 0x03;
		bufferSend[counterBuffer++] = 0x04;
		Bayonet_UART_SendBuff(USART1, bufferSend, 4);
		//End of sending frame.
		Bayonet_Delay_Ms(100);
		//Example shows how to send a string. 
		Bayonet_UART_SendString(USART1, "Hello world. ");
		//End of sending frame. 
		Bayonet_Delay_Ms(100);
	}
}

//Receiving interrupt handler. 
void USART1_IRQHandler()
{
	uint8_t temp;
	//Some stuff received. 
	if(USART1->SR & USART_SR_RXNE)
	{
		//Once DR is read, USART_SR_RXNE is cleared by hardware. 
		temp = USART1->DR;
	}
}
