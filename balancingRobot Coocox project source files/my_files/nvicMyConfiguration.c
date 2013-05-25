#include "nvicMyConfiguration.h"

/*
 * Enables all necessary interruptions:
 * 	- USART1 interruption after receiving data
 * 	- EXTI0 interruption after clicking users button (PA0)
 *
 */
void nvic_config(void){

	#ifdef VECT_TAB_RAM
		NVIC_SetVectorTable(NVIC_VectorTab_RAM, 0x0);
	#else
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	#endif

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitTypeDef *NVIC_InitStructurePionter = &NVIC_InitStructure;

	enableUSART1ReceiveINT(NVIC_InitStructurePionter);
	enableEXTI0INT(NVIC_InitStructurePionter);
}

void enableUSART1ReceiveINT(NVIC_InitTypeDef *NVIC_InitStructure){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure->NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure->NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure->NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(NVIC_InitStructure);
}

void enableEXTI0INT(NVIC_InitTypeDef *NVIC_InitStructure){

	//interruption EXTI0 from user's button
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	EXTI_InitTypeDef   EXTI_InitStructure;
	/* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure->NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure->NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure->NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(NVIC_InitStructure);
}
