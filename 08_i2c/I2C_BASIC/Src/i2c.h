#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"                  // Device header

void I2C1_GPIO_Config(void);
void I2C1_Config(void);
void I2C_TestWrite(void);

#endif // I2C_H
