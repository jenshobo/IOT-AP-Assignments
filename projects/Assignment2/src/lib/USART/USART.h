#ifndef __USART_H
#define __USART_H

#include "stm32f0xx.h"

void USART_init(void);
void USART_putchar(char character);
void USART_putstring(char *string);
void USART_clearscreen();

#endif