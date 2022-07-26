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

	//HAL_ADC_Start(&hadc1);
	for (uint16_t i = 0; i < FFT_SIZE ; i++) {
		fft_Sbuff[i] = (float32_t)(buff_ADC_DATA[i] * REF_VOLTAGE / 4096 - 1.65);//(float32_t) ((fft.data_adc[k] * REF_VOLTAGE / 4096) - REF_VOLTAGE / 2);


	}

	//status = arm_rfft_init_q31(&ST, FFT_SIZE, 0, 1); //функция инициализации необходима для БФП


	status = arm_rfft_fast_init_f32(&ST, FFT_SIZE);


	if (status == ARM_MATH_SUCCESS) {



		arm_rfft_fast_f32(&ST, fft_Sbuff, fft_Dbuff, 0);




		//const float tmp = 2.0f * M_PI / ((float) FFT_SIZE - 1.0);


		arm_cmplx_mag_f32(fft_Dbuff, fft_Sbuff, FFT_SIZE);

		//for (uint32_t i = 0; i < FFT_SIZE ; i++) {
		//	fft_Sbuff[i] *= (0.54 - 0.46 * cosf(tmp * i));//Хамминга
			//*(fft_Sbuff + i) = 0.5f - 0.5f * arm_cos_f32((float) i * tmp);
		//}





		//arm_rfft_q31(&ST, fft_Sbuff, fft_Dbuff); //выполнение БФП
		//arm_cmplx_mag_q31(fft_Dbuff, fft_Sbuff, FFT_SIZE); //вычисляем амплитуды гармоник
	}

}
/*
dTmpFloat = 2.0 * M_PI / (iCoefNum - 1.0);
for (iCnt = 0; iCnt < iCoefNum; iCnt++)
{
   switch (Wind)
      {
    case 0: fCoeff[iCnt] *= 1.0;
    break;
    case 1: fCoeff[iCnt] *= sinf(dTmpFloat * iCnt);//sin window
    break;
    case 2: fCoeff[iCnt] *= (0.42 - 0.5 * cosf(dTmpFloat * iCnt) + 0.08 * cosf(2.0 * dTmpFloat * iCnt));//Блекмана
    break;
    case 3: fCoeff[iCnt] *= (0.54 - 0.46 * cosf(dTmpFloat * iCnt));//Хамминга
    break;
    case 4: fCoeff[iCnt] *= (0.5 - 0.5*cosf(dTmpFloat * iCnt));//Хеннинга
    break;
    case 5: fCoeff[iCnt] *= (0.35875 - 0.48829*cosf(dTmpFloat * iCnt) + 0.14128*cosf(2.0 * dTmpFloat * iCnt) - 0.01168*cosf(3.0 * dTmpFloat * iCnt));//Блэкмана-Харриса
    break;
    case 6: fCoeff[iCnt] *= (0.355768 - 0.487396*cosf(dTmpFloat * iCnt) + 0.144232*cosf(2.0 * dTmpFloat * iCnt) - 0.012604*cosf(3.0 * dTmpFloat * iCnt));//Наталла
    break;
    case 7: fCoeff[iCnt] *= (0.3635819 - 0.4891775*cosf(dTmpFloat * iCnt) + 0.1365995*cosf(2.0 * dTmpFloat * iCnt) - 0.0106411*cosf(3.0 * dTmpFloat * iCnt));//Блэкмана-Наталла
    break;
      }
}
*/
