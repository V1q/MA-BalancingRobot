#include "pwmMyConfiguration.h"

void pwm_config(){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	uint16_t PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 21000000) - 1;

	TIM_TimeBaseStructure.TIM_Period = 665;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


	TIM_OC3Init(TIM4, &TIM_OCInitStructure);


	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	TIM_Cmd(TIM4, ENABLE);


}

void pwm_set_pulse(float pulse){

	pwm_set_direction(pulse);
	int pwmRegister = (int) fabs(pulse);

	TIM2->CCR3 = pwmRegister;
	TIM5->CCR4 = pwmRegister;

}

void pwm_set_direction(float pulse){

	if(pulse > 0){
		// go forward
		GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_RESET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_RESET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_RESET);

		GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_SET);

	}else{
		// go backwards
		GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_RESET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_RESET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_RESET);

		GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_SET);
		GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);

	}

}
