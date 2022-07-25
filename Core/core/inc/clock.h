#pragma once
#define CLOCK_H

#include "stm32f7xx.h"
#include "math.h"
#include "stdlib.h"
#include <header.h>


#define __STARTDWT 	DWT->CTRL |= 0x00000001
#define __STOPDWT 	DWT->CTRL &= 0xFFFFFFFE
#define __CLEAR_DWT DWT->CYCCNT = 0

typedef struct{
	uint8_t 	PLLM;
	uint8_t 	PLLP;
	uint8_t 	PHCLK;
	uint8_t 	PPCLK2;
	uint8_t 	PPCLK1;
	uint16_t 	PLLN;
	uint32_t 	AHB;
	uint32_t 	APB1Perip;
	uint32_t 	APB1Timer;
	uint32_t 	APB2Perip;
	uint32_t 	APB2Timer;
	uint32_t 	Core;
}Clock_Configuration_TypeDef;
Clock_Configuration_TypeDef Clock_Conf;

void clock_update(uint16_t coreClock);
void DWT_init(void);

void Delay_us (uint32_t delay);
void delay (uint32_t delay);
