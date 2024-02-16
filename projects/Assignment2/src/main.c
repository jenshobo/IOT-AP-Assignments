/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/

#include "stm32f0xx.h"
#include "../USART.h"

void USART_init(void);
void delay(const uint32_t time);

int main(void)
{
	USART_init();
	while(1)
	{
		char input = USART_getc();
		//delay(SystemCoreClock/8);
		USART_putc(input);
	}
}
\

void delay(const uint32_t time)
{
	volatile int i;
	
	for (i = time; i > 0; i--) { ; }
}