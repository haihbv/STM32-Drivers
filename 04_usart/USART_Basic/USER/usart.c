#include "usart.h"
#include <stdarg.h>
#include <stdio.h>

void USART_GPIO_Config(USART_TypeDef *USARTx)
{
	GPIO_InitTypeDef gpio;

	if (USARTx == USART1)
	{
		// Enable clock for USART1 and GPIOA
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

		// TX - PA9
		gpio.GPIO_Pin = GPIO_Pin_9;
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio);

		// RX - PA10
		gpio.GPIO_Pin = GPIO_Pin_10;
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &gpio);
	}
	else if (USARTx == USART2)
	{
		// Enable clock for USART2 (APB1) and GPIOA (APB2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

		// TX - PA2
		gpio.GPIO_Pin = GPIO_Pin_2;
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio);

		// RX - PA3
		gpio.GPIO_Pin = GPIO_Pin_3;
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &gpio);
	}
	else if (USARTx == USART3)
	{
		// Enable clock for USART3 (APB1) and GPIOB (APB2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		// TX - PB10
		gpio.GPIO_Pin = GPIO_Pin_10;
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);

		// RX - PB11
		gpio.GPIO_Pin = GPIO_Pin_11;
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &gpio);
	}
}

void USART_Config(USART_TypeDef *USARTx)
{
	USART_GPIO_Config(USARTx);

	USART_InitTypeDef usart;
	usart.USART_BaudRate = 9600;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USARTx, &usart);

	USART_Cmd(USARTx, ENABLE);
}
void USART_SendDataCommand(USART_TypeDef *USARTx, uint16_t data)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
		;
	USART_SendData(USARTx, data);
}

void USART_NewLine(USART_TypeDef *USARTx)
{
	USART_SendDataCommand(USARTx, '\r');
	USART_SendDataCommand(USARTx, '\n');
}

void USART_SendStringCommand(USART_TypeDef *USARTx, const char *str)
{
	while (*str)
	{
		USART_SendDataCommand(USARTx, *str++);
	}
}

void USART_Printf(USART_TypeDef *USARTx, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case 's':
			{
				char *str = va_arg(args, char *);
				USART_SendStringCommand(USARTx, str);
				break;
			}
			case 'd':
			{
				int num = va_arg(args, int);
				char buf[12];
				sprintf(buf, "%d", num);
				USART_SendStringCommand(USARTx, buf);
				break;
			}
			case 'x':
			{
				int num = va_arg(args, int);
				char buf[12];
				sprintf(buf, "%x", num);
				USART_SendStringCommand(USARTx, buf);
				break;
			}
			case 'X':
			{
				int num = va_arg(args, int);
				char buf[12];
				sprintf(buf, (*format == 'X') ? "%X" : "%x", num);
				USART_SendStringCommand(USARTx, buf);
				break;
			}
			case 'c':
			{
				char ch = (char)va_arg(args, int);
				USART_SendDataCommand(USARTx, ch);
				break;
			}
			default:
				USART_SendDataCommand(USARTx, *format);
			}
		}
		else
		{
			USART_SendDataCommand(USARTx, *format);
		}
		format++;
	}

	va_end(args);
}

uint16_t USART_Receive_DataCommand(USART_TypeDef *USARTx)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
		;
	return USART_ReceiveData(USARTx);
}
char USART_ReceiveCharEcho(USART_TypeDef *USARTx)
{
	char c = (char)USART_Receive_DataCommand(USARTx);
	USART_SendDataCommand(USARTx, c); // echo
	return c;
}
