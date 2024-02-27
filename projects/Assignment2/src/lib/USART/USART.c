/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* USART.h														 */
/***************************************/

#include "USART.h"	/* Include own header file */

void USART_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;														/* Enable GPIOA peripheral clock */
	GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);	/* Set PA9 and PA10 to alternate mode */
	GPIOA->AFR[1] |= AFR_SET;																			/* Set PA9 and PA10 for USART communication */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;													/* Enable ADC peripheral clock */
	USART1->BRR = BOUD_RATE;																			/* Set boudspeed 115200 */
	USART1->CR1 = USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;			/* Enable USART stop mode, enable receiving and enable transmission */
	
   USART1->CR1 |= USART_CR1_RXNEIE;															/* Enable RXNE interrupt */
   
   NVIC_EnableIRQ(USART1_IRQn);																	/* Enable USART interrupt */
   NVIC_ClearPendingIRQ(USART1_IRQn);														/* Clear pending flag if set */
}

void USART_putchar(char character)
{
	while((USART1->ISR & USART_ISR_TXE) == 0);	/* Wait for next possible moment */
	USART1->TDR = character;										/* Write character to serial */
}

void USART_putstring(char *string)
{
	uint8_t index = 0;
	char currentChar = ' ';
	for (; currentChar != '\0'; index++)	/* Loop over all characters in char */
	{
		currentChar = string[index];				/* Get current character */
		USART_putchar(currentChar);					/* Write character to serial */
	}
}

void USART_clearscreen(void)
{
  char cmd1[5] = CLEAR_SCREEN;
  char cmd2[4] = HOME_CURSOR;
  
  USART_putstring(cmd1);
  USART_putstring(cmd2);
}