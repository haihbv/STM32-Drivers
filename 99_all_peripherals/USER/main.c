#include "stm32f10x.h"                  // Device header
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "printf.h"
#include "spi.h"
#include "i2c.h"

int main(void)
{
	Systick_Init();
	I2C_Config(I2C1);
	while (1)
	{
		I2C_Write_Data(I2C1, I2C_SLAVE_ADDR, 0x11);
		delay_ms(1000);
	}
}
