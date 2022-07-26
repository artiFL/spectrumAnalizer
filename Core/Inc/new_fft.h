/*
 * new_fft.h
 *
 *  Created on: Jun 19, 2022
 *      Author: artemflegler
 */

#ifndef INC_NEW_FFT_H_
#define INC_NEW_FFT_H_

#include "stm32f7xx.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "stm32f7xx_hal.h"


ADC_HandleTypeDef hadc1;


#define FFT_SIZE 4096//указываем размер FFT

#define  REF_VOLTAGE			(float)3.3


uint16_t buff_ADC_DATA[FFT_SIZE];


uint16_t k;
uint8_t status;
arm_rfft_fast_instance_f32 ST;

void FFT_Process();
void FFT_Initialization();


#endif /* INC_NEW_FFT_H_ */
