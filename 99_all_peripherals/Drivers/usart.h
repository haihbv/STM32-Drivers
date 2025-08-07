#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

#define USART_BAUDRATE_9600 		9600
#define USART_BAUDRATE_19200 		19200
#define USART_BAUDRATE_38400 		38400
#define USART_BAUDRATE_57600 		57600
#define USART_BAUDRATE_115200		115200

void USARTx_Init(USART_TypeDef* USARTx, uint16_t baud_rate);
void USART_Send_Data(USART_TypeDef* USARTx, uint8_t data);
void USART_New_Line(USART_TypeDef* USARTx);
void USART_Send_String(USART_TypeDef* USARTx, const char *str);
uint8_t USART_Receive_Data(USART_TypeDef* USARTx);
void USART_Echo_Char(USART_TypeDef* USARTx);

#ifdef __cplusplus
}
#endif

#endif // __USART_H
