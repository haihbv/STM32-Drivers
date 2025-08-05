#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header

void ADC_Config(void);
uint16_t ADC_Read(void);

#ifdef __cplusplus
}
#endif

#endif // ADC_H
