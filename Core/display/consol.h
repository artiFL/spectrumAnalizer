#pragma once

#define CONSOLE_H

#ifdef HEADER_H
	#include <header.h>
#endif

#include "display.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

typedef struct {
	uint16_t CLI_bacgroundeColor;
	uint16_t CLI_textColor;

}color_t;
color_t color;

typedef enum {
	MsgInfo = 0,
	MsgWarning = 1,
	MsgError = 2
}
eConsoleMsgType;


void console_printf(eConsoleMsgType msgType, const char *args, ...);
void string_line (char *String);
