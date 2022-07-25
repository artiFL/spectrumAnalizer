#include "loging.h"

void FatalError(eTypeError TypeError) {
	switch (TypeError){
	case UnknownError:
		console_printf(MsgError, "UnknownError %d", TypeError);
		break;
	case LowVoltageBat:
		console_printf(MsgError, "LowVoltageBat %d", TypeError);
		break;
	case HoghVoltageBat:
		console_printf(MsgError, "HoghVoltageBat %d", TypeError);
		break;
	case WaitingError:
		console_printf(MsgError, "WaitingError %d", TypeError);
		break;
	case Overrun:
		console_printf(MsgError, "Overrun %d", TypeError);
		break;
	}

	delay(1000);

	SCB->AIRCR |= 1 << SCB_AIRCR_SYSRESETREQ_Pos; //reboot soft "not working correctly"0x05FA0004
}

void lcd_console_log (void) {
	volatile uint16_t *Flashsize = (uint16_t *)FLASHSIZE_BASE;
	volatile uint32_t *UniqueID = (uint32_t *)UID_BASE;

	fill_screen(color.CLI_bacgroundeColor);

	//console_printf(MsgInfo,"<%d> InitializationTick" , DWT->CYCCNT);
	console_printf(MsgInfo,"STM32F767ZIT6 UID - %d:%d:%d", UniqueID[0], UniqueID[1], UniqueID[2]);
	console_printf(MsgWarning,"__CORTEX_M%d __CM7_CMSIS_VERSION - %d",  __CORTEX_M, __CM7_CMSIS_VERSION);
	console_printf(MsgWarning,"Flash Size - %d Kbytes ", Flashsize[0]);
	console_printf(MsgInfo,"Version Firmware  - 2.16 	10/3/2021");

	(SCB->CCR && (uint32_t)SCB_CCR_IC_Msk) != 0 ? (console_printf(MsgInfo,"SCB_I_Cache - Enable")) : (0);
	(SCB->CCR && (uint32_t)SCB_CCR_DC_Msk) != 0 ? (console_printf(MsgInfo,"SCB_D_Cache - Enable")) : (0);
	(MPU->RASR && (uint32_t)MPU_RASR_ENABLE_Msk) != 0 ? (console_printf(MsgInfo,"Memory protect unit is Enable  -0x%08x",(MPU->RBAR))) : (0);
	(PWR->CR1 && PWR_CR1_ODEN) != 0 ? (console_printf(MsgInfo,"PRW OVERRUN is Enable")) : (0);
	(WWDG->CR && (uint32_t)WWDG_CR_WDGA_Msk) != 0 ? (console_printf(MsgInfo,"WWDG Enable")) : (0);
	(FLASH->ACR && (uint32_t)FLASH_ACR_ARTEN_Msk) != 0 ? (console_printf(MsgInfo,"ART Flash Enable")) : (0);


#ifdef FLASH_H
#endif
	(RNG->CR && (uint32_t)RNG_CR_RNGEN) != 0 ? (console_printf(MsgInfo,"RNG is Enable")) : (0);


#ifdef CLOCK_H
	Clock_Conf.Core > 216000000 ? (console_printf(MsgError,"Core Boost	-%dMHz\n", Clock_Conf.Core / 1000000)) : \
								  (console_printf(MsgInfo,"Core	- %dMHz\n", Clock_Conf.Core / 1000000));
	console_printf(MsgInfo," -- APB1_Perip - %dMHz\n", Clock_Conf.APB1Perip / 1000000);
	console_printf(MsgInfo," -- APB1_Timer - %dMHz\n", Clock_Conf.APB1Timer / 1000000);
	console_printf(MsgInfo," -- APB2_Perip - %dMHz\n", Clock_Conf.APB2Perip / 1000000);
	console_printf(MsgInfo," -- APB2_Timer - %dMHz", Clock_Conf.APB2Timer / 1000000);
#endif


//----------------------------------------------DMA------------------------------------------------------------------------------
/*	(RCC->AHB1ENR && (uint32_t)RCC_AHB1ENR_DMA2DEN_Msk) == 1 ? (console_printf(MsgInfo,"DMA2D - Enable")) : (0);
	(RCC->AHB1ENR && (uint32_t)RCC_AHB1ENR_DMA2EN_Msk) == 1 ? (console_printf(MsgInfo,"DMA2 - Enable ")) : (0);
	(RCC->AHB1ENR && (uint32_t)RCC_AHB1ENR_DMA1EN_Msk) == 1 ? (console_printf(MsgInfo,"DMA1 - Enable ")) : (0);
*///-----------------------------------------------------------------------------------------------------------------------------
	//(FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1] && (uint32_t)FMC_BCR1_MBKEN_Msk) != 0 ? (console_printf(MsgInfo,"FMC Bank1 NORSRAM1 - Enable")) : (0);
//-------------------------------------------------------------------------------------------------------------------------------
	(QUADSPI->CR && (uint32_t)QUADSPI_CR_EN_Msk) != 0 ? (console_printf(MsgInfo,"QUADSPI - Enable")) : (0);
//-------------------------------------------------------------------------------------------------------------------------------
	(ADC1->CR2 && (uint32_t)ADC_CR2_ADON_Msk) != 0 ? (console_printf(MsgInfo,"ADC1 - Enable")) : (0);
	(ADC2->CR2 && (uint32_t)ADC_CR2_ADON_Msk) != 0 ? (console_printf(MsgInfo,"ADC2 - Enable")) : (0);
//-------------------------------------------------------------------------------------------------------------------------------
	(DCMI->CR && (uint32_t)DCMI_CR_ENABLE_Msk) != 0 ? (console_printf(MsgInfo,"DCMI - Enable")) : (0);
//-------------------------------------------------------------------------------------------------------------------------------
	(USART1->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"USART1 - Enable - Baudrate-%d", ((16000000 / ((USART1->BRR) * 2))) * 2)) : (0);
	(USART2->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"USART2 - Enable - Baudrate-%d", ((16000000 / ((USART2->BRR) * 2))) * 2)) : (0);
	(USART3->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"USART3 - Enable - Baudrate-%d", ((16000000 / ((USART3->BRR) * 2))) * 2)) : (0);
	(UART4->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"UART4 - Enable - Baudrate-%d", ((16000000 / ((UART4->BRR) * 2))) * 2)) : (0);
	(UART5->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"UART5  - enable - Baudrate-%d", ((16000000 / ((UART5->BRR) * 2))) * 2)) : (0);
	(USART6->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"USART6 - Enable - Baudrate-%d", ((16000000 / ((USART6->BRR) * 2))) * 2)) : (0);
	(UART7->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"UART7 - Enable - Baudrate-%d", ((16000000 / ((UART7->BRR) * 2))) * 2)) : (0);
	(UART8->CR1 && (uint32_t)USART_CR1_UE_Msk) != 0 ? (console_printf(MsgInfo,"UART8 - Enable - Baudrate-%d", ((16000000 / ((UART8->BRR) * 2))) * 2)) : (0);
//------------------------------------------------------------------------------------------------------------------------------

}













