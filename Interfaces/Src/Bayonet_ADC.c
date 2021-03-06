/**
	********************************************************************************
	* 
	* MIT License (MIT)
	* 
	* Copyright (c) 2017 Shandong University at Weihai μMaster team
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
	
#include "Bayonet_ADC.h"
#include "Bayonet_UART.h"
#include "Bayonet_DMA.h"
#include "Bayonet_NVIC.h"
#include <stdbool.h>

bool Bayonet_ADC_isInit[3][16] = {0};
Bayonet_ADC_Channel tableSequence[3][16] = {Bayonet_ADC_Channel_0};
uint32_t ADC_Buff[3][20] = {0};

/**
  * @brief  Configuring clock and IO.
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral.
  * @param  ADC_CHx: where x can be (0..15) to select the input channel.
  * @retval None
  */
void Bayonet_ADC_CLOCK_IO_Init(ADC_TypeDef *ADCx, Bayonet_ADC_Channel ADC_CHx)
{
	if(ADC_CHx == Bayonet_ADC_Channel_0)	//PA0
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_1)	//PA1
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_2)	//PA2
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_3)	//PA3
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_4)
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PA4
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
		}
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
		else  //PF6
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
		}
#endif
	}
	if(ADC_CHx == Bayonet_ADC_Channel_5)
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PA5
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
		}
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
		else  //PF7
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRL &=~ (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
		}
#endif
	}
	if(ADC_CHx == Bayonet_ADC_Channel_6)
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PA6
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOF->CRL &=~ (GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
		}
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
		else  //PF8
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRH &=~ (GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
		}
#endif
	}
	if(ADC_CHx == Bayonet_ADC_Channel_7)
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PA7
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
		}
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
		else  //PF9
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRH &=~ (GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
		}
#endif
	}
	if(ADC_CHx == Bayonet_ADC_Channel_8)
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PB0
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
		}
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
		else  //PF10
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRH &=~ (GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
		}
#endif
	}
	if(ADC_CHx == Bayonet_ADC_Channel_9)
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PB1
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
		}
		else
			AssertFailed("...", __FILE__, __LINE__);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_10)	//PC0
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOC->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_11)	//PC1
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOC->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_12)	//PC2
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOC->CRL &=~ (GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_13)	//PC3
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOC->CRL &=~ (GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_14)	//PC4
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2)
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
			GPIOC->CRL &=~ (GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
		}
		else
			AssertFailed("Channel not exist...", __FILE__, __LINE__);
	}
	if(ADC_CHx == Bayonet_ADC_Channel_15)	//PC5
	{
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
		if(ADCx == ADC1 || ADCx == ADC2) //PA4
#else
		if(ADCx == ADC1)
#endif
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
			GPIOC->CRL &=~ (GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
		}
		else
			AssertFailed("Channel not exist...", __FILE__, __LINE__);
	}
	
	if(ADCx == ADC1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		RCC->APB2RSTR |= RCC_APB2RSTR_ADC1RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_ADC1RST;
		Bayonet_ADC_isInit[0][ADC_CHx] = true;
	}
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
	else if(ADCx == ADC2)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
		RCC->APB2RSTR |= RCC_APB2RSTR_ADC2RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_ADC2RST;
		Bayonet_ADC_isInit[1][ADC_CHx] = true;
	}
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(ADCx == ADC3)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
		RCC->APB2RSTR |= RCC_APB2RSTR_ADC3RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_ADC3RST;
		Bayonet_ADC_isInit[2][ADC_CHx] = true;
	}
#endif
	else
	{
		AssertFailed("ADC Device not exist.", __FILE__, __LINE__);
	}
	
	RCC->CFGR &=~ RCC_CFGR_ADCPRE_DIV8;		
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;		//ADC Clock Prescale.
}

/**
  * @brief  Initializes the channel ADC_CHx of ADCx peripheral with independent mode.
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral.
  * @param  ADC_CHx: where x can be (0..15) to select the input channel.
  * @retval None
  */
