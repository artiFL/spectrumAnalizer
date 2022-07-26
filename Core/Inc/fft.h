#pragma once
#include "arm_math.h"
#include "arm_const_structs.h"
#include "display.h"
#include "string.h"
#include "stm32f7xx_hal.h"



ADC_HandleTypeDef hadc1;

typedef enum
{
	_512 = 512,
	_1024 = 1024,
	_2048 = 2048,
	_4096 = 4096,
	_8192 = 8192

}elightSamplesTypeDef;


#define  FFT_SampleNum  		(int)1
#define  REF_VOLTAGE			(float)3.3




uint16_t Sample_num;

typedef struct
{
	uint16_t data_adc[FFT_SampleNum];
	float32_t input_fft_adc_data_float[FFT_SampleNum];
	float32_t complex[FFT_SampleNum];
	float32_t output_real_data_magnitude[FFT_SampleNum];
	float32_t maxvalue;
	uint32_t maxindex;
	float FFT_window[FFT_SampleNum];
	float FFT_frq[FFT_SampleNum / 2];
	float FFT_dB[FFT_SampleNum / 2];
	float FFT_SampleRate;

}sfftTypeDef;
sfftTypeDef fft;



arm_rfft_fast_instance_f32 S;



void fft_(void);
void fft_force(void);
void init_fft(elightSamplesTypeDef samples);
void ff_(void);





