# DHT11_LED7
# Description 

	Using STM32F051 comunicate with DHT11 and display on 7 segments led. 
	The led is connect with 74HC595.
	
# pin connection

## STM32F051 DISCOVERY KIT                            74HC595
    PORT_B PIN 3          							  74HC595_DO
	PORT_B PIN 4									  74HC595_RCLK
	PORT_B PIN 5									  74HC595_SCLK
	5V												  VCC
	GND												  GND
## STM32F051 DISCOVERY KIT                            DHT11
	PORT B PIN6											DHT11_DATA
	3,3V												VCC
	GND													GND