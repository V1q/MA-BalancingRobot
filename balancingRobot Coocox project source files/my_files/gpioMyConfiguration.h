#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

void gpio_config(void);
void configureGPIODiodes ( GPIO_InitTypeDef *GPIO_InitStructure );
void configureGPIOBT ( GPIO_InitTypeDef *GPIO_InitStructure );
void configureGPIOButton ( GPIO_InitTypeDef *GPIO_InitStructure );
void configureGPIOPWM ( GPIO_InitTypeDef *GPIO_InitStructure );
void configureGPIOMotors ( GPIO_InitTypeDef *GPIO_InitStructure );
