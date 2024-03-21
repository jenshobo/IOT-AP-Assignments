#ifndef TIM_IT_H
#define TIM_IT_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define IT_PERIOD (50)
#define IT_PRESCALER (SystemCoreClock / (8000 * IT_PERIOD)) /* X = SystemCoreClock / (8000Hz  * Period) */ // 120

#define IT_PRESCALER_TOP (IT_PRESCALER * 2) // 240
#define IT_PRESCALER_BOT (IT_PRESCALER / 2)	// 60

#define REMAP(a) (IT_PRESCALER_BOT + (a) * (IT_PRESCALER_TOP - IT_PRESCALER_BOT) / (65535))

void interrupt_init(void);
void map_prescaler(uint16_t value);

#endif
