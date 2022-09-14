#include "display.h"

static uint8_t rotation = 0;						//position

#if (INTERFACE == INTERFACE_FMC)

static uint16_t _width = TFTWIDTH;			//shirina
static uint16_t _height = TFTHEIGHT;		//visota
	static void send_data (uint8_t data)
	{
		 LCD->RAM = data;
	}

	static void send_command(uint8_t command)
	{
		LCD->REG = command;
	}

	static void GPIO_FMC_init (void)
	{
			/*D0 - PD14		A0 - PF0 - RS
			 * 	   			A16 - PD11 -  ADDRES SELECT
			 *D1 - PD15		NE1 - PC7 - CS
			 *D2 - PD0		NOE - PD4 - RD
			 *D3 - PD1		NWE - PD5 - WR
			 *D4 - PE7		RST - PB14
			 *D5 - PE8		CS - ---------------------------------------------
			 *D6 - PE9
			 *D7 - PE10

     		AFR[1]
			|  15   |   14  |  13   |  12   |
			|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
			| | | | | | | | | | | | | | | | |
			|   11  |   10  |   9   |   8   |

			AFR[0]
			|   7   |    6  |   5   |   4   |
			|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
			| | | | | | | | | | | | | | | | |
			|   3   |    2  |   1   |   0   |
			*/

			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

			GPIOD->MODER = 		0xa0000a0a;
			GPIOD->OSPEEDR = 	0xf0000f0f;
			GPIOD->AFR[0] = 	0xcc00cc;
			GPIOD->AFR[1] = 	0xcc000000;





#ifdef A16

			GPIOD->MODER 	|= GPIO_MODER_MODER11_1;
			GPIOD->OSPEEDR  |= GPIO_OSPEEDER_OSPEEDR11;
			GPIOD->AFR[1]	|= GPIO_AFRH_AFRH3_2 | GPIO_AFRH_AFRH3_3;
#endif
#ifdef A18
			GPIOD->MODER 	|= GPIO_MODER_MODER13_1;
			GPIOD->OSPEEDR  |= GPIO_OSPEEDER_OSPEEDR13;							//a18
			GPIOD->AFR[1]	|= GPIO_AFRL_AFRL5_3 | GPIO_AFRL_AFRL5_2;
#endif
#ifndef A16
#ifndef A18

			GPIOF->MODER 	|= GPIO_MODER_MODER0;
			GPIOF->OSPEEDR  |= GPIO_OSPEEDER_OSPEEDR0;
			GPIOF->AFR[0]	|= GPIO_AFRL_AFRL0_2 & GPIO_AFRL_AFRL0_3;
#endif
#endif

			GPIOE->MODER = 		0x2a8000;
			GPIOE->OSPEEDR = 	0x3fc000;
			GPIOE->AFR[0] = 	0xc0000000;
			GPIOE->AFR[1] = 	0xccc;

			GPIOF->MODER = 		0x2;
			GPIOF->OSPEEDR = 	0x3;
			GPIOF->AFR[0] = 	0xc;

			GPIOC->MODER = 		0x8000;
			GPIOC->OSPEEDR = 	0xc000;
			GPIOC->AFR[0] = 	0x90000000;
		}

	static void FSMC_init (void)
	{
			RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
			RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
#ifdef REMAP
			SYSCFG->MEMRMP |= SYSCFG_MEMRMP_SWP_FMC_0;		// Remap adress array 0x60000000 -> 0xC0000000
#endif
			FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1 + 1] = (uint32_t)0x00000000;				// Clear register
			FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1] = 	  (uint32_t)0x00000000;				// Clear register


			FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1] |=  1 << FMC_BCR1_WFDIS_Pos		|		//	Write FIFO Disable
													0 << FMC_BCR1_CCLKEN_Pos	|		//	Continous clock enable
													1 << FMC_BCR1_CBURSTRW_Pos	|		//	Write burst enable
													0 << FMC_BCR1_ASYNCWAIT_Pos |		//	Asynchronous wait
													0 << FMC_BCR1_EXTMOD_Pos	|		//	Extended mode enable
													0 << FMC_BCR1_WAITEN_Pos	|		//	Wait enable bit
													1 << FMC_BCR1_WREN_Pos		|		//	Write enable bit
													1 << FMC_BCR1_WAITCFG_Pos	|		//	Wait timing configuration
													0 << FMC_BCR1_WAITPOL_Pos	|		//	Wait signal polarity bit
													1 << FMC_BCR1_BURSTEN_Pos	|		//	Burst enable bit
													1 << FMC_BCR1_FACCEN_Pos	|		//	Flash access enable
													0 << FMC_BCR1_MWID_Pos		|		//	MWID[1:0] bits (Memory data bus width)		0 = 8b 1 = 16b
													0 << FMC_BCR1_MTYP_Pos		|		//	MTYP[1:0] bits (Memory type)				0 = SRAM 1 = CRAM 2 = NOR
													1 << FMC_BCR1_MUXEN_Pos		|		//	Address/data multiplexing enable bit
													1 << FMC_BCR1_MBKEN_Pos	;			//	Memory bank enable bit

			FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1 + 1]  |= 2 << FMC_BTR1_ADDSET_Pos  |    // Address setup phase duration 0..F * HCLK
														2 << FMC_BTR1_ADDHLD_Pos  |    // Address-hold phase duration 1..F * 2 * HCLK
														3 << FMC_BTR1_DATAST_Pos  |    // Data-phase duration 1..FF * 2 * HCLK
														0 << FMC_BTR1_BUSTURN_Pos |    // Bus turnaround phase duration 0...F
														2 << FMC_BTR1_CLKDIV_Pos  |    // for FSMC_CLK signal 1 = HCLK/2, 2 = HCLK/3 ...  F= HCLK/16
														2 << FMC_BTR1_DATLAT_Pos  |    // Data latency for synchronous NOR Flash memory 0(2CK)...F(17CK)
														1 << FMC_BTR1_ACCMOD_Pos;      // Access mode 0 = A, 1 = B, 2 = C, 3 = D Use w/EXTMOD bit
		}

