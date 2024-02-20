#ifndef __USART_H
#define __USART_H

#include "stm32f0xx.h"

void USART_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);
	GPIOA->AFR[1] |= 0x00000110;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = 0x01A1;
	USART1->CR1 = USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	
   // RXNE interrupt enable
   USART1->CR1 |= USART_CR1_RXNEIE;
   
   // USART1 interrupts enable in NVIC
   NVIC_EnableIRQ(USART1_IRQn);
   NVIC_SetPriority(USART1_IRQn, 0);
   NVIC_ClearPendingIRQ(USART1_IRQn);
}

char USART_getc(void)
{
	char c;
	if((USART1->ISR & USART_ISR_ORE) != 0)
	{
		USART1->ICR |= USART_ICR_ORECF;
	}
	while((USART1->ISR & USART_ISR_RXNE) == 0){ } // this is polling
	c = (char)USART1->RDR;
	return(c);
}

void USART_putc(char c)
{
	while((USART1->ISR & USART_ISR_TXE) == 0); // this is polling
	USART1->TDR = c;
}

#endif