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
	
#include "Bayonet_CAN.h"
#include "Bayonet_RCC.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_NVIC.h"
#include "Bayonet_UART.h"

void Bayonet_CAN_CLOCK_IO_Init(CAN_TypeDef *CANx)
{
	if(CANx == CAN1)
	{
		Bayonet_RCC_Active(Bayonet_RCC_CAN1);
		Bayonet_GPIO_Init(GPIOA, 11, Bayonet_GPIO_MODE_GPIU);
		Bayonet_GPIO_Init(GPIOA, 12, Bayonet_GPIO_MODE_GPOAPP);
	}
}

Bayonet_CAN_STATE Bayonet_CAN_Init(CAN_TypeDef *CANx, uint8_t ID)
{
	uint8_t i = 0;
	/*RCC_ClocksTypeDef RCC_Clock;
	Bayonet_RCC_GetClocksFreq(&RCC_Clock);*/
	
	Bayonet_CAN_CLOCK_IO_Init(CAN1);
	
	CANx->MCR = 0x00000000;
	CANx->MCR |= CAN_MCR_INRQ;		//Initialization request. 
	while(!(CANx->MSR & CAN_MSR_INAK)) 		//Waiting for CAN device to response. 
	{
		if((i++) > 100)
			return Bayonet_CAN_InitializtionNoAck;
	}
	CANx->MCR &=~ CAN_MCR_TTCM;			//No time trigger mode. 
	CANx->MCR &=~ CAN_MCR_ABOM;			//No automatically software bus-off control. 
	CANx->MCR &=~ CAN_MCR_AWUM;			//No automatically wake up. 
	CANx->MCR |=  CAN_MCR_NART;			//No automatically auto transmition. 
	CANx->MCR &=~	CAN_MCR_RFLM;			//No receiving lock mode. 
	CANx->MCR &=~ CAN_MCR_TXFP;			//No priority. 
	CANx->BTR = 0x00000000;
	
	CANx->BTR &=~ CAN_BTR_LBKM;
	CANx->BTR &=~ CAN_BTR_SILM;
	CANx->BTR |= 1 << 24;
	CANx->BTR |= 7 << 20;
	CANx->BTR |= 8 << 16; 
	//(RCC_Clock.PCLK1_Frequency / 500000)
	CANx->BTR |= 1;
	CANx->MCR &=~ CAN_MCR_INRQ;
	while(CAN1->MSR & CAN_MSR_INAK) 		//Waiting for CAN device to response. 
	{
		if((i++) > 100)
			return Bayonet_CAN_EndConfigurationNoAck;
	}
	CANx->FMR |= CAN_FMR_FINIT;
	CANx->FA1R &=~ CAN_FA1R_FACT0;
	CANx->FS1R |= CAN_FS1R_FSC0;
	CANx->FM1R &=~ CAN_FM1R_FBM;
	CANx->FFA1R &=~ CAN_FFA1R_FFA;
	CANx->sFilterRegister[0].FR1 = ID<<21;
	CANx->sFilterRegister[0].FR2 = 0xFFE00000;
	CANx->FA1R |= CAN_FA1R_FACT0;
	CANx->FMR &=~ CAN_FMR_FINIT;
	
	CANx->IER |= CAN_IER_FMPIE0;
	Bayonet_NVIC_Init(USB_LP_CAN1_RX0_IRQn, 1, 0);
	
	return Bayonet_CAN_Succeed;
}

Bayonet_CAN_STATE Bayonet_CAN_SendMessage(CAN_TypeDef *CANx, uint32_t id, uint8_t *data, uint8_t length)
{
	uint8_t mailBox;
	if(CANx->TSR & CAN_TSR_TME0)
		mailBox = 0;
	else if(CANx->TSR & CAN_TSR_TME1)
		mailBox = 1;
	else if(CANx->TSR & CAN_TSR_TME2)
		mailBox = 2;
	else
		return Bayonet_CAN_NoMailBox;
	
	CANx->sTxMailBox[mailBox].TIR = 0x00000000;
	id &= 0x7ff;
	CANx->sTxMailBox[mailBox].TIR |= id << 21;
	CANx->sTxMailBox[mailBox].TIR &=~ CAN_TI0R_IDE; 	//standard. 
	CANx->sTxMailBox[mailBox].TIR &=~ CAN_TI0R_RTR; //Data frame. 
	
	CANx->sTxMailBox[mailBox].TDTR &=~ CAN_TDT0R_DLC;
	CANx->sTxMailBox[mailBox].TDTR = length;		//Data length. 
	
	
	CANx->sTxMailBox[mailBox].TDHR=(((u32)data[7]<<24)|
								((u32)data[6]<<16)|
 								((u32)data[5]<<8)|
								((u32)data[4]));
	CANx->sTxMailBox[mailBox].TDLR=(((u32)data[3]<<24)|
								((u32)data[2]<<16)|
 								((u32)data[1]<<8)|
								((u32)data[0]));
	
	CANx->sTxMailBox[mailBox].TIR |= CAN_TI0R_TXRQ;
	
	return Bayonet_CAN_Succeed;
}
