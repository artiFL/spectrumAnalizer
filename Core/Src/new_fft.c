/*
 * new_fft.c
 *
 *  Created on: Jun 19, 2022
 *      Author: artemflegler
 */

#include "new_fft.h"
#include "arm_fft_bin_data.h"

//Создаём два буфера, в одном будем хранить выборки АЦП, во втором результаты БФП
float fft_Sbuff[FFT_SIZE] = { 0 };
float fft_Dbuff[FFT_SIZE * 2] = { 0 };

void FFT_Initialization()
{
	//status = arm_rfft_init_q31(&ST, FFT_SIZE, 0, 1); //функция инициализации необходима для БФП
	status = arm_rfft_fast_init_f32(&ST, FFT_SIZE);

}

void FFT_Process()
{

	HAL_ADC_Start(&hadc1);
	for (uint16_t i = 0; i < FFT_SIZE ; i++) {
		fft_Sbuff[i] = (float32_t)(ADC1->DR * REF_VOLTAGE / 4096);//(float32_t) ((fft.data_adc[k] * REF_VOLTAGE / 4096) - REF_VOLTAGE / 2);
	}

	//status = arm_rfft_init_q31(&ST, FFT_SIZE, 0, 1); //функция инициализации необходима для БФП


	status = arm_rfft_fast_init_f32(&ST, FFT_SIZE);


	if (status == ARM_MATH_SUCCESS) {



		arm_rfft_fast_f32(&ST, fft_Sbuff, fft_Dbuff, 0);






		arm_cmplx_mag_f32(fft_Dbuff, fft_Sbuff, FFT_SIZE);



		//arm_rfft_q31(&ST, fft_Sbuff, fft_Dbuff); //выполнение БФП
		//arm_cmplx_mag_q31(fft_Dbuff, fft_Sbuff, FFT_SIZE); //вычисляем амплитуды гармоник
	}

}
