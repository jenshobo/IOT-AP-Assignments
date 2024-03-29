#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#include "../led_matrix/led_matrix.h"

#define QUEUE_SIZE 10

void queue_init(void);
void queue_push(char character);
char queue_pop(void);
uint8_t queue_get_length(void);
uint8_t queue_get_new_position(uint8_t pointer);

#endif