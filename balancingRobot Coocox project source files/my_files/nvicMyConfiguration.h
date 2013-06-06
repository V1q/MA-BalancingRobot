#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"

void nvic_config(void);
void enableUSART1ReceiveINT(NVIC_InitTypeDef *NVIC_InitStructure);
void enableEXTI0INT(NVIC_InitTypeDef *NVIC_InitStructure);
int sysTick_Config_Mod(unsigned long int SysTick_CLKSource, unsigned long int ticks);
