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
	
#include "Bayonet_Flash.h"
#include "Bayonet_UART.h"

uint16_t Bayonet_FLASH_Buffer[1024] = {0};

#ifdef Bayonet_Assert

/**
  * @brief  Check if the address using is legal. 
  * @param  address: address to check. 
  * @retval None. 
  */
void Bayonet_FLASH_CheckAddressValid(uint32_t address)
{
	if(address > 0x08000000 && address < 0x0807FFFF)
		return;
	
	AssertFailed("Using address is not in the range we can utilize. ", __FILE__, __LINE__);
}
#endif

/**
  * @brief  Read a buffer of halfword data from flash. 
  * @param  address: address to read. 
  * @param  buffer: pointer to the start of buffer. 
  * @param  count: length of buffer. 
  * @retval None. 
  */
void Bayonet_FLASH_ReadBuffer(uint32_t address, uint16_t *buffer, uint16_t count)
{
	uint16_t i;
	for(i = 0; i < count; i++)
	{
#ifdef Bayonet_Assert
		Bayonet_FLASH_CheckAddressValid(address + 2 * i);
#endif
		buffer[i] = *(__IO uint16_t*)(address + 2 * i);
	}
}

/**
  * @brief  Erase a flash page. 
  * @param  pageAddress: this will erase the page which the address is within. 
  * @retval None. 
  */
void Bayonet_FLASH_ErasePage(uint32_t pageAddress)
{
#ifdef Bayonet_Assert
		Bayonet_FLASH_CheckAddressValid(pageAddress);
#endif
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = pageAddress;
	FLASH->CR |= FLASH_CR_STRT;
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR &=~ FLASH_CR_PER;
}

/**
  * @brief  Write a halfword data to flash. 
  * @param  address: address to write. 
  * @param  data: data to write. 
  * @retval None. 
  */
void Bayonet_FLASH_WriteHalfWord(uint32_t address, uint16_t data)
{
#ifdef Bayonet_Assert
		Bayonet_FLASH_CheckAddressValid(address);
#endif
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR |= FLASH_CR_PG;
	*(__IO uint16_t *)address = data;
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR &=~ FLASH_CR_PG;
}

/**
  * @brief  Write a buffer of halfword data to flash. 
  * @param  address: address to write. 
  * @param  buffer: pointer to the start of buffer. 
  * @param  count: length of buffer. 
  * @retval None. 
  */
void Bayonet_FLASH_WriteBuffer(uint32_t address, uint16_t *buffer, uint16_t count)
{
	uint8_t isNeedErase = 0;
	uint16_t i;
	uint32_t relativeAddress = address - FLASH_BASE;
	uint16_t bufferIndex = 0;				//for high-density device.
	uint16_t pageOffset = relativeAddress % 2048 / 2;
	
	Bayonet_FLASH_Unlock();
	while(1)
	{
		Bayonet_FLASH_ReadBuffer(address - pageOffset, Bayonet_FLASH_Buffer, 1024);
		for(i = 0;i < 1024; i ++)
		{
			if(Bayonet_FLASH_Buffer[i] != 0xffff)
			{
				isNeedErase = 1;
				break;
			}
		}
		if(isNeedErase)
		{
			Bayonet_FLASH_ErasePage(address - pageOffset);
			if(count < (1024 - pageOffset))
			{
				for(i = 0; i < count ; i++)
					Bayonet_FLASH_Buffer[pageOffset + i] = buffer[bufferIndex + i];
			}
			else
			{
				for(i = 0; i < 1024 - pageOffset ; i++)
					Bayonet_FLASH_Buffer[pageOffset + i] = buffer[bufferIndex + i];
			}
			for(i = 0; i < 1024; i++)
				Bayonet_FLASH_WriteHalfWord(address - pageOffset + (i * 2), Bayonet_FLASH_Buffer[i]);
		}
		else
		{
			if(count < 1024 - pageOffset)
			{
				for(i = 0; i < count; i++)
					Bayonet_FLASH_WriteHalfWord(address + (i * 2), buffer[bufferIndex + i]);
			}
			else
			{
				for(i = 0; i < 1024 - pageOffset; i++)
					Bayonet_FLASH_WriteHalfWord(address + (i * 2), buffer[bufferIndex + i]);
			}
		}
		if((1024 - pageOffset - count) < 0)
		{
			count -= (1024 - pageOffset);
			address = address - pageOffset + 2048;
			pageOffset = 0;
			bufferIndex += (1024 - pageOffset);
		}
		else
		{
			break;
		}
	}
	Bayonet_FLASH_Lock();
}