void Bayonet_ADC_Init_OneTimeConversion(ADC_TypeDef *ADCx, Bayonet_ADC_Channel ADC_CHx)
{
	Bayonet_ADC_CLOCK_IO_Init(ADCx, ADC_CHx);
	
	ADCx->CR1 &=~ ADC_CR1_DUALMOD;  //Independent mode.
	ADCx->CR1 &=~ ADC_CR1_SCAN;			//None scan mode.
	ADCx->CR2 &=~ ADC_CR2_CONT;			//None continuous mode.
	ADCx->CR2 &=~ ADC_CR2_EXTSEL;		
	ADCx->CR2 |= ADC_CR2_EXTSEL;		//Software start, external triggers generated by software. 
	ADCx->CR2 |= ADC_CR2_EXTTRIG;		//External triggers on.
	ADCx->CR2 &=~ ADC_CR2_ALIGN;		//Right align mode.
	ADCx->SQR1 &=~ ADC_SQR1_L;			//Only one conversion in regular sequence.
	ADCx->SMPR2 &=~ ADC_SMPR2_SMP1;
	ADCx->SMPR2 |= ADC_SMPR2_SMP1;	//Sample time. 
	ADCx->CR2 |= ADC_CR2_ADON;			//Turn AD peripheral.
	ADCx->CR2 |= ADC_CR2_RSTCAL;
	while(ADCx->CR2 & ADC_CR2_RSTCAL);
	ADCx->CR2 |= ADC_CR2_CAL;
	while(ADCx->CR2 & ADC_CR2_CAL);
}

/**
  * @brief  Configures regular sequence with the first Length items in ADC_CHxs[] of ADCx.
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral.
  * @param  Length: length of regular sequence.
  * @param  ADC_CHxs: the buffer that regular sequence stores in.
  * @retval None
  */
void Bayonet_ADC_SetRegularSequence(ADC_TypeDef *ADCx, uint8_t Length, Bayonet_ADC_Channel ADC_CHxs[])
{
	uint8_t i = 0;
	uint8_t count[3] = {0};
	for(i = 0;i < Length; i++)
	{
		if(i < 6)
		{
			ADCx->SQR3 |= ADC_CHxs[i] << (count[0] * 5);
			count[0]++;
		}
		else if(i < 12)
		{
			ADCx->SQR2 |= ADC_CHxs[i] << (count[1] * 5);
			count[1]++;
		}
		else
		{
			ADCx->SQR1 |= ADC_CHxs[i] << (count[2] * 5);
			count[2]++;
		}
	}
	ADCx->SQR1 |= (Length - 1) << 20;  //0000 for 1 conversion, 
}

/**
  * @brief  Initializes the channel ADC_CHx of ADCx peripheral with independent multichannel mode.
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral.
  * @param  SequenceLength: The length of regular sequence.
  * @param  ADC_CHxs[]: Regular sequence channels.
  * @param  SampleTime: Sample time for all regular channels.
  * @retval None
  */
void Bayonet_ADC_Init_ContinuousConversion(ADC_TypeDef *ADCx, uint8_t SequenceLength, Bayonet_ADC_Channel ADC_CHxs[], Bayonet_ADC_SampleTime SampleTime)
{
	uint8_t i;
	
	if(ADCx == ADC1)
		Bayonet_DMA_P2M_Init(DMA1, DMA1_Channel1, (uint32_t)&ADC1->DR, (uint32_t)ADC_Buff[0], Bayonet_DMA_DataWidth_32bit, SequenceLength);
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
	else if(ADCx == ADC2)
		AssertFailed("Peripheral ADC2 can not apply an independent DMA channel, which must be co-initialized with ADC1.", __FILE__, __LINE__);
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(ADCx == ADC3)
		Bayonet_DMA_P2M_Init(DMA2, DMA2_Channel5, (uint32_t)&ADC3->DR, (uint32_t)ADC_Buff[2], Bayonet_DMA_DataWidth_32bit, SequenceLength);
#endif
	else
		AssertFailed("ADC channel not exist.", __FILE__, __LINE__);
	
	for(i = 0;i < SequenceLength; i++)
	{
		Bayonet_ADC_CLOCK_IO_Init(ADCx, ADC_CHxs[i]);
	}
	
	for(i = 0;i < SequenceLength; i++)
	{
		if(ADC_CHxs[i] < Bayonet_ADC_Channel_10)
			ADCx->SMPR2 |= SampleTime << (3*ADC_CHxs[i]);
		else
			ADCx->SMPR1 |= SampleTime << (3*(ADC_CHxs[i] - Bayonet_ADC_Channel_10));
	}
	
	ADCx->CR1 &=~ ADC_CR1_DUALMOD;
	ADCx->CR1 |=	ADC_CR1_SCAN;
	ADCx->CR2 |=	ADC_CR2_CONT;
	ADCx->CR2 |=	ADC_CR2_DMA;
	ADCx->CR2 |= ADC_CR2_EXTSEL;		//Software start, external triggers generated by software. 
	ADCx->CR2 |= ADC_CR2_EXTTRIG;		//External triggers on.
	ADCx->CR2 &=~ ADC_CR2_ALIGN;		//Right align mode.
	Bayonet_ADC_SetRegularSequence(ADCx, SequenceLength, ADC_CHxs);
	//Sample time. 
	ADCx->CR2 |= ADC_CR2_ADON;			//Turn AD peripheral.
	ADCx->CR2 |= ADC_CR2_RSTCAL;
	while(ADCx->CR2 & ADC_CR2_RSTCAL);
	ADCx->CR2 |= ADC_CR2_CAL;
	while(ADCx->CR2 & ADC_CR2_CAL);
	ADCx->CR2 |= ADC_CR2_SWSTART;
}

