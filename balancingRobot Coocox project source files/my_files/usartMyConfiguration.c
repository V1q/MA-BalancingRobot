#include "usartMyConfiguration.h"

/*
 * Initializes all parameters of USART communication between STM32F4Discovery and KamodBTM222
 */


void usart_config(void){

	USART_InitTypeDef USART_InitStructure;

	// Speed of transmission
	USART_InitStructure.USART_BaudRate = 19200;

	// Length of word
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;

	// set 1 bit of stop
	USART_InitStructure.USART_StopBits = USART_StopBits_1;

	// no parity control
	USART_InitStructure.USART_Parity = USART_Parity_No;

	// data flow control off
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	// working mode Tx-transmitting, Rx - receiving
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// final initializing set values
	USART_Init(USART1, &USART_InitStructure);

	// turn on USART
	USART_Cmd(USART1, ENABLE);

	//enable requesting interrupt by USART1 after receiving data
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
