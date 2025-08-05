#include "delay.h"
#include "i2c.h"

int main()
{
	I2C1_GPIO_Config();
	I2C1_Config();

	while (1)
	{
		I2C_TestWrite();
		delay_ms(1000);
	}
}
