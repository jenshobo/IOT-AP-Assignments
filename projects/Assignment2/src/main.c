/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* USART.c														 */
/* queue.c														 */
/* led_matrix.c												 */
/* stm32f0xx_it.c 										 */
/***************************************/

#include "../USART.h"
#include "../queue.h"

int main(void)
{
	queue_init();
	USART_init();
	for (;;) { ; }
}