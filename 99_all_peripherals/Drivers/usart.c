#include "usart.h"

#define NULL (void*)0
	

void USARTx_Init(USART_TypeDef* USARTx, uint16_t baud_rate)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	if (USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else if (USARTx == USART2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else if (USARTx == USART3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
	else
	{
		return;
	}
	
	USART_InitStruct.USART_BaudRate = baud_rate;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USARTx, &USART_InitStruct);
	
	USART_Cmd(USARTx, ENABLE);
}

void USART_Send_Data(USART_TypeDef* USARTx, uint8_t data)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USARTx->DR = data;
}

void USART_New_Line(USART_TypeDef* USARTx)
{
	USART_Send_Data(USARTx, '\r');
	USART_Send_Data(USARTx, '\n');
}
void USART_Send_String(USART_TypeDef* USARTx, const char *str)
{
	if (str == NULL) return;
	
	do 
	{
		USART_Send_Data(USARTx, *str);
	} while (*++str);
}

uint8_t USART_Receive_Data(USART_TypeDef* USARTx)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
	return (uint8_t)USARTx->DR;
}

void USART_Echo_Char(USART_TypeDef* USARTx)
{
	uint8_t c = USART_Receive_Data(USARTx);
	USART_Send_Data(USARTx, c); 
}
