#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C

#define I2C_SLAVE_ADDR  0x68

void I2C_Config(I2C_TypeDef* I2Cx);
void I2C_Write_Data(I2C_TypeDef* I2Cx, uint8_t u8_slave_addr, uint8_t u8_data);
uint8_t I2C_Read_Data(I2C_TypeDef* I2Cx, uint8_t u8_slave_addr);

#ifdef __cplusplus
}
#endif

#endif // __I2C_H
