#pragma once

#define DISPLAY_H

#include "stm32f7xx.h"
#include "math.h"
#include "color_command.h"
#include <font.h>
#include "stdlib.h"
#include "string.h"


#define REMAP
#define A16
//#define A18




#ifdef A16

#ifndef REMAP
#define DATA_A				0x6001FFFF

#else
#define DATA_A				0xC001FFFF
#endif
//0xC0010000
#else

#ifndef REMAP
#define DATA_A				0x60000001

#else
#define DATA_A				0xC0000001
#endif

#endif

#ifndef REMAP
#define LCD_BASE    ((uint32_t)(0x60000000 | DATA_A))
#define LCD         ((LCD_TypeDef *) LCD_BASE)
#endif

#ifdef REMAP
#define LCD_BASE    ((uint32_t)(0xC0000000 | DATA_A))
#define LCD         ((LCD_TypeDef *) LCD_BASE)
#endif

typedef struct
{                             		// ��������� ���������� �� �������. ������� ����� � ������.
	volatile uint8_t RAM;   		// 0x6001FFFE  >> 1 = 0x0000FFFF bit 16 = 0 �.�. DATA
	volatile uint8_t REG;  			// 0x6001FFFE + 2 (�.�. uint16) = 0x60020000 >> 1 = 0x00010000 bit 16 = 1 �.�. CMD

} LCD_TypeDef;

//---------------------Settings-------------------------//
#define LCD_TYPE						ILI9486
#define INTERFACE						INTERFACE_FMC
#define MOD								DIRECT_MOD
//------------------------------------------------------//
#define ILI9486							0

#define INTERFACE_FMC					0
#define INTERFACE_PROG_FMC				1

#define BUFFER_MOD						0
#define DIRECT_MOD						1
//------------------------------------------------------//

#if (LCD_TYPE == ILI9486)

#define TFTWIDTH   						480								//< ������
#define TFTHEIGHT  						320								//< ������

	#if (INTERFACE == INTERFACE_FMC)
		#define FMC_Bank1_NORSRAM1                             ((uint32_t)0x00000000)
		#define FMC_Bank1_NORSRAM2                             ((uint32_t)0x00000002)
		#define FMC_Bank1_NORSRAM3                             ((uint32_t)0x00000004)
		#define FMC_Bank1_NORSRAM4                             ((uint32_t)0x00000006)
		#define FMC_Bank2_NAND                                 ((uint32_t)0x00000010)
		#define FMC_Bank3_NAND                                 ((uint32_t)0x00000100)
	#endif

	volatile uint16_t Screen[240 * 240];

//
	#if (INTERFACE == INTERFACE_PROG_FMC)
/*
 * CS	-	F3
 * RD	-	A3
 * D/C	-	C3
 * RS	-	C0
 * RST	-	F5
 * F_CS	-	F10
 *
 * D0	-	F12
 * D1	-	D15
 * D2	-	F15
 * D3	-	E13
 * D4	-	F14
 * D5	-	E11
 * D6	-	E9
 * D7	-	F13
 */
	#endif



//
#if (MOD == BUFFER_MOD)

	uint16_t ScreenBuff[240 * 240];			//not relised

#endif
//
#endif

void display_init(uint8_t Rotation);
//----------------------------------------------------------------------------------------------------------------------
void set_XY (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
//----------------------------------------------------------------------------------------------------------------------
void Image (uint16_t *buff);
void fill_screen (uint16_t color);
void set_pixel (uint16_t poX, uint16_t poY, uint16_t color);
void clear_screen (void);
//----------------------------------------------------------------------------------------------------------------------
void Push_Color (uint16_t color);
//----------------------------------------------------------------------------------------------------------------------
void draw_vertical_line(uint16_t poX, uint16_t poY, uint16_t length, uint16_t color);
void draw_horizontal_line (uint16_t poX, uint16_t poY, uint16_t length, uint16_t color);
void draw_rectangle (uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY ,uint16_t color);
void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void draw_circle (uint16_t poX, uint16_t poY, uint16_t radius, uint16_t color);
void draw_triangle (uint16_t poX1, uint16_t poY1, uint16_t poX2, uint16_t poY2, uint16_t poX3, uint16_t poY3, uint16_t color);
void draw_vertical_punct(uint16_t x, uint16_t y, uint16_t light, uint16_t segment, uint16_t color);
void draw_horizontal_punct(uint16_t x, uint16_t y, uint16_t light, uint16_t segment, uint16_t color);
//----------------------------------------------------------------------------------------------------------------------
uint8_t draw_char (uint16_t x, uint16_t y, uint8_t FontID, uint8_t Char, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg);
uint16_t draw_string (uint16_t x, uint16_t y, uint8_t FontID, char *Str, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg);
void print (char *String);
void printX (uint16_t x, uint16_t y, char *String);
uint16_t draw_number (uint16_t x, uint16_t y, uint8_t FontID, uint16_t Number, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg);

void DMA_Init_Buff (void);
void DMA_send16b (uint16_t *Data, uint32_t size);

