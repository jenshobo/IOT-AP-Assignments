#ifndef QUEUE_H
#define QUEUE_H

#include "stm32f0xx.h"
#include <stdint.h>
#include <stdbool.h>

void queue_init(void)
{
	// make static queue array
	// setup led pins
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= 0x00155554;
}

bool queue_push(char character)
{
	static uint16_t var = 0;
	var = var + 1;
	GPIOC->ODR = var;
	// if queue is full
	// return false
	
	// push char to queue
	// update led pins
	// return true
	return true;
}

char queue_pop(void)
{
	// pop char from queue
	// update led pins
	// return char
	return 'c';
}

uint8_t queue_get_length(void)
{
	// return length
	return 1;
}


#endif