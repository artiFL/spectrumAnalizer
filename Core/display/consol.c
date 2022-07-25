#include "consol.h"

#define LineHeight	10
static uint16_t ConsoleLine = 0;

void console_printf(eConsoleMsgType msgType, const char *args, ...) {
	char StrBuff[256];
	uint16_t TextColor;

	color.CLI_textColor = GREEN;
	color.CLI_bacgroundeColor = BLACK;

	switch (msgType){
	case MsgInfo:
		TextColor = color.CLI_textColor;
		break;
	case MsgWarning:
		TextColor = ORANGE;
		break;
	case MsgError:
		TextColor = RED;
		break;
	}
	va_list ap;
	va_start(ap, args);
	vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
	va_end(ap);

	draw_string(0, ConsoleLine * LineHeight, FONTID_6X8M, (uint8_t*)StrBuff, TextColor, WHITE, 1);
    printf("%s", StrBuff);

    if (msgType != MsgInfo)
    {
    	for (uint32_t i = 0; i < 50000; i ++) __NOP();
    }


	if (++ConsoleLine > 320 / LineHeight)
    {
		ConsoleLine = 0;
		for (uint32_t i = 0; i < 50000; i ++) __NOP();
		clear_screen();
		fill_screen(color.CLI_bacgroundeColor);
		delay(1000);
    }
}

void stringLine (char *String) {
	draw_string(0, ConsoleLine * LineHeight, FONTID_6X8M, "�", RED, YELLOW,1);
	draw_string(20, ConsoleLine * LineHeight, FONTID_6X8M, String, RED, WHITE, 1);
}




