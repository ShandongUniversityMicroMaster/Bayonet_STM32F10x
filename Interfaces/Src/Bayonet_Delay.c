#include "Bayonet_Delay.h"
#include "Bayonet_UART.h"
#include "Bayonet_RCC.h"
#include "stdbool.h"

static u8  fac_us=0;
static u16 fac_ms=0;

bool isInit = false;

/**
  * @brief  Initializing systick for percise delay. 
  * @param  SYSCLK: highest clock frequency in your controller. 
  * @retval None
  */
void Bayonet_Delay_Init(void)
{
	RCC_ClocksTypeDef RCC_ClocksStructure;
	Bayonet_RCC_GetClocksFreq(&RCC_ClocksStructure);
	SysTick->CTRL &=~ SysTick_CTRL_CLKSOURCE;	//External clock. 
	fac_us = (RCC_ClocksStructure.SYSCLK_Frequency / 1000000) >> 3;
	fac_ms = (uint16_t)fac_us * 1000;
	isInit = true;
}

/**
  * @brief  Delay nms milliseconds. 
  * @param  nms: how many milliseconds to delay. 
  * @retval None
  */
void Bayonet_Delay_Ms(uint16_t nms)
{
#ifdef Bayonet_Assert
	if(isInit == false)
		AssertFailed("Delay module not initialized. Function Bayonet_Delay_Us"); 
#endif
	uint32_t load = 0;
	uint32_t temp;
	while(nms)
	{
		if(nms > 1864)
		{
			load = 1864;
			nms -= 1864;
		}
		else
		{
			load = nms;
			nms = 0;
		}
		SysTick->LOAD = (uint32_t)load * fac_ms;
		SysTick->VAL = 0x00;
		SysTick->CTRL = SysTick_CTRL_ENABLE;
		do
		{
			temp = SysTick->CTRL; //CTRL may change after every cycle, put it in a buffer. 
		}
		while(temp&SysTick_CTRL_ENABLE && !(temp&SysTick_CTRL_COUNTFLAG));
		SysTick->CTRL=0x00;
		SysTick->VAL =0X00; 
	}
}   
	    								   
/**
  * @brief  Delay nus microseconds. 
  * @param  nms: how many microseconds to delay. 
  * @retval None
  */
void Bayonet_Delay_Us(uint16_t nus)
{
	uint32_t load = 0, temp = 0;
#ifdef Bayonet_Assert
	if(isInit == false)
		AssertFailed("Delay module not initialized. Function Bayonet_Delay_Us()"); 
#endif
	while(nus)
	{
		if(nus > 1864)
		{
			load = 1864;
			nus -= 1864;
		}
		else
		{
			load = nus;
			nus = 0;
		}
		SysTick->LOAD = load * fac_us;
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
}
