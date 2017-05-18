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
	
#include "Bayonet_RCC.h"
#include "Bayonet_UART.h"

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  * @note   The result of this function could be not correct when using 
  *         fractional value for HSE crystal.  
  * @retval None
  */
void Bayonet_RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

#ifdef  STM32F10X_CL
  uint32_t prediv1source = 0, prediv1factor = 0, prediv2factor = 0, pll2mull = 0;
#endif /* STM32F10X_CL */

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
  uint32_t prediv1factor = 0;
#endif
    
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
      
#ifndef STM32F10X_CL      
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
 #if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
       prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;
       /* HSE oscillator clock selected as PREDIV1 clock entry */
       RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE / prediv1factor) * pllmull; 
 #else
        /* HSE selected as PLL clock entry */
        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
        {/* HSE oscillator clock divided by 2 */
          RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE >> 1) * pllmull;
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = HSE_VALUE * pllmull;
        }
 #endif
      }
#else
      pllmull = pllmull >> 18;
      
      if (pllmull != 0x0D)
      {
         pllmull += 2;
      }
      else
      { /* PLL multiplication factor = PLL input clock * 6.5 */
        pllmull = 13 / 2; 
      }
            
      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {/* PREDIV1 selected as PLL clock entry */
        
        /* Get PREDIV1 clock source and division factor */
        prediv1source = RCC->CFGR2 & CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;
        
        if (prediv1source == 0)
        { /* HSE oscillator clock selected as PREDIV1 clock entry */
          RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE / prediv1factor) * pllmull;          
        }
        else
        {/* PLL2 clock selected as PREDIV1 clock entry */
          
          /* Get PREDIV2 division factor and PLL2 multiplication factor */
          prediv2factor = ((RCC->CFGR2 & CFGR2_PREDIV2) >> 4) + 1;
          pll2mull = ((RCC->CFGR2 & CFGR2_PLL2MUL) >> 8 ) + 2; 
          RCC_Clocks->SYSCLK_Frequency = (((HSE_VALUE / prediv2factor) * pll2mull) / prediv1factor) * pllmull;                         
        }
      }
#endif /* STM32F10X_CL */ 
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/**
  * @brief  RCC peripheral mapping. 
  * @param  GPIOx) where x can be (A..F) to select the GPIO port.
  * @retval Clock frequency of its bus. 
  */
uint32_t Bayonet_RCC_Active(Bayonet_RCC device)
{
	RCC_ClocksTypeDef Clock_Structure;
	Bayonet_RCC_GetClocksFreq(&Clock_Structure);
	
	if(device == Bayonet_RCC_AFIO)
	{
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_GPIOA)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_GPIOB)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_GPIOC)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_GPIOD)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
		return Clock_Structure.PCLK2_Frequency;
	}
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
	else if(device == Bayonet_RCC_GPIOE)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
		return Clock_Structure.PCLK2_Frequency;
	}
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(device == Bayonet_RCC_GPIOF)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_GPIOG)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPGEN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_TIM8)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_ADC3)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
		return Clock_Structure.PCLK2_Frequency;
	}
#endif
#ifdef STM32F10X_XL
	else if(device == Bayonet_RCC_TIM9)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_TIM10)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_TIM11)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
		return Clock_Structure.PCLK2_Frequency;
	}
#endif
	else if(device == Bayonet_RCC_ADC1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_ADC2)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_TIM1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_SPI1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_UART1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		return Clock_Structure.PCLK2_Frequency;
	}
	else if(device == Bayonet_RCC_DMA1)
	{
		RCC->AHBENR |= RCC_AHBENR_DMA1EN;
		return Clock_Structure.HCLK_Frequency;
	}
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL) || defined  (STM32F10X_HD_VL) || defined  (STM32F10X_XL)
	else if(device == Bayonet_RCC_DMA2)
	{
		RCC->AHBENR |= RCC_AHBENR_DMA2EN;
		return Clock_Structure.HCLK_Frequency;
	}
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
	else if(device == Bayonet_RCC_FSMC)
	{
		RCC->AHBENR |= RCC_AHBENR_FSMCEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_SDIO)
	{
		RCC->AHBENR |= RCC_AHBENR_SDIOEN;
		return Clock_Structure.HCLK_Frequency;
	}
#endif
#ifdef STM32F10X_CL
	else if(device == Bayonet_RCC_OTGFS)
	{
		RCC->AHBENR |= RCC_AHBENR_OTGFSEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_ETHMAC)
	{
		RCC->AHBENR |= RCC_AHBENR_ETHMACEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_ETHMACTX)
	{
		RCC->AHBENR |= RCC_AHBENR_ETHMACTXEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_ETHMACRX)
	{
		RCC->AHBENR |= RCC_AHBENR_ETHMACRXEN;
		return Clock_Structure.HCLK_Frequency;
	}
#endif
	else if(device == Bayonet_RCC_SRAM)
	{
		RCC->AHBENR |= RCC_AHBENR_SRAMEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_FLITF)
	{
		RCC->AHBENR |= RCC_AHBENR_FLITFEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_CRC)
	{
		RCC->AHBENR |= RCC_AHBENR_CRCEN;
		return Clock_Structure.HCLK_Frequency;
	}
	else if(device == Bayonet_RCC_TIM2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_WWDG)
	{
		RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;
		return Clock_Structure.PCLK1_Frequency;
	}
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
	else if(device == Bayonet_RCC_TIM4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_SPI2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_UART3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_I2C2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		return Clock_Structure.PCLK1_Frequency;
	}
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_MD) || defined  (STM32F10X_LD) || defined  (STM32F10X_XL)
	else if(device == Bayonet_RCC_USB)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USBEN;
		return Clock_Structure.PCLK1_Frequency;
	}
#endif
#if defined (STM32F10X_HD) || defined  (STM32F10X_CL)
	else if(device == Bayonet_RCC_TIM5)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_TIM6)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_TIM7)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_SPI3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_UART4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_UART5)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_DAC)
	{
		RCC->APB1ENR |= RCC_APB1ENR_DACEN;
		return Clock_Structure.PCLK1_Frequency;
	}
#endif
#ifdef STM32F10X_CL
	else if(device == Bayonet_RCC_CAN2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;
		return Clock_Structure.PCLK1_Frequency;
	}
#endif
	else if(device == Bayonet_RCC_UART2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_I2C1)
	{
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_CAN1)
	{
		RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_BKP)
	{
		RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else if(device == Bayonet_RCC_PWR)
	{
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		return Clock_Structure.PCLK1_Frequency;
	}
	else
		AssertFailed("Device not exit. ", __FILE__, __LINE__);
	
	return 1;
}
