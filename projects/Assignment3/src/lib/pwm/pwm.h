#ifndef PWM_H
#define PWM_H

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define PERIOD 100
#define LED_PRESCALER  (SystemCoreClock / 200 * PERIOD) /* X = SystemCoreClock / (200Hz * Period) */
#define MASK_PRESCALER (SystemCoreClock / 20  * PERIOD) /* X = SystemCoreClock / (20Hz  * Period) */
#define START_PERCENTAGE 70

void pwm_init(void);	/* public methode(s) */

#endif
