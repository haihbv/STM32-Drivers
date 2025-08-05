#include "systick.h"

volatile static uint32_t systick_counter = 0;
void Systick_Init(void)
{
	SysTick->LOAD = 72000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_TICKINT | SysTick_CTRL_CLKSOURCE;
	
}

void delay_ms(uint32_t ms)
{
	systick_counter = ms;
	while (systick_counter != 0);
}

void SysTick_Handler(void)
{
	if (systick_counter > 0)
	{
		systick_counter--;
	}
}
