#include "pwmMyConfiguration.h"

void pwm_config(){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	// TIM clock is 84MHz
	// 84MHz / (2100*4) = 10 KHz
	TIM_TimeBaseStructInit( &TIM_TimeBaseInitStruct );
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseInitStruct.TIM_Period = 65535 - 1; // resolution
	TIM_TimeBaseInitStruct.TIM_Prescaler = 2100-1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct );
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseInitStruct );

	TIM_OCInitTypeDef TIM_OCInitStruct;

	TIM_OCStructInit( &TIM_OCInitStruct );
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	// Initial duty cycle equals 0%
	TIM_OCInitStruct.TIM_Pulse = 0;

	TIM_OC2Init( TIM4, &TIM_OCInitStruct ); //PA2
	TIM_OC4Init( TIM5, &TIM_OCInitStruct ); //PA3

	TIM_Cmd( TIM4, ENABLE );
	TIM_Cmd( TIM5, ENABLE );

}

void pwm_set_pulse(uint32_t pulse){

	TIM2->CCR3 = pulse;
	TIM5->CCR4 = pulse;

}

