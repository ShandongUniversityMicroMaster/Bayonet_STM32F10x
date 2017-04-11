#include "Bayonet_Delay.h"
#include "Bayonet_UART.h"

static u8  fac_us=0;
static u16 fac_ms=0;

void Bayonet_Delay_Init(u8 SYSCLK)
{
	SysTick->CTRL &=~ SysTick_CTRL_CLKSOURCE;
	fac_us = SYSCLK >> 3;
	fac_ms = (uint16_t)fac_us * 1000;
}				

void Bayonet_Delay_Ms(uint16_t nms)
{	 		  	  
	u32 temp;
	if(nms > 1864)
		AssertFailed("Delay count over maximum...");
	SysTick->LOAD = (uint32_t)nms * fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL = SysTick_CTRL_ENABLE;
	do
	{
		temp = SysTick->CTRL;
	}
	while((temp&SysTick_CTRL_ENABLE)&&!(temp&SysTick_CTRL_COUNTFLAG));
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00; 
}   
	    								   
void Bayonet_Delay_Us(u32 nus)
{
	u32 temp;
	if(nus > 1864)
		AssertFailed("Delay count over maximum...");
	SysTick->LOAD = nus * fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL = SysTick_CTRL_ENABLE;
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp&SysTick_CTRL_ENABLE && !(temp&SysTick_CTRL_COUNTFLAG));
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}
