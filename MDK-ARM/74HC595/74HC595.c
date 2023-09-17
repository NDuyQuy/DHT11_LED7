#include "main.h"
#include "74HC595.h"
void startSRCLK(void)
{
	/*2 BIT START SRCLK*/
	HAL_GPIO_WritePin(GPIOB,SCLK_Pin,1);
	HAL_GPIO_WritePin(GPIOB,SCLK_Pin,0);
	HAL_GPIO_WritePin(GPIOB,SCLK_Pin,1);
	HAL_GPIO_WritePin(GPIOB,SCLK_Pin,0);
}
void send1Byte(uint8_t reg)
{
	for(int i =0;i<8;i++)
	{
		if((reg&0x80)==0x80)
		{
			HAL_GPIO_WritePin(GPIOB,DO_Pin,1);
		}
		else HAL_GPIO_WritePin(GPIOB,DO_Pin,0);
		reg<<=1;
		HAL_GPIO_WritePin(GPIOB,SCLK_Pin,1);
		HAL_GPIO_WritePin(GPIOB,SCLK_Pin,0);
		
	}
}
void setRCLK(void)
{
	HAL_GPIO_WritePin(GPIOB,RCLK_Pin,1);
	HAL_GPIO_WritePin(GPIOB,RCLK_Pin,0);
}
void HC595_Test(void)
{
//	send1Byte(0xC0);
//	send1Byte(0xFF);
//	setRCLK();
	send1Byte(0xFF);
	send1Byte(0X00);
	setRCLK();
}
void HC595_M_Led(uint8_t ledValue, uint8_t pwValue)
{
	send1Byte(0xFF);
	send1Byte(0X00);
	setRCLK();
	send1Byte(ledValue);
	send1Byte(pwValue);
	setRCLK();
}