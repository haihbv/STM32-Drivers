#include "adc.h"
#include "systick.h"

void ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef  ADC_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_71Cycles5);
	
	ADC_Cmd(ADC1, ENABLE);
	delay_ms(1);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));
}
uint16_t ADC_Read(void)
{
	uint16_t value;
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (!(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)));
	value = ADC_GetConversionValue(ADC1);
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	return value;
}

void ADC_Multi_Channel_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef  ADC_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; // enable scan mode
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE; // read once then stop
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 3; // number channel to read
	ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_71Cycles5);
	
	ADC_Cmd(ADC1, ENABLE);
	delay_ms(1);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));
}
uint16_t ADC_ReadChannel(uint8_t channel)
{
	uint16_t value;
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_71Cycles5);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	value =  ADC_GetConversionValue(ADC1);
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
  return value;
}

void ADC_Multi_Channel_Read(void)
{
	adc_ch0_value = ADC_ReadChannel(ADC_Channel_0);
  adc_ch1_value = ADC_ReadChannel(ADC_Channel_1);
  adc_ch2_value = ADC_ReadChannel(ADC_Channel_2);
	adc_ch3_value = ADC_ReadChannel(ADC_Channel_3);
	
}

