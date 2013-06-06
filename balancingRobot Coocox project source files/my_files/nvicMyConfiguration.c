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

int sysTick_Config_Mod(unsigned long int SysTick_CLKSource, unsigned long int ticks){

	unsigned long int Settings;

	//check parameter
	assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));

	//check whether initial value < MAX of register
	if(ticks > SysTick_LOAD_RELOAD_Msk) return(1);

	//load initial value to SysTick register
	SysTick->LOAD = ( ticks & SysTick_LOAD_RELOAD_Msk)-1;

	//set priority of interruption
	NVIC_SetPriority(SysTick_IRQn, 0);

	//load current value of timer register
	SysTick->VAL = 0;

	//enable SysTick interruption and timer itself
	Settings = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

	//choose proper clock source on basis of SysTick_CLKSource parameter
	if(SysTick_CLKSource == SysTick_CLKSource_HCLK){
		Settings |= SysTick_CLKSource_HCLK;
	}else{
		Settings |= SysTick_CLKSource_HCLK_Div8;
	}

	//save settings to steering register
	SysTick->CTRL = Settings;

	return (0);
}
