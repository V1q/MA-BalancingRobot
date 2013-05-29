/**
*****************************************************************************
**
**  File        : stm32f4xx_it.c
**
**  Abstract    : Main Interrupt Service Routines.
**                This file provides template for all exceptions handler and
**                peripherals interrupt service routine.
**
*****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/*
__IO uint16_t IC3ReadValues[8];
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM1Freq = 0;

__IO uint16_t Throttle, Aileron, Elevation, Rudder;

u8 StateBefore = 0;
*/

#define MAX_STRLEN 20 // this is the maximum string length of our string in characters
volatile char received_string[MAX_STRLEN+2] = {' '}; // this will hold the recieved string
#include "usartMyFunctions.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

extern unsigned char buforRx[];
extern unsigned char bufRxIndex;
extern unsigned char odebranoDane;

void USART1_IRQHandler(void)
{

	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		static uint8_t cnt = 0; // this counter is used to determine the string length
		char t = USART1->DR; // the character from the USART1 data register is saved in t

		/* check if the received character is not the '!' character (used to determine end of string)
		 * or the if the maximum string length has been been reached
		 */
		if( (t != '!') && (cnt < MAX_STRLEN) ){
			received_string[cnt] = t;
			cnt++;
		}
		else{ // otherwise reset the character counter and print the received string
			while(cnt<=MAX_STRLEN) {
				received_string[cnt]=' ';
				cnt++;
			}
			received_string[MAX_STRLEN]='\n';
			received_string[MAX_STRLEN+1]='\r';
			cnt = 0;
			USART_puts(USART1, received_string);
		}
	}
}

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI0_IRQHandler(void)
{

	uint8_t currentButtonStatus = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	int i=1000;
	while(i)i=i-1;
	uint8_t nextButtonStatus = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

	if(EXTI_GetITStatus(EXTI_Line0) != RESET
			&& currentButtonStatus==nextButtonStatus && currentButtonStatus == 0)
	{
		/* Toggle LED1 */
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

		volatile char message[]= "Klik!\r\n";
		volatile char *messagePointer = &message[0];

		USART_puts(USART1, messagePointer);

		/* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

