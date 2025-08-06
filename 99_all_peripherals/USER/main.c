#include "stm32f10x.h"                  // Device header
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"

int main()
{
	Systick_Init();
	GPIOx_Init(GPIOA, GPIO_Pin_8 | GPIO_Pin_0, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	
	TIM1_PWM_Servo_Init();
	TIM2_PWM_Servo_Init();
	
	while (1)
	{
		Servo_SweepAngle(TIM2, 0,   180, 10, 300);
		Servo_SweepAngle(TIM2, 180, 0,   10, 300);
	}
}
