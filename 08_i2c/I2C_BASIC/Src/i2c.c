#include "i2c.h"
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

void I2C1_GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	// SCL (PB6), SDA (PB7)
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
}
void I2C1_Config(void)
{
	I2C_DeInit(I2C1);
	
	I2C_InitTypeDef i2c;
	i2c.I2C_ClockSpeed = 100000;
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c.I2C_OwnAddress1 = 0x00;
	i2c.I2C_Ack = I2C_Ack_Enable;
	i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE);
}
void I2C_TestWrite(void)
{
   uint8_t addr = 0x68;  
   uint8_t data = 0x00;

   while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); 

   I2C_GenerateSTART(I2C1, ENABLE);
   while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

   I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter); 
   while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

   I2C_SendData(I2C1, 0x00); 
   while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

   I2C_SendData(I2C1, data); 
   while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

   I2C_GenerateSTOP(I2C1, ENABLE);
}
