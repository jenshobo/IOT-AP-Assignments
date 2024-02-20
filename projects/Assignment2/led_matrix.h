#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "stm32f0xx.h"

#define LED_SIZE 10

void led_matrix_init(void);
void set_matrix(uint8_t start_pointer, uint8_t end_pointer);
uint8_t led_get_new_position(uint8_t pointer);
uint16_t power_of(uint8_t base, uint8_t exponent);

#endif