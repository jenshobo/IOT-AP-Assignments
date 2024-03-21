#ifndef STATE_H
#define STATE_H

#include "stm32f0xx.h"
#include "stdbool.h"

#include "./../pwm/pwm.h"
#include "./../dac/dac.h"

void state_init(void);
void switch_state(void);
void delay(const uint32_t);

#endif
