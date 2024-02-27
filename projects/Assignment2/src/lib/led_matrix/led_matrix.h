#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "stm32f0xx.h"
#include "../queue/queue.h"
#include "../delay/delay.h"

#define LED_SIZE 10
#define LED_MATRIX 0x00155554
#define FLASH_DELAY 10
#define FLASH_SPEED 10
#define MATRIX_OFFSET <<1

void led_matrix_init(void);
void set_matrix(uint8_t start_pointer, uint8_t end_pointer);
uint16_t power_of(uint8_t base, uint8_t exponent);
void flash_led();

#endif