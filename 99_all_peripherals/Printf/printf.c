#include "printf.h"
#include <stdarg.h>

USART_TypeDef *printf_usart = USART1;

int fputc(int data, FILE *f)
{
    (void)f;
    USART_Send_Data(printf_usart, (uint8_t)data);
    return data;
}

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wformat-nonliteral"

// void USART_Printf(USART_TypeDef* USARTx, const char *format, ...)
//{
//   char buffer[128];
//   va_list args;
//   va_start(args, format);
//   vsnprintf(buffer, sizeof(buffer), format, args);
//   va_end(args);

//  USART_Send_String(USARTx, buffer);
//}

// #pragma GCC diagnostic pop

void print(USART_TypeDef *USARTx, const char *format, ...)
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
            case 'd':
            {
                int val = va_arg(args, int);
                char buf[12];
                sprintf(buf, "%d", val);
                USART_Send_String(USARTx, buf);
                break;
            }
            case 'u':
            {
                unsigned int val = va_arg(args, unsigned int);
                char buf[12];
                sprintf(buf, "%u", val);
                USART_Send_String(USARTx, buf);
                break;
            }
            case 'x':
            {
                unsigned int val = va_arg(args, unsigned int);
                char buf[12];
                sprintf(buf, "%x", val);
                USART_Send_String(USARTx, buf);
                break;
            }
            case 's':
            {
                char *str = va_arg(args, char *);
                USART_Send_String(USARTx, str);
                break;
            }
            case '%':
                USART_Send_Data(USARTx, '%');
                break;
            default:
                USART_Send_Data(USARTx, '?');
                break;
            }
        }
        else
        {
            USART_Send_Data(USARTx, *format);
        }

        format++;
    }

    va_end(args);
}
