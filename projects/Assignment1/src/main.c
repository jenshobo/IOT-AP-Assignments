/***************************************/
/* Code writen for Windesheim IOT 2024 */
/*     <studentnumber> mod 4 = 2       */
/*       Patern used: X0011100X        */
/***************************************/
/* DISCLAIMER, POLLING IS NOT REQUIRED */
/* THE USE OF INTERRUPTS HAS BEEN			 */
/* APROVED BY HP Veldhuijzen van 			 */
/* Zanten. Thank you, please rate fair */
/* 																		 */
/* Explanation for the code:					 */
/* 																		 */
/* The code start with setup code.		 */
/* This initializes the output pin and */
/* sets up the interupt routine.			 */
/* To round off the starting paturn is */
/* displayed on the led matrix.				 */
/* 																		 */
/* Next the program does nothing but 	 */
/* wait for a pin change interrupt.		 */
/* Ones one is detected the interrupt  */
/* routing will do the following:			 */
/* A) check the direction based off		 */
/* 		status of the other input pin.	 */
/* B) Move the value over one in the	 */
/* 		resulting direction.						 */
/* C) Clamp the value.								 */
/* D) Write the value to the output		 */
/* 		pins.														 */
/* E) Debounce delay, considering			 */
/* 		this is only the first					 */
/* 		assignment and the overall size	 */
/* 		of the program, I see no reasonq */
/* 		to overcomplicate with timers.	 */
/* F) Reset the interrupt routine,		 */
/* 		this is done last to prevent		 */
/* 		another interrupt from taking		 */
/* 		place. Trust me, it's more       */
/* 		stable like this.								 */
/* 																		 */
/* After this the program goes back		 */
/* to waiting for another interrupt.	 */
/***************************************/
#include "stm32f0xx.h"

#define GPIOC_LED_MATRIX 0x00155554				/* PC1 to PC10 MODER register set */

#define START_VAL 0x00E0 									/* Start value for LED_MATRIX */
#define MAX_VAL   0x3800 									/* Max value for LED_MATRIX   */
#define MIN_VAL   0x0007 									/* Min value for LED MATRIX   */

#define DEBOUNCE_TIME 6000								/* Debounce for knob */
#define SHIFTCORRECTION >>1								/* position shift correction */

void setInterrupt(void);
uint16_t clampMatrixValue(uint16_t current_value);
void delay(const uint16_t time);								

void EXTI0_1_IRQHandler(void)							/* Maybe put this in de stm32f0xx_it.c file if posible */
{
	static uint16_t matrix_value = START_VAL;				/* Set start value */
	
	if (GPIOA->IDR & GPIO_BRR_BR_1)									/* Check direction of knob */
	{ matrix_value = matrix_value>>1;	}							/* Knob direction right >> 1 */
	else
	{ matrix_value = matrix_value<<1;	}							/* Knob direction left  << 1 */
	
	matrix_value = clampMatrixValue(matrix_value);	/* Clamp value between MAX_VAL and MIN_VAL */
		
	GPIOC->ODR = matrix_value SHIFTCORRECTION;			/* Display value in LED_MATRIX + position shift correction */
	
	delay(DEBOUNCE_TIME);														/* Start debounce time */ /* See line 30 for why I use a debounce here */
	EXTI->PR |= EXTI_PR_PR0;												/* Clear Pending flag */ /* See line 35 for why this is at the bothem */
}

int main(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;			/* GPIOC Periph clock enable */
	
	GPIOC->MODER |= GPIOC_LED_MATRIX;				/* Set PC1 to PC10 to output mode */
	
	setInterrupt();
	
	GPIOC->ODR = START_VAL SHIFTCORRECTION;	/* Turn on LED's on starting value + position shift correction */
	for(;;) { ; }														/* Idle loop */
}

void setInterrupt(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;	/* GPIOA Periph clcok enable */
	
	EXTI->IMR |= EXTI_IMR_MR0;					/* Set GPIO0 pin mask */
	EXTI->RTSR |= EXTI_RTSR_TR0;				/* Set GPIO0 rising edge interrupt trigger */
	
	NVIC_EnableIRQ(EXTI0_1_IRQn);				/* Enable EXTI0_1 interrupts */
	NVIC_SetPriority(EXTI0_1_IRQn,0);		/* Set Priority for intterupt */
}

uint16_t clampMatrixValue(uint16_t current_value)
{
	if (current_value <= MIN_VAL)
	{ return MIN_VAL; }									/* Return min if value is to small */
	else if (current_value >= MAX_VAL)
	{ return MAX_VAL; }									/* Return max if value is to big */
	else
	{ return current_value; }						/* Return old value */
}

void delay(const uint16_t time)
{
	volatile uint16_t i;
	
	for (i=time;i>0;i--) { ; } /* Idle for <time> cycles */
}