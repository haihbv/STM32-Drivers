#include "i2c.h"

void I2C_Config(I2C_TypeDef* I2Cx)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef	 I2C_InitStruct;
	
	if (I2Cx == I2C1)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
	else if (I2Cx == I2C2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
	else
	{
		return;
	}
	
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2Cx, &I2C_InitStruct);
	
	I2C_Cmd(I2Cx, ENABLE);
}
void I2C_Write_Data(I2C_TypeDef* I2Cx, uint8_t u8_slave_addr, uint8_t u8_data)
{
	// Start
	I2Cx->CR1 &= ~(1 << 9); // cleat bit stop hoac bo neu bus ranh
	I2C_GenerateSTART(I2Cx, ENABLE);
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) == RESET);
	
	// Address + Write
	I2C_Send7bitAddress(I2Cx, (uint8_t)(u8_slave_addr << 1), I2C_Direction_Transmitter);
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == RESET);
	
	// Data
	I2C_SendData(I2Cx, u8_data);
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET);
	
	// Stop
	I2C_GenerateSTOP(I2Cx, ENABLE);
}

uint8_t I2C_Read_Data(I2C_TypeDef* I2Cx, uint8_t u8_slave_addr)
{
	uint8_t u8_data;
	
	// start
	I2C_GenerateSTART(I2C1, ENABLE);
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) == RESET);
	
	// address + read
	I2C_Send7bitAddress(I2Cx, (uint8_t)(u8_slave_addr << 1), I2C_Direction_Receiver);
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == RESET);
	
	// receive data
	while (I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) == RESET);
	u8_data = I2C_ReceiveData(I2Cx);
	
	// stop
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	return u8_data;
}
