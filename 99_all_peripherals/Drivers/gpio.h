#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

void GPIOx_Init(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, GPIOMode_TypeDef gpio_mode, GPIOSpeed_TypeDef gpio_speed);
void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin);
void GPIO_Debounce_Basic(GPIO_TypeDef *GPIOx_Input, uint16_t gpio_pin_input, GPIO_TypeDef *GPIOx_Output, uint16_t gpio_pin_output);

#ifdef __cplusplus
}
#endif 

#endif // GPIO_H
