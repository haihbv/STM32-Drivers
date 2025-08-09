#include "stm32f10x.h"                  // Device header
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "printf.h"
#include "spi.h"
#include "i2c.h"

uint16_t adc_ch0_value = 0;
uint16_t adc_ch1_value = 0;
uint16_t adc_ch2_value = 0;

int main(void)
{
	Systick_Init();
	ADC_Multi_Channel_Config();
	while (1)
	{
		ADC_Multi_Channel_Read();
		delay_ms(1000);
	}
}
