#ifndef TIM_IT_H
#define TIM_IT_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define IT_PERIOD (50)
#define IT_PRESCALER (SystemCoreClock / (8000 * IT_PERIOD)) /* X = SystemCoreClock / (8000Hz  * Period) */

void interrupt_init(void);

#endif
