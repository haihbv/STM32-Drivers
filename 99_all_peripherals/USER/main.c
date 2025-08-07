#include "stm32f10x.h"                  // Device header
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "printf.h"
#include "spi.h"

int main()
{
	Systick_Init();
	SPI_Config();
	while (1)
	{
		SPI_Send_Data_Command(0xA5);
		delay_ms(1000);
	}
}
