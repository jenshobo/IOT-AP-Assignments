#ifndef PWM_H
#define PWM_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define PERIOD 							(255)
#define PRESCALER 					(SystemCoreClock / (60000 * PERIOD)) 					/* X = SystemCoreClock / (60000Hz * Period) */
#define START_PERCENTAGE		(PERIOD / 2)																	/* Start with 50% duty cycle */

#define INTERRUPT_PERIOD		(10)
#define INTERRUPT_PRESCALER (SystemCoreClock / (8000 * INTERRUPT_PERIOD)) /* X = SystemCoreClock / (8000Hz  * Period) */

void pwm_init(void);	/* public methode(s) */

#endif
