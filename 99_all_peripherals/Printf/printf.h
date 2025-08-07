#ifndef __PRINTF_H
#define __PRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"
#include "stdio.h"

extern USART_TypeDef* printf_usart;

int fputc(int data, FILE *f);
void print(USART_TypeDef* USARTx, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif // __PRINTF_H