//
#endif
#if (INTERFACE == INTERFACE_PROG_FMC)
		static uint16_t _width = TFTWIDTH;
		static uint16_t _height = TFTHEIGHT;

		static inline void CS_HIGH() 			{GPIOF->ODR |= GPIO_ODR_ODR_3;}
		static inline void CS_LOW() 			{GPIOF->ODR &= ~GPIO_ODR_ODR_3;}

		static inline void WRITE_DISPLAY_HIGH() {GPIOC->ODR |= GPIO_ODR_ODR_0;}
		static inline void WRITE_DISPLAY_LOW() 	{GPIOC->ODR &= ~GPIO_ODR_ODR_0;}

		static inline void DATA_COMMAND_HIGH() 	{GPIOC->ODR |= GPIO_ODR_ODR_3;}
		static inline void DATA_COMMAND_LOW() 	{GPIOC->ODR &= ~GPIO_ODR_ODR_3;}

		static void GPIO_init(void)
		{
			//ENABLE hardware driver ili9486 on GPIOA A0-A7

			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN \
						 |  RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN;


			GPIOA->MODER |= GPIO_MODER_MODER3_0;				//DATA RD
			GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;

			GPIOC->MODER |= GPIO_MODER_MODER0_0;				//LCD WR
			GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;

			GPIOC->MODER |= GPIO_MODER_MODER3_0;				//LCD RS
			GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;

			GPIOF->MODER |= GPIO_MODER_MODER3_0;				//LCD CS
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;

			GPIOF->MODER |= GPIO_MODER_MODER5_0;				//LCD RST
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;

			GPIOF->MODER |= GPIO_MODER_MODER10_0;				//F_CS
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;


			GPIOF->MODER |= GPIO_MODER_MODER12_0;				//LCD D0
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_1;

			GPIOD->MODER |= GPIO_MODER_MODER15_0;				//LCD D1
			GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_1;

			GPIOF->MODER |= GPIO_MODER_MODER15_0;				//LCD D2
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_1;

			GPIOE->MODER |= GPIO_MODER_MODER13_0;				//LCD D3
			GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;

			GPIOF->MODER |= GPIO_MODER_MODER14_0;				//LCD D4
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;

			GPIOE->MODER |= GPIO_MODER_MODER11_0;				//LCD D5
			GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;

			GPIOE->MODER |= GPIO_MODER_MODER9_0;				//LCD D6
			GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;

			GPIOF->MODER |= GPIO_MODER_MODER13_0;				//LCD D7
			GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;

			GPIOF->BSRR |= GPIO_BSRR_BS_5;
			GPIOA->BSRR |= GPIO_BSRR_BS_3;
		}

		static void send_command (uint8_t command)
		{
			CS_LOW();
			DATA_COMMAND_LOW();

			command & 0x01 ? GPIOF->ODR |= GPIO_ODR_ODR_12 : GPIOF->ODR &= ~GPIO_ODR_ODR_12
			command & 0x02 ? GPIOF->ODR |= GPIO_ODR_ODR_15 : GPIOF->ODR &= ~GPIO_ODR_ODR_15
			command & 0x04 ? GPIOF->ODR |= GPIO_ODR_ODR_15 : GPIOF->ODR &= ~GPIO_ODR_ODR_15
			command & 0x08 ? GPIOF->ODR |= GPIO_ODR_ODR_13 : GPIOF->ODR &= ~GPIO_ODR_ODR_13
			command & 0x10 ? GPIOF->ODR |= GPIO_ODR_ODR_14 : GPIOF->ODR &= ~GPIO_ODR_ODR_14
			command & 0x20 ? GPIOF->ODR |= GPIO_ODR_ODR_11 : GPIOF->ODR &= ~GPIO_ODR_ODR_11
			command & 0x40 ? GPIOF->ODR |= GPIO_ODR_ODR_9 : GPIOF->ODR &= ~GPIO_ODR_ODR_9
			command & 0x80 ? GPIOF->ODR |= GPIO_ODR_ODR_13 : GPIOF->ODR &= ~GPIO_ODR_ODR_13

			WRITE_DISPLAY_LOW();
			WRITE_DISPLAY_HIGH();
		    DATA_COMMAND_HIGH();

			CS_HIGH();
		}

		static void send_data (uint8_t data)
		{
			CS_LOW();

		    if(data & 0x01) GPIOF->ODR |= GPIO_ODR_ODR_12; else  GPIOF->ODR &= ~GPIO_ODR_ODR_12; \
		    if(data & 0x02) GPIOD->ODR |= GPIO_ODR_ODR_15; else  GPIOD->ODR &= ~GPIO_ODR_ODR_15; \
		    if(data & 0x04) GPIOF->ODR |= GPIO_ODR_ODR_15; else  GPIOF->ODR &= ~GPIO_ODR_ODR_15; \
		    if(data & 0x08) GPIOE->ODR |= GPIO_ODR_ODR_13; else GPIOE->ODR &= ~GPIO_ODR_ODR_13; \
		    if(data & 0x10) GPIOF->ODR |= GPIO_ODR_ODR_14; else  GPIOF->ODR &= ~GPIO_ODR_ODR_14; \
		    if(data & 0x20) GPIOE->ODR |= GPIO_ODR_ODR_11; else  GPIOE->ODR &= ~GPIO_ODR_ODR_11; \
		    if(data & 0x40) GPIOE->ODR |= GPIO_ODR_ODR_9; else  GPIOE->ODR &= ~GPIO_ODR_ODR_9; \
		    if(data & 0x80) GPIOF->ODR |= GPIO_ODR_ODR_13; else  GPIOF->ODR &= ~GPIO_ODR_ODR_13;

		    WRITE_DISPLAY_LOW();
			WRITE_DISPLAY_HIGH();

			CS_HIGH();
		}