/**
  * @brief  Enable End of Conversion interrupt of the specific ADC. 
  * @param  ADCx: where x can be (1..3) to select the peripheral.
  * @param  prePriority: prePriority for interrupt. 
  * @param  subPriority: subPriority for interrupt. 
  * @retval None
  */
void Bayonet_ADC_EnableInterrupt_EOC(ADC_TypeDef *ADCx, uint8_t prePriority, uint8_t subPriority)
{
	uint8_t i, sum = 0;
	for(i = 0; i < 16;i++)
		sum += Bayonet_ADC_isInit[Bayonet_NVIC_GetIRQChannel_ADC(ADCx)][i];
	if(!sum)
		AssertFailed("This ADC has no channel initialized. ", __FILE__, __LINE__);
	
	ADCx->CR1 |= ADC_CR1_EOCIE;
	Bayonet_NVIC_Init(Bayonet_NVIC_GetIRQChannel_ADC(ADCx), prePriority, subPriority);
}

/*****************************************************
	*
	*		Interrupt Request Handler should be like below: 
	*
	*		<ADC Index>  -->  port index of your ADC. 
	*
	****************************************************
	*
	*	for ADC 1-2:
	*
		void ADC1_2_IRQHandler()
		{
			if(ADC<ADC Index>->SR & ADC_SR_EOC)
			{
				//Tour code. 
				ADC<ADC Index>->SR &=~ ADC_SR_EOC;		//I am not sure if it will be cleared in continous conversion mode, clear it by sofrware to ensure. 
			}
		}
	****************************************************
	*	for ADC 3:
	*
		void ADC3_IRQHandler()
		{
			if(ADC3->SR & ADC_SR_EOC)
			{
				//Your code. 
				ADC3->SR &=~ ADC_SR_EOC;		//I am not sure if it will be cleared in continous conversion mode, clear it by sofrware to ensure. 
			}
		}
	*
******************************************************/

/**
  * @brief  Gets the ADC result of channel ADC_CHx of ADCx peripheral in independent mode. 
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral. 
  * @param  ADC_CHx: where x can be (0..15) to select the input channel. 
  * @retval The ADC value of channel ADC_CHx of ADCx peripheral. 
  */
u16 Bayonet_ADC_OneTime(ADC_TypeDef *ADCx, Bayonet_ADC_Channel ADC_CHx)
{
#ifdef BAYONET_ADC_ASSERT
	if(ADC_CHx > Bayonet_ADC_Channel_15)
		AssertFailed("ADC Channel not exist...", __FILE__, __LINE__);
	if(ADCx == ADC1)
	{
		if(!Bayonet_ADC_isInit[0][ADC_CHx])
			AssertFailed("ADC Channel not initialized...", __FILE__, __LINE__);
	}
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL)
	else if(ADCx == ADC2)
	{
		if(!Bayonet_ADC_isInit[1][ADC_CHx])
			AssertFailed("ADC Channel not initialized...", __FILE__, __LINE__);
	}
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(ADCx == ADC3)
	{
		if(!Bayonet_ADC_isInit[2][ADC_CHx])
			AssertFailed("ADC Channel not initialized...", __FILE__, __LINE__);
	}
#endif
	else
		AssertFailed("ADC Channel not exist...", __FILE__, __LINE__);
#endif
	
	Bayonet_ADC_SetRegularSequence(ADCx, 1, &ADC_CHx);
	ADCx->CR2 |= ADC_CR2_SWSTART;
	while(!(ADCx->SR & ADC_SR_EOC));
	return ADCx->DR;	
}
