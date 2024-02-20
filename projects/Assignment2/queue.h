#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>

#include "led_matrix.h"

#define QUEUE_SIZE 10

uint8_t queue_get_length(void);
uint8_t queue_get_new_position(uint8_t pointer);

char queue[QUEUE_SIZE];
uint8_t start_pointer = 0;
uint8_t end_pointer = 0;

void queue_init(void)
{
	// setup led pins
	led_matrix_init();
}

bool queue_push(char character)
{
	// if queue is full
	// return false
	
	// push char to queue
	// update led pins
	// return true
	queue[start_pointer] = character;
	
	start_pointer = queue_get_new_position(start_pointer);
	set_matrix(start_pointer, end_pointer);
	
	return true;
}

char queue_pop(void)
{
	char character;
	
	if (queue_get_length() <= 0)
	{	return '\0';	}
	// pop char from queue
	// update led pins
	// return char
	character = queue[end_pointer];
	
	end_pointer = queue_get_new_position(end_pointer);
	set_matrix(start_pointer, end_pointer);
	
	return character;
}

uint8_t queue_get_length(void)
{
	uint8_t count = 0;
	for (uint8_t counter = start_pointer; counter != end_pointer; counter++)
	{
		count = count + 1;
		counter = queue_get_new_position(counter);
	}
	return count;
}

uint8_t queue_get_new_position(uint8_t pointer)
{
	return pointer >= QUEUE_SIZE - 1 ? 0 : pointer + 1;
}

#endif