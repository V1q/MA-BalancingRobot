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

	rcc_config();
	nvic_config();
	gpio_config();
	usart_config();
	USART_puts(USART1, "Init complete!\r\n"); // just send a message to indicate that it works

	//MPU6050_I2C_Init();


    while(1)
    {

    }
}
