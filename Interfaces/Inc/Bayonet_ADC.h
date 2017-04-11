#ifndef __BAYONET_ADC_H
#define __BAYONET_ADC_H

#include "stm32f10x.h"
#include "Bayonet_Config.h"

#define Bayonet_ADC_CH0				0x00000000
#define Bayonet_ADC_CH1				0x00000001
#define Bayonet_ADC_CH2				0x00000002
#define Bayonet_ADC_CH3				0x00000003
#define Bayonet_ADC_CH4				0x00000004
#define Bayonet_ADC_CH5				0x00000005
#define Bayonet_ADC_CH6				0x00000006
#define Bayonet_ADC_CH7				0x00000007
#define Bayonet_ADC_CH8				0x00000008
#define Bayonet_ADC_CH9				0x00000009
#define Bayonet_ADC_CH10			0x0000000A
#define Bayonet_ADC_CH11			0x0000000B
#define Bayonet_ADC_CH12			0x0000000C
#define Bayonet_ADC_CH13			0x0000000D
#define Bayonet_ADC_CH14			0x0000000E
#define Bayonet_ADC_CH15			0x0000000F

#define Bayonet_ADC_SampleTime_1Cycles5		0x00000000
#define Bayonet_ADC_SampleTime_7Cycles5		0x00000001
#define Bayonet_ADC_SampleTime_13Cycles5	0x00000002
#define Bayonet_ADC_SampleTime_28Cycles5	0x00000003
#define Bayonet_ADC_SampleTime_41Cycles5	0x00000004
#define Bayonet_ADC_SampleTime_55Cycles5	0x00000005
#define Bayonet_ADC_SampleTime_71Cycles5	0x00000006
#define Bayonet_ADC_SampleTime_239Cycles5	0x00000007

extern uint32_t ADC_Buff[3][20];
extern uint32_t tableSequence[3][16];

void Bayonet_ADC_Independent_Init(ADC_TypeDef *ADCx, uint32_t ADC_CHx);
void Bayonet_ADC_IM_Init(ADC_TypeDef *ADCx, uint8_t length, uint32_t ADC_CHxs[], uint32_t SampleTime);
uint16_t Bayonet_ADC_OneTime(ADC_TypeDef *ADCx, uint32_t channel);

#endif
