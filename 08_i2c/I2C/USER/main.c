#include "stm32f10x.h" // Device header

void I2C1_Init(void);
void I2C_WriteByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C_ReadByte(uint8_t slaveAddr, uint8_t regAddr);

uint8_t value;
int main(void)
{
	I2C1_Init();

	// ghi 0x55 vao thanh ghi 0x10 cua I2C co dia chi 0xD0
	I2C_WriteByte(0xD0, 0x10, 0x55);

	// doc lai du lieu tu thanh ghi do
	value = I2C_ReadByte(0xD1, 0x10);

	while (1)
		;
}

void I2C1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	I2C_DeInit(I2C1);
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = ENABLE;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}
void I2C_WriteByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t data)
{
	// doi bus ranh
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
		;

	// gui tin hieu start
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
		;

	// gui dia chi slave (write)
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;

	// gui dia chi thanh ghi
	I2C_SendData(I2C1, regAddr);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	// gui du lieu
	I2C_SendData(I2C1, data);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	// stop
	I2C_GenerateSTOP(I2C1, ENABLE);
}
uint8_t I2C_ReadByte(uint8_t slaveAddr, uint8_t regAddr)
{
	uint8_t receive_data;

	// doi bus ranh
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
		;

	// gui start
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
		;

	// giua dia chi slave
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;

	// gui dia chi thanh ghi can doc
	I2C_SendData(I2C1, regAddr);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	// gui lenh start lai
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
		;

	// gui dia chi slave (read)
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		;

	// tat ack
	I2C_AcknowledgeConfig(I2C1, DISABLE);

	// cho nhan xong byte
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
		;
	receive_data = I2C_ReceiveData(I2C1);

	// gui stop
	I2C_GenerateSTOP(I2C1, ENABLE);

	// bat lai ack cho cac lan sau
	I2C_AcknowledgeConfig(I2C1, ENABLE);

	return receive_data;
}
