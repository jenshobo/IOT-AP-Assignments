#ifndef TIM_IT_H
#define TIM_IT_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define IT_PERIOD (50)
#define IT_PRESCALER (SystemCoreClock / (8000 * IT_PERIOD)) /* X = SystemCoreClock / (8000Hz  * Period) */
#define IT_SYSTICK (SystemCoreClock / 10)										/* X = SystemCoreClock / 10Hz */

#define IT_PRESCALER_TOP (IT_PRESCALER * 2)	/* 200% speed */
#define IT_PRESCALER_BOT (IT_PRESCALER / 2)	/* 50%  speed */

#define REMAP(a) (IT_PRESCALER_BOT + (a) * (IT_PRESCALER_TOP - IT_PRESCALER_BOT) / (65535))	/* Remap value from uint16_t to prescaler */

void interrupt_init(void);
void map_prescaler(uint16_t value);

#endif
