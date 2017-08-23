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
	
#include "Bayonet_CRC.h"
#include "Bayonet_RCC.h"

/**
  * @brief  Initializing CRC device. 
  * @retval None. 
  */
void Bayonet_CRC_Init()
{
	Bayonet_RCC_Active(Bayonet_RCC_CRC);
}

/**
  * @brief  Resetting DR to 0xFFFFFFFF, but not effect the IDR. 
  * @retval None. 
  */
void Bayonet_CRC_Reset()
{
	CRC->CR |= CRC_CR_RESET;
}

/**
  * @brief  Calculate the cyclic reduncancy check value of the specific data with a polynomial of 0x4C11DB7. 
  * @param  data: data to calculate. 
  * @retval CRC result of the data. 
  */
uint32_t Bayonet_CRC_CalculateWord(uint32_t data)
{
	CRC->DR = data;
	return CRC->DR;			//Auto-blocking calculation for 4 AHB clocks. 
}

/**
  * @brief  Calculate the cyclic reduncancy check value of a buffer of data with a polynomial of 0x4C11DB7. 
  * @param  pBuffer: data buffer to calculate. 
  * @param  length: length of buffer. 
  * @retval CRC result of the data. 
  */
uint32_t Bayonet_CRC_CaculateBuffer(uint32_t* pBuffer, uint16_t length)
{
	uint16_t i;
	
	Bayonet_CRC_Reset();
	
	for(i = 0; i < length; i++)
		CRC->DR = *(pBuffer + i);
	
	return CRC->DR;
}
