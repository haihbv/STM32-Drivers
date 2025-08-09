#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header

extern uint16_t adc_ch0_value;
extern uint16_t adc_ch1_value;
extern uint16_t adc_ch2_value;
extern uint16_t adc_ch3_value;

void ADC_Config(void);
uint16_t ADC_Read(void);
uint16_t ADC_ReadChannel(uint8_t channel);
void ADC_Multi_Channel_Config(void);
void ADC_Multi_Channel_Read(void);

#ifdef __cplusplus
}
#endif

#endif // ADC_H
