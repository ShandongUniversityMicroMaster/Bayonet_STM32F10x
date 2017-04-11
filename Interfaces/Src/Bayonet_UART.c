#include "Bayonet_UART.h"
#include <stdio.h>
#include "Bayonet_NVIC.h"
#include "Bayonet_RCC.h"
#include "Bayonet_LED.h"
#include "Bayonet_Delay.h"

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 

void AssertFailed(char *str)
{
	Bayonet_LED_Init(Bayonet_LED0 | Bayonet_LED1 | Bayonet_LED2 | Bayonet_LED3);
	while(1)
	{
		Bayonet_Delay_Ms(100);
		printf("Assert Failed!:%s\r\n", str);
		Bayonet_LED_Turn(Bayonet_LED0 | Bayonet_LED1 | Bayonet_LED2 | Bayonet_LED3);
	}
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
	
	Bayonet_NVIC_Init(channel, PrePriority, SubPriority);
}

void Bayonet_UART_Init(USART_TypeDef *USARTx, u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
  mantissa<<=4;
	mantissa+=fraction; 
	
	if(USARTx == USART1)
	{
		/*  CLOCK  */
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		/*   GPIO Port Configuration   */
		GPIOA->CRH &=~ (GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10);  //坑爹的运算符优先级
		GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1;
		/*  Reset USART Port  */
		RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_USART1RST;
	}
	else if(USARTx == USART2)
	{
		/*   CLOCK   */
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		/*   GPIO Port Configuration   */
		GPIOA->CRL &=~ (GPIO_CRL_MODE2 | GPIO_CRL_CNF2 | GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
		GPIOA->CRL |= GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF3_1;
		/*  Reset USART Port  */
		RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
		RCC->APB1RSTR &=~ RCC_APB1RSTR_USART2RST;
	}
	else if(USARTx == USART3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else
	{
		AssertFailed("USART port not exist.\r\n");
	}
	
 	USARTx->BRR=mantissa;
	USARTx->CR1 |= USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
  UART_NVIC_Configuration(USARTx, 0, 0);
}

void UART_Put_Char(unsigned char DataToSend)
{
	//U1TxBuffer[U1count++] = DataToSend;  
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  
}

/*u8 UART_Get_Char(void)
{
	while (!(USART1->SR & USART_FLAG_RXNE));
	return(USART_ReceiveData(USART1));
}*/

void UART_Put_String(unsigned char *Str)
{
	//判断Str指向的数据是否有效.
	while(*Str){
	//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
	if(*Str=='\r')UART_Put_Char(0x0d);
		else if(*Str=='\n')UART_Put_Char(0x0a);
			else UART_Put_Char(*Str);
	//等待发送完成.
  	//while (!(USART1->SR & USART_FLAG_TXE));
	//指针++ 指向下一个字节.
	Str++;
	}
}

void Bayonet_UART_SendBuff(USART_TypeDef *USARTx, uint8_t *buff, uint16_t count)
{
	uint16_t i = 0;
	for(i = 0; i < count; i++)
	{
		while(!(USARTx->SR & USART_SR_TC));
		USARTx->DR = *buff;
		buff++;
	}
}

void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_TXE)
	{
		USART1->SR &=~ USART_SR_TXE;
	}
	else if(USART1->SR & USART_SR_RXNE)
	{
		USART1->SR &=~ USART_SR_RXNE;
	}
}


void DEBUG_PRINTLN(unsigned char *Str)
  {
	  UART_Put_String(Str);  //通过USART1 发送调试信息
	}
