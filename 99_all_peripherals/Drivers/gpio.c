#include "gpio.h"
#include "systick.h"

void GPIOx_Init(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, GPIOMode_TypeDef gpio_mode, GPIOSpeed_TypeDef gpio_speed)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	if (GPIOx == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if (GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if (GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	
	GPIO_InitStruct.GPIO_Pin = gpio_pin;
	GPIO_InitStruct.GPIO_Mode = gpio_mode;
	GPIO_InitStruct.GPIO_Speed = gpio_speed;
	GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	if (GPIOx->ODR & GPIO_Pin)
		GPIO_ResetBits(GPIOx, GPIO_Pin);
	else
		GPIO_SetBits(GPIOx, GPIO_Pin);
}

void GPIO_Debounce_Basic(GPIO_TypeDef *GPIOx_Input, uint16_t gpio_pin_input, GPIO_TypeDef *GPIOx_Output, uint16_t gpio_pin_output)
{
	if (!GPIO_ReadInputDataBit(GPIOx_Input, gpio_pin_input))
		{
			delay_ms(20);
			if (!GPIO_ReadInputDataBit(GPIOx_Input, gpio_pin_input))
			{
				GPIO_Toggle_Pin(GPIOx_Output, gpio_pin_output);
				
				// wait release
				while (!GPIO_ReadInputDataBit(GPIOx_Input, gpio_pin_input));
				delay_ms(20);
			}
		}
}
