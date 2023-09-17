#include"main.h"
#include "DHT1X_SW.h"
uint8_t data[5];
uint8_t timeCnt;
uint8_t pinStatus;
extern TIM_HandleTypeDef htim3;

void DHT1X_SetDataPinDirection(uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// Configuration of Data_Pin 
	GPIO_InitStruct.Pin = DHT11_DATA_Pin;
	if(mode == 0)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
	}else
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	}
  HAL_GPIO_Init(DHT11_DATA_GPIO_Port, &GPIO_InitStruct);
}

void DHT1X_Start(void)
{
	DHT1X_SetDataPinDirection(1);
	HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin,0);
	tim3_delay(18000);
	HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin,1);
	tim3_delay(40);
}

void DHT1X_Responds(void)
{
	DHT1X_SetDataPinDirection(0);
	pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
	while(pinStatus==0)
	{
		pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
	}
	while(pinStatus==1)
	{
		pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
	}
}
void DHT1X_Read_1_byte(uint8_t *value)
{
	for(int i =0;i<8;i++)
	{
		*value<<=1;
		pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
		while(pinStatus==0)
		{
			pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
		}
		tim3_delay(45);
		pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
		if(pinStatus==1)
		{
			*value |=1;
			while(pinStatus==1)
			{
				pinStatus = HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin);
			}
		}
	}
}
void DHT1X_ReadFull(void)
{
	for(int i = 0;i<5;i++)
	{
		DHT1X_Read_1_byte(&data[i]);
	}
}
 void DHT1X_Run(void)
{
	DHT1X_Start();
	DHT1X_Responds();
	DHT1X_ReadFull();
}
uint8_t DHT1X_ReadData(uint8_t *u8RH, uint8_t *u8Tem)
{
	
	__disable_irq();
	DHT1X_Run();
	__enable_irq();
	if(data[4]==(data[1]+data[2]+data[3]+data[0]))
	{
		*u8RH = data[0];
		*u8Tem = data[2];
		return 1;
	} 
	return 0;
}