#include "Bayonet_ADC.h"
#include "Bayonet_UART.h"
#include "Bayonet_DMA.h"

uint8_t isInit[16][3] = {0};
uint32_t tableSequence[3][16] = {0};
uint32_t tableMode[3] = {0};

uint32_t ADC_Buff[3][20] = {0};

/**
  * @brief  Configuring clock and IO.
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral.
  * @param  ADC_CHx: where x can be (0..15) to select the input channel.
  * @retval None
  */
void Bayonet_ADC_CLOCK_IO_Init(ADC_TypeDef *ADCx, uint32_t ADC_CHx)
{
	if(ADC_CHx == Bayonet_ADC_CH0)	//PA0
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	}
	if(ADC_CHx == Bayonet_ADC_CH1)	//PA1
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	}
	if(ADC_CHx == Bayonet_ADC_CH2)	//PA2
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
	}
	if(ADC_CHx == Bayonet_ADC_CH3)	//PA3
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
	}
	if(ADC_CHx == Bayonet_ADC_CH4)
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PA4
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
		}
		else  //PF6
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
		}
	}
	if(ADC_CHx == Bayonet_ADC_CH5)
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PA5
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
		}
		else  //PF7
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRL &=~ (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
		}
	}
	if(ADC_CHx == Bayonet_ADC_CH6)
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PA6
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOF->CRL &=~ (GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
		}
		else  //PF8
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRH &=~ (GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
		}
	}
	if(ADC_CHx == Bayonet_ADC_CH7)
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PA7
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
		}
		else  //PF9
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRH &=~ (GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
		}
	}
	if(ADC_CHx == Bayonet_ADC_CH8)
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PB0
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
		}
		else  //PF10
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
			GPIOF->CRH &=~ (GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
		}
	}
	if(ADC_CHx == Bayonet_ADC_CH9)
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PB1
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
		}
		else
			AssertFailed("...", __FILE__, __LINE__);
	}
	if(ADC_CHx == Bayonet_ADC_CH10)	//PC0
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	}
	if(ADC_CHx == Bayonet_ADC_CH11)	//PC1
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	}
	if(ADC_CHx == Bayonet_ADC_CH12)	//PC2
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
	}
	if(ADC_CHx == Bayonet_ADC_CH13)	//PC3
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOA->CRL &=~ (GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
	}
	if(ADC_CHx == Bayonet_ADC_CH14)	//PC4
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PA4
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
		}
		else
			AssertFailed("Channel not exist...", __FILE__, __LINE__);
	}
	if(ADC_CHx == Bayonet_ADC_CH15)	//PC5
	{
		if(ADCx == ADC1 || ADCx == ADC2) //PA4
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
			GPIOA->CRL &=~ (GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
		}
		else
			AssertFailed("Channel not exist...", __FILE__, __LINE__);
	}
	
	if(ADCx == ADC1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		RCC->APB2RSTR |= RCC_APB2RSTR_ADC1RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_ADC1RST;
		isInit[ADC_CHx][0] = 1;
	}
	else if(ADCx == ADC2)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
		RCC->APB2RSTR |= RCC_APB2RSTR_ADC2RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_ADC2RST;
		isInit[ADC_CHx][1] = 1;
	}
	else if(ADCx == ADC3)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
		RCC->APB2RSTR |= RCC_APB2RSTR_ADC3RST;
		RCC->APB2RSTR &=~ RCC_APB2RSTR_ADC3RST;
		isInit[ADC_CHx][2] = 1;
	}
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
void Bayonet_ADC_Independent_Init(ADC_TypeDef *ADCx, uint32_t ADC_CHx)
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
void Bayonet_ADC_SetRegularSequence(ADC_TypeDef *ADCx, uint8_t Length, uint32_t ADC_CHxs[])
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

void Bayonet_ADC_IM_Init(ADC_TypeDef *ADCx, uint8_t SequenceLength, uint32_t ADC_CHxs[], uint32_t SampleTime)
{
	uint8_t i;
	
	if(ADCx == ADC1)
		Bayonet_DMA_P2M_Init(DMA1, DMA1_Channel1, (uint32_t)&ADC1->DR, (uint32_t)ADC_Buff[0], Bayonet_DMA_DataWidth_32bit, SequenceLength);
	else if(ADCx == ADC2)
		AssertFailed("Peripheral ADC2 can not apply an independent DMA channel, which must be co-initialized with ADC1.", __FILE__, __LINE__);
	else if(ADCx == ADC3)
		Bayonet_DMA_P2M_Init(DMA2, DMA2_Channel5, (uint32_t)&ADC3->DR, (uint32_t)ADC_Buff[2], Bayonet_DMA_DataWidth_32bit, SequenceLength);
	else
		AssertFailed("ADC channel not exist.", __FILE__, __LINE__);
	
	for(i = 0;i < SequenceLength; i++)
	{
		Bayonet_ADC_CLOCK_IO_Init(ADCx, ADC_CHxs[i]);
		if(ADC_CHxs[i] < Bayonet_ADC_CH10)
			ADCx->SMPR2 |= SampleTime << (3*ADC_CHxs[i]);
		else
			ADCx->SMPR1 |= SampleTime << (3*(ADC_CHxs[i] - Bayonet_ADC_CH10));
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
  * @brief  Gets the ADC result of channel ADC_CHx of ADCx peripheral in independent mode. 
  * @param  ADCx: where x can be (1..3) to select the ADC peripheral. 
  * @param  ADC_CHx: where x can be (0..15) to select the input channel. 
  * @retval The ADC value of channel ADC_CHx of ADCx peripheral. 
  */
u16 Bayonet_ADC_OneTime(ADC_TypeDef *ADCx, uint32_t ADC_CHx)
{
#ifdef BAYONET_ADC_ASSERT
	if(ADC_CHx > Bayonet_ADC_CH15)
		AssertFailed("ADC Channel not exist...", __FILE__, __LINE__);
	if(ADCx == ADC1)
	{
		if(!isInit[ADC_CHx][0])
			AssertFailed("ADC Channel not initialized...", __FILE__, __LINE__);
	}
	else if(ADCx == ADC2)
	{
		if(!isInit[ADC_CHx][1])
			AssertFailed("ADC Channel not initialized...", __FILE__, __LINE__);
	}
	else if(ADCx == ADC3)
	{
		if(!isInit[ADC_CHx][2])
			AssertFailed("ADC Channel not initialized...", __FILE__, __LINE__);
	}
	else
		AssertFailed("ADC Channel not exist...", __FILE__, __LINE__);
#endif
	
	Bayonet_ADC_SetRegularSequence(ADCx, 1, &ADC_CHx);
	ADCx->CR2 |= ADC_CR2_SWSTART;
	while(!(ADCx->SR & ADC_SR_EOC));
	return ADCx->DR;	
}

