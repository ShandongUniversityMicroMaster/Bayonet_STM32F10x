#include "Bayonet_CAN.h"
#include "Bayonet_RCC.h"
#include "Bayonet_GPIO.h"
#include "Bayonet_NVIC.h"


void Bayonet_CAN_CLOCK_IO_Init(CAN_TypeDef *CANx)
{
	if(CANx == CAN1)
	{
		Bayonet_RCC_Active(Bayonet_RCC_CAN1);
		Bayonet_GPIO_Init(GPIOA, 11, Bayonet_GPIO_MODE_GPIU);
		Bayonet_GPIO_Init(GPIOA, 12, Bayonet_GPIO_MODE_GPOAPP);
	}
}

Bayonet_CAN_STATE Bayonet_CAN_Init(CAN_TypeDef *CANx)
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
	
	//CANx->BTR |= CAN_BTR_LBKM;
	CANx->BTR |= 1 << 24;
	CANx->BTR |= 7 << 20;
	CANx->BTR |= 8 << 16; 
	//(RCC_Clock.PCLK1_Frequency / 500000)
	CANx->BTR |= 3;
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
	CANx->sFilterRegister[0].FR1 = 0x00000000;
	CANx->sFilterRegister[1].FR2 = 0xFFE000A0;
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

void USB_LP_CAN1_RX0_IRQHandler()
{
}
