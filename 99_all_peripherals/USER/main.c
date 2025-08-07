#include "stm32f10x.h"                  // Device header
#include "systick.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "printf.h"

int main()
{
	Systick_Init();
	USARTx_Init(USART1, USART_BAUDRATE_9600);
	
	while (1)
	{
		print(USART1, "Hello Word!\n");
		delay_ms(5000);
	}
}
