#include "led_matrix.h"

void led_matrix_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= 0x00155554;
}

void set_matrix(uint8_t start_pointer, uint8_t end_pointer)
{
	// while (start_pointer and end_pointer are not the same)
	// enable LED bit on start_pointer position
	// get next position for start_pointer
	uint16_t matrix = 0;
	while (start_pointer != end_pointer)
	{
		matrix |= power_of(2, end_pointer);
		end_pointer = led_get_new_position(end_pointer);
	}
	
	GPIOC->ODR = matrix<<1;
}

uint8_t led_get_new_position(uint8_t pointer)
{
	return pointer >= LED_SIZE - 1 ? 0 : pointer + 1;
}

uint16_t power_of(uint8_t base, uint8_t exponent)
{
	uint16_t start = 1;
	while (exponent > 0)
	{
		start = start * base;
		exponent = exponent - 1;
	}
	return start;
}