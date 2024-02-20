#include "delay.h"

void delay(const uint32_t delay_time)
{
	uint32_t timer = delay_time;
	for (; timer > 0; timer--) { ; }
}