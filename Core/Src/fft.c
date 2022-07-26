#include "fft.h"
#include "string.h"

//#include "arm_fft_bin_data.h"

void init_fft(elightSamplesTypeDef samples) {
	uint32_t SampleRate = 10000000;
	fft.FFT_SampleRate = SampleRate;
	Sample_num = samples;
	arm_rfft_fast_init_f32(&S, samples);
}

void fft_force(void) {

	//memset(fft.data_adc, 0, FFT_SampleNum);
	//memset(fft.input_fft_adc_data_float, 0, FFT_SampleNum);
	//memset(fft.complex, 0, FFT_SampleNum);
	//memset(fft.output_real_data_magnitude, 0, FFT_SampleNum);




	//HAL_ADC_Start(&hadc1);

	//for (uint16_t i = 0; i < FFT_SampleNum ; i++) {
	//	fft.data_adc[i] = ADC1->DR;
	//}

	for (uint16_t k = 0; k < FFT_SampleNum ; k++) {
		fft.input_fft_adc_data_float[k] = (float32_t)(fft.data_adc[k] * REF_VOLTAGE / 4096);//(float32_t) ((fft.data_adc[k] * REF_VOLTAGE / 4096) - REF_VOLTAGE / 2);

		//fft.input_fft_adc_data_float[k] = (float32_t)(ADC1->DR * REF_VOLTAGE / 4096);//(float32_t) ((fft.data_adc[k] * REF_VOLTAGE / 4096) - REF_VOLTAGE / 2);

	}

	fft_();

	//постоянная составляющая
	//fft.output_real_data_magnitude[0] = 0;
	//fft.output_real_data_magnitude[1] = 0;
	//fft.output_real_data_magnitude[2] = 0;

}

void fft_(void) {


	const float tmp = 2.0f * M_PI / (float) FFT_SampleNum;



	arm_mult_f32(fft.input_fft_adc_data_float, fft.FFT_window, fft.input_fft_adc_data_float, FFT_SampleNum);


/*
void arm_rfft_fast_f32		(const arm_rfft_fast_instance_f32 * 	S,
							float32_t * 	p,
							float32_t * 	pOut,
							uint8_t 	ifftFlag )
[in]	S	points to an arm_rfft_fast_instance_f32 structure
[in]	p	points to input buffer (Source buffer is modified by this function.)
[in]	pOut	points to output buffer
[in]	ifftFlag
value = 0: RFFT
value = 1: RIFFT
 */
	arm_rfft_fast_f32(&S, fft.input_fft_adc_data_float, fft.complex, 0);






	arm_cmplx_mag_f32(fft.complex, fft.output_real_data_magnitude, FFT_SampleNum / 2);

	arm_max_f32(&fft.output_real_data_magnitude, (FFT_SampleNum / 2), &fft.maxvalue, &fft.maxindex);

	for (uint32_t i = 0; i < FFT_SampleNum ; i++) {
		*(fft.FFT_window + i) = 0.5f - 0.5f * arm_cos_f32((float) i * tmp);
	}

	for (uint32_t i = 0; i < FFT_SampleNum / 2; i++) {
		*(fft.FFT_frq + i) = (float) i * (float) fft.FFT_SampleRate / (float) FFT_SampleNum;
	}

}

