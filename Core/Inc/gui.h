#pragma once
#include "fft.h"

#include "display.h"

typedef struct
{
	uint16_t start_x_window;
	uint16_t start_y_window;
	uint16_t end_x_window;
	uint16_t end_y_window;

	uint16_t start_x_line;
	uint16_t start_y_line;
	uint16_t next_step_x_line;
	uint16_t next_step_y_line;
	uint16_t color_line;
	uint16_t shift_y_line;
	uint16_t shift_x_line;

	uint16_t left_edge_bandwidth;
	uint16_t right_edge_bandwidth;
	uint16_t bandwidth_display;



}smainWindowTypeDef;

smainWindowTypeDef ui;



void draw_window (void);
void change_bandwidth_display(uint16_t pix_shift);