#endif


static void set_rotation(uint8_t m)
{
    rotation = m % 4; // can't be higher than 3
    switch (rotation)
    {
        case 0:
            m = (MADCTL_MX | MADCTL_BGR);
            _width  = TFTWIDTH + 1;
            _height = TFTHEIGHT + 1;
            break;
        case 1:
            m = (MADCTL_MV | MADCTL_BGR);
            _width  = TFTHEIGHT;
            _height = TFTWIDTH;
            break;
        case 2:
            m = (MADCTL_MY | MADCTL_BGR);
            _width  = TFTWIDTH + 1;
            _height = TFTHEIGHT + 1;
            break;
        case 3:
            m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
            _width  = TFTHEIGHT;
            _height = TFTWIDTH;
            break;
    }
    send_command(MEMORYACCESSCONTROL);
    send_data(m);
}

void display_init(uint8_t rotation)
{

#if (INTERFACE == INTERFACE_FMC)
	GPIO_FMC_init();
	FSMC_init();
#endif

#if (INTERFACE == INTERFACE_PROG_FMC)
	GPIO_init();
#endif

	send_command(SOFTTRESET);//soft reset
	for (uint32_t i = 0; i < 1000000; i ++) __NOP();

    // Interface Mode Control
	send_command(0xb0);
	send_data(0x00);
    // Interface Pixel Format, 16 bits / pixel
	send_command(0x3A);
	send_data(0x55);
    // PGAMCTRL(Positive Gamma Control)
	send_command(0xE0);
    send_data(0x0F);
    send_data(0x1F);
    send_data(0x1C);
    send_data(0x0C);
    send_data(0x0F);
    send_data(0x08);
    send_data(0x48);
    send_data(0x98);
    send_data(0x37);
    send_data(0x0A);
    send_data(0x13);
    send_data(0x04);
    send_data(0x11);
    send_data(0x0D);
    send_data(0x00);
    // NGAMCTRL (Negative Gamma Correction)
    send_command(0xE1);
    send_data(0x0F);
    send_data(0x32);
    send_data(0x2E);
    send_data(0x0B);
    send_data(0x0D);
    send_data(0x05);
    send_data(0x47);
    send_data(0x75);
    send_data(0x37);
    send_data(0x06);
    send_data(0x10);
    send_data(0x03);
    send_data(0x24);
    send_data(0x20);
    send_data(0x00);
    // VCOM Control
    send_command(0xC5);
    send_data(0x00);
    send_data(0x00);
    send_data(0x00);
    send_data(0x00);
    // Power Control 3
    send_command(0xC2);
    send_data(0x44);
    // Memory Access Control
    send_command(0x36);
    send_data(0x08);
    // Set rotation
    // # Sleep OUT

    send_command(SLEEPOUT);    	//Exit Sleep
	for (uint32_t i = 0; i < 100000; i ++) __NOP();
	send_command(DISPLAYON);    //Display on
	send_command(MEMORYWRITE);
	for (uint32_t i = 0; i < 10000; i ++) __NOP();

	set_rotation(rotation);
}


