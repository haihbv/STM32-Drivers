#include "usart.h"

void delay_ms(uint32_t ms);
void GPIOC_Config(void);
int main()
{
	USART_Config(USART1);
	GPIOC_Config();
	while (1)
	{
		//		USART_SendDataCommand(USART1, 'H');
		//		delay_ms(1000);
		//		USART_NewLine(USART1);
		//		USART_SendStringCommand(USART1, "haihbv\r\n");
		//		delay_ms(1000);

		//		USART_Printf(USART1, "Hello %s - So nguyen: %d - Hex: 0x%X\r\n", "haihbv", 1234, 1234);
		//		delay_ms(1000);

		char c = USART_ReceiveCharEcho(USART1);
		if (c == 'T')
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			USART_NewLine(USART1);
			USART_Printf(USART1, "Led PC13 da duoc bat\r\n");
		}
		else if (c == 'H')
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			USART_NewLine(USART1);
			USART_Printf(USART1, "Led PC13 da duoc tat\r\n");
		}
	}
}

void delay_ms(uint32_t ms)
{
	volatile uint32_t i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 0x1995; j++)
			;
	}
}
void GPIOC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);
}
