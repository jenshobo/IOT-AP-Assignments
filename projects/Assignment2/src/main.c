/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* USART.c														 */
/* delay.c														 */
/* queue.c														 */
/* led_matrix.c												 */
/* stm32f0xx_it.c 										 */
/***************************************/

#include "./lib/USART/USART.h"
#include "./lib/queue/queue.h"
#include "./lib/delay/delay.h"

int main(void)
{
	queue_init();
	USART_init();
	
	USART_clearscreen();
	for (;;)
	{
		if (queue_get_length() != 0)
		{
			USART_putstring("This is a test: ");
			USART_putchar(queue_pop());
			USART_putstring("\r\n");
			delay(ONE_SECOND);
		}
	}
}