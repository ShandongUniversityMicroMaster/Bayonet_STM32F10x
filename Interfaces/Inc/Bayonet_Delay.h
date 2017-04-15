#ifndef __BAYONET_DELAY_H
#define __BAYONET_DELAY_H

#include "stm32f10x.h"

#define delay_ms Bayonet_Delay_Ms
#define delay_us Bayonet_Delay_Us

void Bayonet_Delay_Init(void);
void Bayonet_Delay_Ms(uint16_t nms);
void Bayonet_Delay_Us(uint16_t nus);

#endif
