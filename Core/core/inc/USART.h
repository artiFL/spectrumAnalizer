#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stm32f7xx.h"
#include "clock.h"

#define USART_T					USART2
#define _CR						0x0D

volatile char RessivBuffer[100];
volatile uint8_t address;

typedef struct {
	uint8_t	 USARTEnable_flag;
	uint32_t Boudrate_USART;
}USART_configuration_TypeDef;
USART_configuration_TypeDef USART_Conf;

typedef struct {
	volatile uint8_t ressiveByte;
	volatile uint8_t ressiveString;
	volatile uint8_t ressiveArray;
}USART_Flag_TypeDef;
USART_Flag_TypeDef USART_Flag;

void USART_Init(uint32_t boudrate, uint8_t numberUSART);
void SendByte (uint8_t data);
void print_str (const char *args, ...);
void get_byte(volatile char* array);
void get_array_str (volatile char* array);

/*Dec Oct Hex  Binary   Value
 --- --- --- -------- --------------------------
 000 000 000 00000000 NUL (Null char.)
 001 001 001 00000001 SOH (Start of Header)
 002 002 002 00000010 STX (Start of Text)
 003 003 003 00000011 ETX (End of Text)
 004 004 004 00000100 EOT (End of Transmission)
 005 005 005 00000101 ENQ (Enquiry)
 006 006 006 00000110 ACK (Acknowledgment)
 007 007 007 00000111 BEL (Bell)
 008 010 008 00001000 BS  (Backspace)
 009 011 009 00001001 HT  (Horizontal Tab)
 010 012 00A 00001010 LF  (Line Feed)
 011 013 00B 00001011 VT  (Vertical Tab)
 012 014 00C 00001100 FF  (Form Feed)
 013 015 00D 00001101 CR  (Carriage Return)
 014 016 00E 00001110 SO  (Shift Out)
 015 017 00F 00001111 SI  (Shift In)
 016 020 010 00010000 DLE (Data Link Escape)
 017 021 011 00010001 DC1 (XON)(Device Control 1)
 018 022 012 00010010 DC2 (Device Control 2)
 019 023 013 00010011 DC3 (XOFF)(Device Control 3)
 020 024 014 00010100 DC4 (Device Control 4)
 021 025 015 00010101 NAK (Negative Ack.)
 022 026 016 00010110 SYN (Synchronous Idle)
 023 027 017 00010111 ETB (End of Trans. Block)
 024 030 018 00011000 CAN (Cancel)
 025 031 019 00011001 EM  (End of Medium)
 026 032 01A 00011010 SUB (Substitute)
 027 033 01B 00011011 ESC (Escape)
 028 034 01C 00011100 FS  (File Separator)
 029 035 01D 00011101 GS  (Group Separator)
 030 036 01E 00011110 RS  (Record Separator)
 031 037 01F 00011111 US  (Unit Separator)
 032 040 020 00100000 SP  (Space)
 033 041 021 00100001 !   (exclamation mark)
 034 042 022 00100010 "   (double quote)
 035 043 023 00100011 #   (number sign)
 036 044 024 00100100 $   (dollar sign)
 037 045 025 00100101 %   (percent)
 038 046 026 00100110 &   (ampersand)
 039 047 027 00100111 '   (apostophe)
 040 050 028 00101000 (   (L/opening parenthesis)
 041 051 029 00101001 )   (R/closing parenthesis)
 042 052 02A 00101010 *   (asterisk)
 043 053 02B 00101011 +   (plus)
 044 054 02C 00101100 ,   (comma)
 045 055 02D 00101101 -   (minus or dash)
 046 056 02E 00101110 .   (dot)
 047 057 02F 00101111 /   (forward slash)
 048 060 030 00110000 0
 049 061 031 00110001 1
 050 062 032 00110010 2
 051 063 033 00110011 3
 052 064 034 00110100 4
 053 065 035 00110101 5
 054 066 036 00110110 6
 055 067 037 00110111 7
 056 070 038 00111000 8
 057 071 039 00111001 9
 058 072 03A 00111010 :   (colon)
 059 073 03B 00111011 ;   (semi-colon)
 060 074 03C 00111100 <   (less than)
 061 075 03D 00111101 =   (equal sign)
 062 076 03E 00111110 >   (greater than)
 063 077 03F 00111111 ?   (question mark)
 064 100 040 01000000 @   (AT symbol)
 065 101 041 01000001 A
 066 102 042 01000010 B
 067 103 043 01000011 C
 068 104 044 01000100 D
 069 105 045 01000101 E
 070 106 046 01000110 F
 071 107 047 01000111 G
 072 110 048 01001000 H
 073 111 049 01001001 I
 074 112 04A 01001010 J
 075 113 04B 01001011 K
 076 114 04C 01001100 L
 077 115 04D 01001101 M
 078 116 04E 01001110 N
 079 117 04F 01001111 O
 080 120 050 01010000 P
 081 121 051 01010001 Q
 082 122 052 01010010 R
 083 123 053 01010011 S
 084 124 054 01010100 T
 085 125 055 01010101 U
 086 126 056 01010110 V
 087 127 057 01010111 W
 088 130 058 01011000 X
 089 131 059 01011001 Y
 090 132 05A 01011010 Z
 091 133 05B 01011011 [   (left/opening bracket)
 092 134 05C 01011100 \   (back slash)
 093 135 05D 01011101 ]   (right/closing bracket)
 094 136 05E 01011110 ^   (caret/cirumflex)
 095 137 05F 01011111 _   (underscore)
 096 140 060 01100000 `
 097 141 061 01100001 a
 098 142 062 01100010 b
 099 143 063 01100011 c
 100 144 064 01100100 d
 101 145 065 01100101 e
 102 146 066 01100110 f
 103 147 067 01100111 g
 104 150 068 01101000 h
 105 151 069 01101001 i
 106 152 06A 01101010 j
 107 153 06B 01101011 k
 108 154 06C 01101100 l
 109 155 06D 01101101 m
 110 156 06E 01101110 n
 111 157 06F 01101111 o
 112 160 070 01110000 p
 113 161 071 01110001 q
 114 162 072 01110010 r
 115 163 073 01110011 s
 116 164 074 01110100 t
 117 165 075 01110101 u
 118 166 076 01110110 v
 119 167 077 01110111 w
 120 170 078 01111000 x
 121 171 079 01111001 y
 122 172 07A 01111010 z
 123 173 07B 01111011 {   (left/opening brace)
 124 174 07C 01111100 |   (vertical bar)
 125 175 07D 01111101 }   (right/closing brace)
 126 176 07E 01111110 ~   (tilde)
 127 177 07F 01111111 DEL (delete)
 */
