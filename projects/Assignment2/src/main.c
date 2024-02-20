/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/

#include "stm32f0xx.h"
#include "../USART.h"

void delay(const uint32_t time);

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= 0x00155554;
	
	USART_init(); // init queue
	//queue_init(); // init usart
	while(1)
	{/*
		if (queue_get_length() > 0)// if item in queue
		{
			delay(SystemCoreClock/8); // wait 1 sec
			USART_putc(queue_pop()); // send to putty
		}*/
	}
}
\

void delay(const uint32_t time)
{
	volatile int i;
	
	for (i = time; i > 0; i--) { ; }
}