#ifndef SYSTICK_H
#define SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header

void Systick_Init(void);
void SysTick_Handler(void);
void delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif // SYSTICK_H
