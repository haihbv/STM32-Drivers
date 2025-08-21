#include "stm32f10x.h"                  // Device header

void gpio_test(void);
void delay_ms(uint32_t ms);

int main()
{
	gpio_test();
	while (1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(1000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_ms(1000);
	}
}

void gpio_test(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);
}
void delay_ms(uint32_t ms)
{
	volatile uint32_t i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 0x1995; j++);
	}
}
