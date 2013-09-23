#include "pwmMyConfiguration.h"

void pwm_config(){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	// TIM clock is 84MHz
	// 84MHz / (21) = 4 MHz
	//TIM_TimeBaseStructInit( &TIM_TimeBaseInitStruct );
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 2000 - 1; // resolution
	TIM_TimeBaseInitStruct.TIM_Prescaler = 21 -1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct );
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseInitStruct );

	TIM_OCInitTypeDef TIM_OCInitStruct;

	//TIM_OCStructInit( &TIM_OCInitStruct );
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	// Initial duty cycle equals 0%
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;

	TIM_OC3Init( TIM2, &TIM_OCInitStruct ); //PA2
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_OC4Init( TIM5, &TIM_OCInitStruct ); //PA3
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

	TIM_Cmd( TIM2, ENABLE );
	TIM_Cmd( TIM5, ENABLE );

}

void pwm_set_pulse(uint32_t pulse){

	//pwm_set_direction(pulse);
	//int pwmRegister = (int) fabs(pulse);
	uint32_t pulse_width = pulse;
	if(pulse < 4)
	{
		pulse_width=4;
	}
	if(pulse > (1999-4))
	{
		pulse_width = 1999-4;
	}

	TIM2->CCR3 = pulse;

	TIM5->CCR4 = pulse+4;

}

void pwm_set_direction(direction dir){

	switch(dir){
	case(FORWARD):
			GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_SET);
			GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);
			break;
	case(BACKWARD):
			GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_RESET);
			GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_RESET);
			break;
	case(STOP):
			GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
			GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_RESET);
			break;
	case(START):
			GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
			GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_SET);
			break;
	default:
		break;
	}

}
