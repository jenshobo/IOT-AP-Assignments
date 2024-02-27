#ifndef __USART_H
#define __USART_H

#include "stm32f0xx.h"

#define AFR_SET 0x00000110
#define BOUD_RATE 0x01A1

#define CLEAR_SCREEN {0x1B, '[', '2', 'J', '\0'}
#define HOME_CURSOR {0x1B, '[', 'f', '\0'}

void USART_init(void);
void USART_putchar(char character);
void USART_putstring(char *string);
void USART_clearscreen();

#endif