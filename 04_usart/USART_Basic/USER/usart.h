#ifndef USART_H
#define USART_H

#include "stm32f10x.h" // Device header

void USART_GPIO_Config(USART_TypeDef *USARTx);
void USART_Config(USART_TypeDef *USARTx);

// Transmit
void USART_SendDataCommand(USART_TypeDef *USARTx, uint16_t data);
void USART_NewLine(USART_TypeDef *USARTx);
void USART_SendStringCommand(USART_TypeDef *USARTx, const char *str);

// Print
void USART_Printf(USART_TypeDef *USARTx, const char *format, ...) __attribute__((format(printf, 2, 3)));

// Receive
uint16_t USART_Receive_DataCommand(USART_TypeDef *USARTx);

// Echo
char USART_ReceiveCharEcho(USART_TypeDef *USARTx);

#endif // USART_H
