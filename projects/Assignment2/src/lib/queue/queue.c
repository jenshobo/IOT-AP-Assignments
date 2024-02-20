#include "queue.h"

char queue[QUEUE_SIZE];
uint8_t start_pointer = 0;
uint8_t end_pointer = 0;

void queue_init(void)
{
	led_matrix_init();
}

void queue_push(char character)
{
	if (queue_get_new_position(start_pointer) == end_pointer)
	{
		flash_led();
		return;
	}
	
	queue[start_pointer] = character;
	
	start_pointer = queue_get_new_position(start_pointer);
	set_matrix(start_pointer, end_pointer);
}

char queue_pop(void)
{
	char character;
	
	if (queue_get_length() <= 0)
	{	return '\0';	}
	character = queue[end_pointer];
	
	end_pointer = queue_get_new_position(end_pointer);
	set_matrix(start_pointer, end_pointer);
	
	return character;
}

uint8_t queue_get_length(void)
{
	int16_t count = end_pointer - start_pointer;
	if (count < 0)
	{	count = count + QUEUE_SIZE - 1;	}
	return count;
}

uint8_t queue_get_new_position(uint8_t pointer)
{
	return pointer >= QUEUE_SIZE - 1 ? 0 : pointer + 1;
}