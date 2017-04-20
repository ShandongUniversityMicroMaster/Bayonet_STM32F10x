#ifndef __BAYONET_CAN_H

#include "stm32f10x.h"

typedef enum
{
	Bayonet_CAN_Succeed,
	Bayonet_CAN_InitializtionNoAck,
	Bayonet_CAN_EndConfigurationNoAck,
	
	Bayonet_CAN_NoMailBox
}Bayonet_CAN_STATE;

Bayonet_CAN_STATE Bayonet_CAN_Init(CAN_TypeDef *CANx);
Bayonet_CAN_STATE Bayonet_CAN_SendMessage(CAN_TypeDef *CANx, uint32_t id, uint8_t *data, uint8_t length);

#endif
