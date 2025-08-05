#include "stm32f10x.h"                  // Device header
#include "systick.h"
#include "gpio.h"
#include "adc.h"

static uint16_t value;
int main()
{
	Systick_Init();
	ADC_Config();
	GPIOx_Init(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	while (1)
	{
		value = ADC_Read();
		if (value < 512)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6, Bit_SET);
		}
		else if (value < 1024)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_5 | GPIO_Pin_6, Bit_SET);
		}
		else if (value < 2048)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5, Bit_RESET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
		}
		else if (value < 3072)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_5 | GPIO_Pin_6, Bit_RESET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
		}
		else 
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6, Bit_RESET);
		}
	}
}
