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
	SPIx_Init(SPI1);
	while (1)
	{
		SPI_Send_Data_Command(SPI1, 0xA3);
		delay_ms(1000);
	}
}
