#pragma once
#define RNG_H

#include "stm32f7xx.h"



void rng_init (void) ;
uint32_t rng_gen (void);
