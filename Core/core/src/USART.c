#include "USART.h"

void USART_Init(uint32_t baudrate, uint8_t numberUSART) {
/*`USART2 init
 * 8 bit data
 * 1 stop bit
 * non parity control
 * none flow control
 * PA2 TX
 * PA3 RX
 */
	RCC->DCKCFGR2   |= RCC_DCKCFGR2_USART2SEL_1;		// clock surce 16MHz HSI
	uint32_t U_BRR = (16000000 + baudrate / 2) / baudrate;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	//PA2, PA3
	GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
	GPIOA->AFR[0] |= (0x07 << (4 * 2));
	GPIOA->AFR[0] |= (0x07 << (4 * 3));

	USART_T->BRR = U_BRR;  //351,5625		703,125		1 406,25
	USART_T->CR1 |= USART_CR1_TE;
	USART_T->CR1 |= USART_CR1_RE;
	USART_T->CR1 |= USART_CR1_RXNEIE;

	USART_T->CR1 |= USART_CR1_UE;

	USART_Conf.Boudrate_USART = baudrate;
	NVIC_EnableIRQ(USART2_IRQn);
	USART_Conf.USARTEnable_flag = 1;
}

void SendByte (uint8_t data) {
    while(!(USART_T->ISR & USART_ISR_TC));
    	USART_T->TDR = data;
}

void print_str (const char *args, ...)
{
	uint8_t count = 0;
	char StrBuff[256];
	va_list ap;
	va_start(ap, args);
	vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
	while (StrBuff[count]) {
		SendByte(StrBuff[count++]);
	}
}

void USART2_IRQHandler(void) {
	if ((USART_T->RDR) != 0) {
		get_array_str(RessivBuffer);
	}
	NVIC_ClearPendingIRQ(USART2_IRQn);

}

void get_byte(volatile char* array) {

    array[address++] = USART_T->RDR;

    USART_T->RQR |= USART_RQR_RXFRQ;

    USART_Flag.ressiveByte = 1;
}
void get_array_str (volatile char* array) {

	char tmpChar = 0;
	uint16_t q = 0;

	do {

		if ((USART_T->ISR & USART_ISR_RXNE) != 0) {

			tmpChar = USART_T -> RDR;
			array[q++] = tmpChar;

			USART_T -> RQR |= USART_RQR_RXFRQ;
			USART_T -> ICR |= USART_ICR_ORECF;

		}
	}

	while (tmpChar != _CR);

	array[--q] = 0;
	USART_Flag.ressiveString = 1;
	print_str(array);

}

