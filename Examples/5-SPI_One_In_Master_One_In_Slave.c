#include "stm32f10x.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_SPI.h"

uint8_t data;

int main(void)
{
	Bayonet_Delay_Init();
	Bayonet_NVIC_SetGroup(Bayonet_NVIC_PriorityGroup_2);
	
	Bayonet_SPI_Init_Slave(SPI1, 1, 1);
	Bayonet_SPI_Init_Master(SPI2, 1);
	while(1)
	{
		data = Bayonet_SPI_ReadWriteByte(SPI2, 0xaa);
		Bayonet_Delay_Ms(1);
	}
}

void SPI1_IRQHandler()
{
	if(SPI1->SR & SPI_SR_RXNE)
	{
		data = SPI1->DR;
		SPI1->DR = 0x55;
	}
}
