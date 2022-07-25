#include "gui.h"
#include "new_fft.h"

extern float fft_Sbuff[FFT_SIZE];
extern float fft_Dbuff[FFT_SIZE * 2];

void draw_window(void) {
	//fft_force();

	FFT_Process();
	clear_screen();

	ui.start_x_window = 5;
	ui.start_y_window = 40;
	ui.end_x_window = TFTWIDTH - ui.start_x_window;
	ui.end_y_window = TFTHEIGHT - 5;

	ui.color_line = RED;

	change_bandwidth_display(0);

	draw_rectangle(ui.start_x_window, ui.start_y_window, ui.end_x_window, ui.end_y_window, WHITE);
	//draw_line(ui.start_x, 285, ui.end_x, 285, GREEN);

	ui.start_x_line = ui.start_x_window + 1;
	ui.start_y_line = 300;
	ui.next_step_x_line = ui.start_x_line;

	draw_vertical_punct(94 + 5, ui.start_y_window, ui.end_y_window, 3, YELLOW);
	draw_vertical_punct(187, ui.start_y_window, ui.end_y_window, 3, YELLOW);
	draw_vertical_punct(280, ui.start_y_window, ui.end_y_window, 3, YELLOW);
	draw_vertical_punct(374, ui.start_y_window, ui.end_y_window, 3, YELLOW);

	draw_number(40, 20, FONTID_6X8M, fft.maxindex + 1, RED, BLACK, 0);
	draw_number(120, 20, FONTID_6X8M, fft.maxvalue, RED, BLACK, 0);

	for (int i = ui.left_edge_bandwidth; i < ui.bandwidth_display; i++) {
		ui.next_step_x_line += 1;

		ui.next_step_x_line > ui.end_x_window ? (ui.next_step_x_line = ui.end_x_window - 1) : (ui.next_step_x_line = ui.next_step_x_line);

		ui.next_step_y_line = 300 - fft_Sbuff[i] * 3;

		ui.next_step_y_line < (ui.start_y_window + 2) ? (ui.next_step_y_line = (ui.start_y_window + 2)) : (ui.next_step_y_line = ui.next_step_y_line);

		draw_line(ui.start_x_line, ui.start_y_line, ui.next_step_x_line, ui.next_step_y_line, ui.color_line);

		ui.start_y_line = ui.next_step_y_line;
		ui.start_x_line = ui.next_step_x_line;

	}
	ui.start_x_line = 0;
	ui.start_y_line = 0;
	ui.next_step_x_line = 0;
	ui.next_step_y_line = 0;

	//HAL_Delay(300);
}

void change_bandwidth_display(uint16_t pix_shift) {
	ui.left_edge_bandwidth = pix_shift;
	ui.right_edge_bandwidth = ui.end_x_window - 1;
	ui.bandwidth_display = ui.left_edge_bandwidth + ui.right_edge_bandwidth;
}


/*
 * #include "gui.h"

void draw_window(void) {
	fft_force();
	clear_screen();

	ui.start_x_window = 5;
	ui.start_y_window = 40;
	ui.end_x_window = TFTWIDTH - ui.start_x_window;
	ui.end_y_window = TFTHEIGHT - 5;

	ui.color_line = RED;

	change_bandwidth_display(0);

	draw_rectangle(ui.start_x_window, ui.start_y_window, ui.end_x_window, ui.end_y_window, WHITE);
	//draw_line(ui.start_x, 285, ui.end_x, 285, GREEN);

	ui.start_x_line = ui.start_x_window + 1;
	ui.start_y_line = 300;
	ui.next_step_x_line = ui.start_x_line;

	draw_vertical_punct(94 + 5, ui.start_y_window, ui.end_y_window, 3, YELLOW);
	draw_vertical_punct(187, ui.start_y_window, ui.end_y_window, 3, YELLOW);
	draw_vertical_punct(280, ui.start_y_window, ui.end_y_window, 3, YELLOW);
	draw_vertical_punct(374, ui.start_y_window, ui.end_y_window, 3, YELLOW);

	draw_number(40, 20, FONTID_6X8M, fft.maxindex + 1, RED, BLACK, 0);
	draw_number(120, 20, FONTID_6X8M, fft.maxvalue, RED, BLACK, 0);

	for (int i = ui.left_edge_bandwidth; i < ui.bandwidth_display; i++) {
		ui.next_step_x_line += 1;

		ui.next_step_x_line > ui.end_x_window ? (ui.next_step_x_line = ui.end_x_window - 1) : (ui.next_step_x_line = ui.next_step_x_line);

		ui.next_step_y_line = 300 - fft.output_real_data_magnitude[i] * 4;

		ui.next_step_y_line < (ui.start_y_window + 2) ? (ui.next_step_y_line = (ui.start_y_window + 2)) : (ui.next_step_y_line = ui.next_step_y_line);

		draw_line(ui.start_x_line, ui.start_y_line, ui.next_step_x_line, ui.next_step_y_line, ui.color_line);

		ui.start_y_line = ui.next_step_y_line;
		ui.start_x_line = ui.next_step_x_line;

	}
	ui.start_x_line = 0;
	ui.start_y_line = 0;
	ui.next_step_x_line = 0;
	ui.next_step_y_line = 0;

	//HAL_Delay(300);
}

void change_bandwidth_display(uint16_t pix_shift) {
	ui.left_edge_bandwidth = pix_shift;
	ui.right_edge_bandwidth = ui.end_x_window - 1;
	ui.bandwidth_display = ui.left_edge_bandwidth + ui.right_edge_bandwidth;
}
 *
 */
