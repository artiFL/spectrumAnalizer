#include "main.h"
#include "usb_device.h"
#include "gui.h"
#include <stdio.h>
#include <errno.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <loging.h>
#include "cli.h"
#include "string.h"
#include "display.h"
#include "rng.h"
#include "fft.h"
#include "new_fft.h"

extern char TxBufferFS[40];
extern char RxBufferFS[40];
extern sfftTypeDef fft;

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

PUTCHAR_PROTOTYPE {
	CDC_Transmit_FS((uint8_t*) ch, 1);

	return ch;
}

#endif

int _write(int file, char *data, int len) {
	if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
		errno = EBADF;
		return -1;
	}

	// arbitrary timeout 1000
	CDC_Transmit_FS((uint8_t*) data, len);

	// return # of bytes written - as best we can tell
	return len;
}

#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar (void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE * f)
#endif

DMA_HandleTypeDef hdma_adc1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);

void MX_DMA_Init(void);

void DMA_init(void);
void DMA_(void);

#define DMAStart 	DMA2_Stream1->CR |= DMA_SxCR_EN
#define DMAStop 	DMA2_Stream1->CR &= ~DMA_SxCR_EN

uint16_t data_adc_get[4096];



void MPU_RegionConfig(void) {
	MPU_Region_InitTypeDef MPU_InitStruct;
	/* Disable MPU */
	HAL_MPU_Disable();
	/* Configure FMC region as REGION N°2, 0.5GB of size, R/W region */

	MPU_InitStruct.Enable = MPU_REGION_ENABLE;

	MPU_InitStruct.BaseAddress = 0xC0000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_512MB;

	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;

	MPU_InitStruct.Number = MPU_REGION_NUMBER2;

	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	/* Enable MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

DMA2D_HandleTypeDef hdma2d;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

uint8_t new_sample;

uint8_t test_src[255];
uint8_t test_dst[255];

int main(void) {

	SCB_EnableICache();
	SCB_EnableDCache();
	HAL_Init();

	//MPU_RegionConfig();

	SystemClock_Config();
	MX_GPIO_Init();

	MX_DMA_Init();

	MX_ADC1_Init();


	HAL_ADC_Start_DMA(&hadc1, (unsigned long int *) buff_ADC_DATA, FFT_SIZE);



	//MX_USB_DEVICE_Init();
	//MX_DMA2D_Init();
	rng_init();

	display_init(1);
	lcd_console_log();
	HAL_Delay(1000);
	clear_screen();

	init_fft(FFT_SampleNum);
	FFT_Initialization();
	// RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;

	//memset(ScreenBuff, RED, TFTWIDTH * TFTHEIGHT);

	while (1) {
		//HAL_DMA2D_Start_IT(&hdma2d,(uint32_t)&ScreenBuff,  /* Source memory buffer      */(uint32_t)LCD->RAM, /* Destination memory buffer */480,             /* Width of the 2D memory transfer in pixels */320);             /* Height of the 2D memory transfer in lines */
		draw_window();
	}
}
/*
void DMA2_Steram0_IRQHandler(void) {
	uint32_t temp_SR = DMA2->LISR;
	if (temp_SR & DMA_LISR_TCIF0) {
		DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
		new_sample = 1;
	}
}
*/
void MX_DMA2D_Init(void) {
	hdma2d.Instance = DMA2D;
	hdma2d.Init.Mode = DMA2D_M2M;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
	hdma2d.Init.OutputOffset = 0;
	hdma2d.LayerCfg[1].InputOffset = 0;
	hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[1].InputAlpha = 0;
	hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
	hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
	if (HAL_DMA2D_Init(&hdma2d) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN DMA2D_Init 2 */

	/* USER CODE END DMA2D_Init 2 */

}
void DMA_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	DMA2_Stream1->CR |= DMA_SxCR_CHSEL_2;		//Chanel 4
	DMAStop;		//DMA Disable
	DMA2_Stream1->CR &= ~DMA_SxCR_MINC;		//Addr increment reset
	//DMA2_Stream1 -> CR |= DMA_SxCR_PINC;		//Peripheral incremental mode disable
	DMA2_Stream1->CR |= DMA_SxCR_MSIZE_0;		//Memory size		16b
	DMA2_Stream1->CR |= DMA_SxCR_PSIZE_0;		//peripheral size	16b
	DMA2_Stream1->CR &= ~DMA_SxCR_CIRC;		//Circle off
	DMA2_Stream1->CR &= ~DMA_SxCR_DIR;		//Memory to peripheral
	DMA2_Stream1->CR |= DMA_SxCR_PL;			//Very High priority
	DMA2_Stream1->CR |= DMA_SxCR_TCIE;		//Transfer complete interrupt enable
	DMA2_Stream1->PAR = (uint32_t) &ADC1->DR;		//(u32)&(*(__IO uint8_t*)&(SPI4->DR));//

}

void DMA_(void) {
	DMAStop;
	DMA2_Stream1->PAR = (uint32_t) &ADC1->DR;
	//DMA2_Stream1->M0AR = (uint32_t)&input_fft_adc_data_float;
	//DMA2_Stream1->NDTR = TEST_LENGTH_SAMPLES;
	DMAStart;

}


void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 10;
	RCC_OscInitStruct.PLL.PLLN = 216;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
	PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void) {

	/* USER CODE BEGIN ADC1_Init 0 */
	  //NVIC_SetPriority(ADC_IRQn, 0); /* ADC IRQ greater priority than DMA IRQ */
	  //NVIC_EnableIRQ(ADC_IRQn);
	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */

}

/**
 * Enable DMA controller clock
 */

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void adc1_init(void) {

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR1 |= ADC_CR1_SCAN;                // Scan mode
	ADC1->SQR3 = 9;                            //выбор канала PA9
	ADC1->CR2 |= ADC_CR2_DDS;                //DMA disable selection (for single ADC mode)
	ADC1->CR2 &= ~ADC_CR2_CONT;            //Continuous conversion
	ADC1->CR2 |= ADC_CR2_EXTEN_0;            //01: Trigger detection on the rising edge
	ADC1->CR2 |= ADC_CR2_ADON;                //Вкл. переобразования
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
