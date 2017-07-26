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
	
#include "Bayonet_IIC.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_Delay.h"

uint8_t deviceNumber = 0; 

Bayonet_IIC_Device Bayonet_IIC_CreateDevice(GPIO_TypeDef *SDA_Port, uint8_t SDA_Pin, GPIO_TypeDef *SCL_Port, uint8_t SCL_Pin)
{
	Bayonet_IIC_Device device;
	device.SDA_Port = SDA_Port;
	device.SDA_Pin = SDA_Pin;
	device.SCL_Port = SCL_Port;
	device.SCL_Pin = SCL_Pin;
	device.deviceID = deviceNumber;
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD);
	Bayonet_GPIO_Init(SCL_Port, SCL_Pin, Bayonet_GPIO_MODE_GPOGOD);
	deviceNumber++;
	return device;
}

void Bayonet_IIC_Start(Bayonet_IIC_Device device)
{
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD);
	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, true);	  	  
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true);
	Bayonet_Delay_Us(4);
 	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, false);
	Bayonet_Delay_Us(4);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
}

void Bayonet_IIC_Stop(Bayonet_IIC_Device device)
{
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, false);
 	Bayonet_Delay_Us(4);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true); 
	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, true);
	Bayonet_Delay_Us(4);							   	
}

uint8_t Bayonet_IIC_WaitAck(Bayonet_IIC_Device device)
{
	uint8_t ucErrTime=0;
	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, true);
	Bayonet_Delay_Us(1);	   
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPIU);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true);
	Bayonet_Delay_Us(1);	 
	while(Bayonet_GPIO_Get(device.SDA_Port, device.SDA_Pin))
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			Bayonet_IIC_Stop(device);
			return 1;
		}
	  Bayonet_Delay_Us(1);
	}
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
	return 0;  
} 

void Bayonet_IIC_Ack(Bayonet_IIC_Device device)
{
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD);
	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, false);
	Bayonet_Delay_Us(2);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true);
	Bayonet_Delay_Us(2);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
}

void Bayonet_IIC_NAck(Bayonet_IIC_Device device)
{
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD);
	Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, true);
	Bayonet_Delay_Us(2);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true);
	Bayonet_Delay_Us(2);
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
}					 				     

void Bayonet_IIC_SendByte(Bayonet_IIC_Device device, uint8_t txd)
{                        
  uint8_t t;   
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD); 	    
	Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);
	for(t=0;t<8;t++)
	{              
		Bayonet_GPIO_Set(device.SDA_Port, device.SDA_Pin, (txd&0x80)>>7);
		txd<<=1; 	  
		Bayonet_Delay_Us(2);   
		Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true);
		Bayonet_Delay_Us(2); 
		Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false);	
		Bayonet_Delay_Us(2);
	}
} 	 

uint8_t Bayonet_IIC_ReadByte(Bayonet_IIC_Device device, uint8_t ack)
{
	uint8_t i,receive=0;
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPIU);
  for(i = 0; i < 8; i++ )
	{
		Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, false); 
		Bayonet_Delay_Us(2);
		Bayonet_GPIO_Set(device.SCL_Port, device.SCL_Pin, true);
		receive <<= 1;
    if(Bayonet_GPIO_Get(device.SDA_Port, device.SDA_Pin) == true)
			receive++;   
		Bayonet_Delay_Us(2); 
  }					 
	if (ack)
			Bayonet_IIC_Ack(device); 
	else
			Bayonet_IIC_NAck(device); 
	Bayonet_GPIO_Init(device.SDA_Port, device.SDA_Pin, Bayonet_GPIO_MODE_GPOGOD);
	return receive;
}

uint8_t Bayonet_IIC_ReadBytes(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t length, uint8_t *data)
{
  uint8_t count = 0;
	uint8_t temp;
	Bayonet_IIC_Start(device);
	Bayonet_IIC_SendByte(device, slaveAddress);
	Bayonet_IIC_WaitAck(device);
	Bayonet_IIC_SendByte(device, reg);
  Bayonet_IIC_WaitAck(device);	  
	Bayonet_IIC_Start(device);
	Bayonet_IIC_SendByte(device, slaveAddress+1);
	Bayonet_IIC_WaitAck(device);
	for(count=0;count<length;count++)
	{ 
		if(count!=(length-1))
			temp = Bayonet_IIC_ReadByte(device, 1);
		else
			temp = Bayonet_IIC_ReadByte(device, 0);
		data[count] = temp;
	}
	Bayonet_IIC_Stop(device);
	return count;
}

uint8_t Bayonet_IIC_WriteBytes(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t length, uint8_t* data)
{
 	uint8_t count = 0;
	Bayonet_IIC_Start(device);
	Bayonet_IIC_SendByte(device, slaveAddress);
	Bayonet_IIC_WaitAck(device);
	Bayonet_IIC_SendByte(device, reg);
  Bayonet_IIC_WaitAck(device);
	for(count=0;count<length;count++)
	{
		Bayonet_IIC_SendByte(device, data[count]); 
		Bayonet_IIC_WaitAck(device); 
	 }
	Bayonet_IIC_Stop(device);
  return 1;
}

uint8_t Bayonet_IIC_WriteBit(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t bitNum, uint8_t data)
{
	uint8_t b;
	Bayonet_IIC_ReadBytes(device, slaveAddress, reg, 1, &b);
	b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	return Bayonet_IIC_WriteBytes(device, slaveAddress, reg, 1, &b);
}

uint8_t Bayonet_IIC_WriteBits(Bayonet_IIC_Device device, uint8_t slaveAddress, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t data)
{
	uint8_t oldData, mask;
	Bayonet_IIC_ReadBytes(device, slaveAddress, reg, 1, &oldData);
	mask = (0xff << (bitStart + 1)) | 0xff >> ((8 - bitStart) + length - 1);
	data <<= (8 - length);
	data >>= (7 - bitStart);
	oldData &= mask;
	oldData |= data;
	return Bayonet_IIC_WriteBytes(device, slaveAddress, reg, 1, &data);
}
