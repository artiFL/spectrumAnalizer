#include "clock.h"

uint32_t Clock_Surce = CLOCK;

void clock_update(uint16_t CoreClock){
	CoreClock < 50 ? (CoreClock = 50) : (CoreClock);

	//FLASH->ACR |= FLASH_ACR_ARTEN;		//ART ACCELERATOR EN			http://forum.easyelectronics.ru/viewtopic.php?f=35&t=40035
	FLASH-> ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
	FLASH-> ACR |= (uint32_t)FLASH_ACR_LATENCY_1WS;// SW7
	FLASH-> ACR |= FLASH_ACR_PRFTEN;

	//������ ������
	RCC->CR = 0;
	RCC->CFGR = 0;

	//Enable HSE
	RCC->CR |= RCC_CR_HSEON;
	//Wait till HSE is ready
	    while(!(RCC->CR & RCC_CR_HSERDY));

	RCC->PLLCFGR = 0;
	RCC->PLLCFGR	|=			10  << RCC_PLLCFGR_PLLM_Pos	|
				 	 	 CoreClock  << RCC_PLLCFGR_PLLN_Pos	|
								2   << RCC_PLLCFGR_PLLP_Pos;

	// PLL surce
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
	// HCLK = SYSCLK
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	// PCLK1 = APB1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	// PCLK2 = APB2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	// Turn on the PLL
	RCC->CR |= RCC_CR_PLLON;
	// Wait till PLL is ready
	    while((RCC->CR & RCC_CR_PLLRDY) == 0);

	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
//-----------------------------------------------------------------------------------------------------------------------------------------------
	    Clock_Conf.PLLM = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
	    Clock_Conf.PLLN = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6;
	    Clock_Conf.PLLP = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16);

		((RCC->CFGR >> 4) & 0xF) == 0 ? (Clock_Conf.PHCLK = 1) : (Clock_Conf.PHCLK = pow(2, (((RCC -> CFGR >> 4) & 0xF) % 8) + 1));
		(((RCC->CFGR >> 10) & 0x7) % 4) == 0 ? (Clock_Conf.PPCLK1 = 1) : (Clock_Conf.PPCLK1 = pow(2, (((RCC -> CFGR >> 10) & 0xF) % 4) + 1));
		(((RCC->CFGR >> 13) & 0x7) % 4) == 0 ? (Clock_Conf.PPCLK2 = 2) : (Clock_Conf.PPCLK2 = pow(2, (((RCC -> CFGR >> 13) & 0xF) % 4) + 1));

		Clock_Conf.AHB = (((Clock_Surce / Clock_Conf.PLLM) * Clock_Conf.PLLN) / Clock_Conf.PLLP) / Clock_Conf.PHCLK;
		Clock_Conf.APB1Perip = Clock_Conf.AHB / Clock_Conf.PPCLK1;
		Clock_Conf.APB2Perip = Clock_Conf.AHB / Clock_Conf.PPCLK2;
		Clock_Conf.APB1Timer = Clock_Conf.APB1Perip * 2;
		Clock_Conf.APB2Timer = Clock_Conf.APB2Perip * 2;
		Clock_Conf.Core = Clock_Conf.AHB;
}

void Delay_us (uint32_t delay) {
	uint32_t us_count_tick =  (delay * (Clock_Conf.Core/1000000)) / 3;
	DWT_init();
	__CLEAR_DWT;
	__STARTDWT;
	while(DWT->CYCCNT < us_count_tick);
	__STOPDWT;
}

void delay (uint32_t delay) {
	Delay_us(delay * 1000);
}

void DWT_init(void) {
    CoreDebug->DEMCR |= 0x01000000;
    DWT-> LAR = 0xC5ACCE55;
    DWT->CYCCNT = 0;
    DWT->CTRL = 0;
}

