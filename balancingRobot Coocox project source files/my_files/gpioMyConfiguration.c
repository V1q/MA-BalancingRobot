#include "gpioMyConfiguration.h"

/* Initializes all needed GPIO pins for balancing robot project
 * GPIO ports initialized: 	PORT D -> 12,13,14,15 diodes
 *							PORT B -> 6,7 TX,RX USART used for communication with Bluetooth module
 *							PORT A -> 8 NRES (reset) signal for Bluetooth module
 *							PORT A -> 0 user's button
*/
void gpio_config(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef *GPIO_InitStructurePointer = &GPIO_InitStructure;

	configureGPIODiodes(GPIO_InitStructurePointer);
	configureGPIOBT(GPIO_InitStructurePointer);
	configureGPIOButton(GPIO_InitStructurePointer);
}

void configureGPIODiodes ( GPIO_InitTypeDef *GPIO_InitStructure ){

	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure->GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOD, GPIO_InitStructure);
}

void configureGPIOBT ( GPIO_InitTypeDef *GPIO_InitStructure ){

	//PB6 - Tx USART for BT
	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure->GPIO_OType = GPIO_OType_PP;			// this defines the output type as push pull mode (as opposed to open drain)
	GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_UP;			// this activates the pullup resistors on the IO pins
	GPIO_Init(GPIOB, GPIO_InitStructure);

	//PB7 - Rx USART for BT
	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure->GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, GPIO_InitStructure);

	//PA8 - NRES for BT
	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure->GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);	// Alternate function for PB6,7 for USART1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

	GPIO_SetBits(GPIOA, GPIO_Pin_8); // disable reset on bluetooth module
}

void configureGPIOButton ( GPIO_InitTypeDef *GPIO_InitStructure ){

	//PA0 - user button
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure->GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, GPIO_InitStructure);
}
