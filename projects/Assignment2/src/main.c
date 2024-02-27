/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* USART.c														 */
/* delay.c														 */
/* queue.c														 */
/* led_matrix.c	(line 46-51)					 */
/* stm32f0xx_it.c 										 */
/***************************************/

#include "./lib/USART/USART.h"
#include "./lib/queue/queue.h"
#include "./lib/delay/delay.h"

int main(void)
{
	queue_init(); 													/* Create queue in queue.h */
	USART_init(); 													/* Setup USART registers */
	
	USART_clearscreen(); 										/* Clear junk from serial screen */
	for (;;)
	{
		if (queue_get_length() != 0) 					/* If item in queue */
		{
			USART_putstring("This is a test: ");
			USART_putchar(queue_pop()); 				/* Take top most item from queue */
			USART_putstring("\r\n");
			delay(ONE_SECOND); 									/* Wait ~one second */
		}
	}
}