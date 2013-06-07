#include "rccMyConfiguration.h"

void rcc_config(void){
	//status variable
	ErrorStatus HSEStartUpStatus;

	//RCC registers reset
	RCC_DeInit();

	//turn on HSE
	RCC_HSEConfig(RCC_HSE_ON);

	//wait for HSE stabilization
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		//delay time for FLASH memory
		//depends on speed of clock
		//*        @arg FLASH_Latency_0: FLASH Zero Latency cycle	 	0 - 30MHz
		//*        @arg FLASH_Latency_1: FLASH One Latency cycle		30 - 60MHz
		//*        @arg FLASH_Latency_2: FLASH Two Latency cycles	   	60 - 90MHz
		//*        @arg FLASH_Latency_3: FLASH Three Latency cycles		90 - 120MHz
		//*        @arg FLASH_Latency_4: FLASH Four Latency cycles 		120 - 150MHz
		//*        @arg FLASH_Latency_5: FLASH Five Latency cycles 		120 - 168MHz
		//*        @arg FLASH_Latency_6: FLASH Six Latency cycles		NA
		//*        @arg FLASH_Latency_7: FLASH Seven Latency cycles		NA
		FLASH_PrefetchBufferCmd(ENABLE);
		FLASH_SetLatency(FLASH_Latency_5);

		//HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		//PCLK2 = HCLK/2 		MAX 84MHz
		RCC_PCLK2Config(RCC_HCLK_Div2);

		//PCLK1 = HCLK/4		MAX	42MHz
		RCC_PCLK1Config(RCC_HCLK_Div4);

		//PLLCLK 	PLLM = 8, PLLN = 336, PLLP = 2, PLLQ = 7
		//PLLCLK = (HSE * (PLLN/PLLM))/PLLP  = 168MHz 			(MAX 168MHz)
		//USB OTG FS, SDIO, RNG clock output = PLLCLK / PLLQ  	(lets assume < 48MHz, irrelevant if not used)
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);

		//PLL on
		RCC_PLLCmd(ENABLE);

		//wait for pll readiness
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		//set pll as clock source for sysclk
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		//wait for change of clock source
		//0x00: HSI used as system clock
        //0x04: HSE used as system clock
        //0x08: PLL used as system clock
		while(RCC_GetSYSCLKSource() != 0x08){;}

		enableClockSourcesForPeripherials();
	}
}

void enableClockSourcesForPeripherials(){

	//enable clock source for GPIO D (diodes)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//enable clock source for GPIO A (nres,button,pwms)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//enable clock source for USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//enable syscfg clock - for external interruptions
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//enable clock source for GPIO B - USART pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//enable clock source for TIM2 and TIM5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	//enable port E for motor direction control
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
}
