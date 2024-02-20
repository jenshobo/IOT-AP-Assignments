/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* USART.h														 */
/* queue.h														 */
/* led_matrix.h												 */
/* stm32f0xx_it.c 										 */
/***************************************/

#include "../USART.h"

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= 0x00155554;
	
	USART_init();
	for (;;) { ; }
}