#if (MOD == DIRECT_MOD)

static void set_column (uint16_t StartCol, uint16_t EndCol)
{
	send_command(COLUMNADDRSET);
	send_data(StartCol>>8);
	send_data(StartCol);
	send_data(EndCol>>8);
	send_data(EndCol);
}

static void set_page (uint16_t StartPage, uint16_t EndPage)
{
	send_command(PAGEADDRSET);
	send_data(StartPage>>8);
	send_data(StartPage);
	send_data(EndPage>>8);
	send_data(EndPage);
}

void set_XY (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	set_column(x1, x2);
	set_page(y1, y2);
	send_command(MEMORYWRITE);
}

void screen_set_image (uint16_t *buff)
{
	set_XY(0, 0, _height, _width);

	for (uint32_t i = 0; i < _height * _width; i ++  ) {

		send_data((buff[i]) >> 8);
		send_data(buff[i]);
	}
}

void fill_screen (uint16_t color)
{
	set_XY(0, 0, _height, _width);

	for (uint32_t i = 0; i < _height * _width; i ++ ) {

		send_data(color >> 8);
		send_data(color);
	}
}

void set_pixel (uint16_t poX, uint16_t poY, uint16_t color)
{
	set_XY(poX, poY, poX, poY);
	send_data(color >> 8);
	send_data(color);
}

void clear_screen (void)
{
	set_XY(0, 0, _height, _width);
	for (uint32_t i = 0; i < (_height * _width) * 2; i ++ ) {
		send_data(BLACK);
	}
}

#endif
#if (MOD == BUFFER_MOD)

static void set_column (uint16_t StartCol, uint16_t EndCol) {//�� �� ��, ��� ������������ �� 8 ���
	send_command(COLUMNADDRSET);
	send_data(StartCol>>8);
	send_data(StartCol);
	send_data(EndCol>>8);
	send_data(EndCol);
}
static void set_page (uint16_t StartPage, uint16_t EndPage)
{
	send_command(PAGEADDRSET);
	send_data(StartPage>>8);
	send_data(StartPage);
	send_data(EndPage>>8);
	send_data(EndPage);
}

void set_XY (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	set_column(x1, x2);
	set_page(y1, y2);
	send_command(MEMORYWRITE);
}
void set_pixel (uint16_t poX, uint16_t poY, uint16_t color)
{
	set_XY(poX, poY, poX, poY);
	ScreenBuff[(poY * _width) + poX] = color;
}
void clear_screen (void){
	set_XY(0, 0, _height, _width);
	memset(ScreenBuff,0x0000,_height * _width);
}
void fill_screen (uint16_t color)
{
	set_XY(0, 0, _height, _width);

	memset(ScreenBuff,color,_height * _width);
}
#endif

