#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI

void SPI_Config(void);
void SPI_Send_Data_Command(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif // __SPI_H
