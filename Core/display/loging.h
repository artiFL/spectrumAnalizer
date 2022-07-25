#pragma once
#define LOGGING_H

#include "stm32f7xx.h"
#include "consol.h"
#include <header.h>

#include"clock.h"
#include <flash.h>


typedef enum {
	UnknownError = 0,
	LowVoltageBat = 1,
	HoghVoltageBat = 2,
	WaitingError = 3,
	Overrun = 4
}
eTypeError;

void fatal_eror(eTypeError TypeError);
void lcd_console_log (void);

