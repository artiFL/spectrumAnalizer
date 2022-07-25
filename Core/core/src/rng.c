#include "rng.h"


void rng_init (void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
	RNG->CR |= RNG_CR_RNGEN;
}

uint32_t rng_gen (void)
{
	return RNG->DR;
}
