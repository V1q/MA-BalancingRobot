//includes
#include "rccMyConfiguration.h"
#include "gpioMyConfiguration.h"
#include "nvicMyConfiguration.h"
#include "usartMyConfiguration.h"
#include "MPU6050.h"

//--------------
//main loop
int main(void)
{
	int i=0;
	for(i=0;i<100000ul;i++);

	int16_t  AccelGyro[6]={0};

	rcc_config();
	nvic_config();
	gpio_config();
	usart_config();
	USART_puts(USART1, "USART init complete!\r\n"); // just send a message to indicate that it works

	MPU6050_I2C_Init();
	MPU6050_Initialize();
	if( MPU6050_TestConnection() == 1){
	    // connection success
		USART_puts(USART1, "I2C init complete!\r\n");
	}else{
	    // connection failed
		USART_puts(USART1, "I2C init failed!\r\n");
	}

	MPU6050_GetRawAccelGyro(AccelGyro);


    while(1)
    {

    }
}