void draw_vertical_line(uint16_t poX, uint16_t poY, uint16_t length, uint16_t color)
{
	for(int i = 0; i < length; i++)
		set_pixel(poX, poY + i, color);
}
void draw_horizontal_line (uint16_t poX, uint16_t poY, uint16_t length, uint16_t color)
{
	for(int i = 0; i < length; i++)

		set_pixel(poX + i, poY, color);
}
void draw_rectangle (uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY ,uint16_t color)
{
	uint16_t lengthX,lengthY;

	lengthX = endX - startX;
	lengthY = endY - startY;

	draw_vertical_line(startX, startY, lengthY, color);
	draw_horizontal_line(startX, startY, lengthX, color);

	draw_vertical_line(startX + lengthX, startY, lengthY, color);
	draw_horizontal_line(startX, startY + lengthY, lengthX, color);
}
void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	const uint16_t deltaX = fabs(x2 - x1);
	const uint16_t deltaY = fabs(y2 - y1);
	const uint16_t signX = x1 < x2 ? 1 : -1;
	const uint16_t signY = y1 < y2 ? 1 : -1;

	uint16_t error = deltaX - deltaY;

	set_pixel(x2, y2, color);

		while (x1 != x2 || y1 != y2){

			set_pixel(x1, y1, color);
			const int16_t error2 = error * 2;

	    if (error2 > -deltaY){

	      error -= deltaY;
	      x1 += signX;

	    }

	    if (error2 < deltaX){

	      error += deltaX;
	      y1 += signY;

	    }
	  }
}
void draw_circle (uint16_t poX, uint16_t poY, uint16_t radius, uint16_t color)
{
    int x = -radius, y = 0, err = 2 - 2 * radius, e2;

    do {

        set_pixel(poX - x, poY + y, color);
        set_pixel(poX + x, poY + y, color);
        set_pixel(poX + x, poY - y, color);
        set_pixel(poX - x, poY - y, color);

        e2 = err;

        if (e2 <= y) {

            err += ++y * 2 + 1;

            if (-x == y && e2 <= x) e2 = 0;
        }

        if (e2 > x) err += ++x * 2 + 1;

    }

    while (x <= 0);
}
void draw_triangle (uint16_t poX1, uint16_t poY1, uint16_t poX2, uint16_t poY2, uint16_t poX3, uint16_t poY3, uint16_t color)
{
	draw_line(poX1, poY1, poX2, poY2, color);
	draw_line(poX1, poY1, poX3, poY3, color);
	draw_line(poX2, poY2, poX3, poY3, color);
}
void draw_vertical_punct(uint16_t x, uint16_t y, uint16_t light, uint16_t segment, uint16_t color)
{
	for (uint16_t i = y; i < light; i = i + segment + 10) {

		draw_vertical_line(x, i, segment, color);
	}
}
void draw_horizontal_punct(uint16_t x, uint16_t y, uint16_t light, uint16_t segment, uint16_t color)
{
	for (uint16_t i = x; i < light; i = i + segment + 10) {

		draw_horizontal_line(i, y, segment, color);
	}
}
//--------------------------------------------------------------------------------
uint8_t draw_char (uint16_t x, uint16_t y, uint8_t FontID, uint8_t Char, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg)
{
	uint8_t *pCharTable = font_GetFontStruct(FontID, Char);
	uint8_t CharWidth = font_GetCharWidth(pCharTable);//9
	uint8_t CharHeight = font_GetCharHeight(pCharTable);//16
	pCharTable += 2;

	if (FontID == FONTID_6X8M) {

			for (uint8_t row = 0; row < CharHeight; row ++)
			{
				for (uint8_t col = 0; col < CharWidth; col ++)
				{
					if (pCharTable[row] & (1 << (7 - col)))
					{
						set_pixel(x + col, y + row, TextColor);
					}
					else if (!TransparentBg)
					{
						set_pixel(x + col, y + row, BgColor);
					}
				}
			}
	}
	else {
		for (uint8_t row = 0; row < CharHeight; row ++)
		{
			for (uint8_t col = 0; col < CharWidth; col ++)
			{
				if (col < 8)
				{
					if (pCharTable[row * 2] & (1 << (7 - col)))
					{
						set_pixel(x + col, y + row, TextColor);
					}
					else if (!TransparentBg)
					{
						set_pixel(x + col, y + row, BgColor);
					}
				}
				else {
					if (pCharTable[(row * 2) + 1] & (1 << (15 - col)))
					{
						set_pixel(x + col, y + row, TextColor);
					}
					else if (!TransparentBg)
					{
						set_pixel(x + col, y + row, BgColor);
					}
				}
			}
		}
	}

	return CharWidth;
}
uint16_t draw_string (uint16_t x, uint16_t y, uint8_t FontID, char *Str, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg)
{
	uint8_t *pCharTable = font_GetFontStruct(FontID, Str[0]);
	uint8_t done = 0;
	uint16_t XStart = x;
	uint8_t StrHeigh = font_GetCharHeight(pCharTable);

	while (!done) {

		switch (*Str) {

		case '\0':
			done = 1;
			break;

		case '\n':
			y += StrHeigh = font_GetCharHeight(pCharTable);
			break;

		case '\r':
			x = XStart;
		break;

		default:
			if (TransparentBg) {
				x += draw_char(x, y, FontID, *Str, TextColor, 0, 1);
			}
			else {
				x += draw_char(x, y, FontID, *Str, TextColor, BgColor, 0);
			}
			StrHeigh = font_GetCharHeight(font_GetFontStruct(FontID, *Str));
			break;
		}
		Str++;
	}
	return x;
}
void printX (uint16_t x, uint16_t y, char *String)
{
	draw_string(x, y, FONTID_16F, (uint8_t*)String, WHITE, WHITE, 1);
}
uint16_t draw_number (uint16_t x, uint16_t y, uint8_t FontID, uint16_t Number, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg)
{
	uint8_t n1,n2,n3,n4;

	if (Number > 9 && Number < 100) {
		n2 = (Number - (Number % 10)) / 10;
		n1 =  Number % 10;

		if (TransparentBg)
		{
			x += draw_char(x, y, FontID, n2 + 0x30, TextColor, 0, 1);
			x += draw_char(x, y, FontID, n1 + 0x30, TextColor, 0, 1);
		}
		else {
			x += draw_char(x, y, FontID, n2 + 0x30, TextColor, BgColor, 0);
			x += draw_char(x, y, FontID, n1 + 0x30, TextColor, BgColor, 0);
		}
	}
	else if (Number > 99 && Number < 1000)
	{
	    n3 = (Number - (Number % 100)) / 100;
		n2 = ((Number - (Number % 10)) - (Number - (Number % 100))) / 10;
		n1 = Number % 10;
		if (TransparentBg)
		{
			x += draw_char(x, y, FontID, n3 + 0x30, TextColor, 0, 1);
			x += draw_char(x, y, FontID, n2 + 0x30, TextColor, 0, 1);
			x += draw_char(x, y, FontID, n1 + 0x30, TextColor, 0, 1);
		}
		else {
			x += draw_char(x, y, FontID, n3 + 0x30, TextColor, BgColor, 0);
			x += draw_char(x, y, FontID, n2 + 0x30, TextColor, BgColor, 0);
			x += draw_char(x, y, FontID, n1 + 0x30, TextColor, BgColor, 0);
		}
	}
	else if (Number > 999 && Number < 10000)
	{
	    n4 = (Number - (Number % 1000)) / 1000;
	    n3 = ((Number - (Number % 100)) - (Number - (Number % 1000))) / 100;
	    n2 = ((Number - (Number % 10)) - (Number - (Number % 100))) / 10;
	    n1 = Number % 10;
		if (TransparentBg)
		{
			x += draw_char(x, y, FontID, n4 + 0x30, TextColor, 0, 1);
			x += draw_char(x, y, FontID, n3 + 0x30, TextColor, 0, 1);
			x += draw_char(x, y, FontID, n2 + 0x30, TextColor, 0, 1);
			x += draw_char(x, y, FontID, n1 + 0x30, TextColor, 0, 1);
		}

		else {
			x += draw_char(x, y, FontID, n4 + 0x30, TextColor, BgColor, 0);
			x += draw_char(x, y, FontID, n3 + 0x30, TextColor, BgColor, 0);
			x += draw_char(x, y, FontID, n2 + 0x30, TextColor, BgColor, 0);
			x += draw_char(x, y, FontID, n1 + 0x30, TextColor, BgColor, 0);
		}
	}
	else if (Number > 9999)
	{
		draw_string (x, y, FontID, "> 9999", TextColor, BgColor, 1);
	}
	else {
		if (TransparentBg)
		{
			x += draw_char(x, y, FontID, Number + 0x30, TextColor, 0, 1);
		}
		else {
			x += draw_char(x, y, FontID, Number + 0x30, TextColor, BgColor, 0);
		}
	}
	return (0);
}

