#ifndef __TIM_H
#define __TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

// TIM1
void TIM1_PWM_Config(uint16_t duty);
void TIM1_PWM_Servo_Init(void);

	
// TIM2
void TIM2_Config(void);
void delay_tim2_ms(uint32_t ms);
void delay_us(uint32_t us);
void TIM2_IRQHandler(void);
void TIM2_PWM_Servo_Init(void);

// TIM3
void TIM3_Config(void);
void delay_tim3_ms(uint32_t ms);

void Servo_SetAngle(TIM_TypeDef* TIMx, uint16_t angle);
void Servo_SweepAngle(TIM_TypeDef *TIMx, uint8_t from_angle, uint8_t to_angle, uint8_t step_angle, uint16_t delay_ms);

#ifdef __cplusplus
}
#endif

#endif // __TIM_H
