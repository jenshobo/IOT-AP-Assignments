#ifndef DELAY_H
#define DELAY_H

#define ONE_SECOND SystemCoreClock/8

#include <stdint.h>

void delay(const uint32_t delay_time);

#endif