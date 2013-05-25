//includes

#include "rccMyConfiguration.h"
#include "gpioMyConfiguration.h"
#include "nvicMyConfiguration.h"
#include "usartMyConfiguration.h"


//--------------
//main loop
int main(void)
{
	rcc_config();
	nvic_config();
	gpio_config();
	usart_config();

    while(1)
    {

    }
}
