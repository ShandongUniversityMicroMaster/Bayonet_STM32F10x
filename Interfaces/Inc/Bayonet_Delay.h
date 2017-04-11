#ifndef __BAYONET_DELAY_H
#define __BAYONET_DELAY_H

#include "stm32f10x.h"

#define delay_ms Bayonet_Delay_Ms
#define delay_us Bayonet_Delay_Us

void Bayonet_Delay_Init(u8 SYSCLK);
void Bayonet_Delay_Ms(u16 nms);
void Bayonet_Delay_Us(u32 nus);

#endif
