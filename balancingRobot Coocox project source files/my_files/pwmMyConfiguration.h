#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include <Math.h>
#include <stdint.h>

#define MAX_PWM (2000-1);

typedef enum{
	FORWARD,
	BACKWARD,
	STOP,
	START
} direction;

void pwm_config();

void pwm_set_pulse(uint32_t pulse);

void pwm_set_direction(direction dir);
