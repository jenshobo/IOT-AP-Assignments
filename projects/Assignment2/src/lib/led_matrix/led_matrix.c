/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* led_matrix.h												 */
/***************************************/

#include "led_matrix.h"	/* Include own header file */

void led_matrix_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	/* Enable GPIOC peripheral clock */
	GPIOC->MODER |= LED_MATRIX; 				/* Set PC1 to PC10 to output */
}

void set_matrix(uint8_t start_pointer, uint8_t end_pointer)
{
	uint16_t matrix = 0;
	while (start_pointer != end_pointer)									/* Loop over all items in queue */
	{
		matrix |= power_of(2, end_pointer);									/* Set bit of item in queue high */
		end_pointer = queue_get_new_position(end_pointer);	/* Get next location in queue */
	}
	GPIOC->ODR = matrix MATRIX_OFFSET;										/* Write to GPIOC with offset */
}

uint16_t power_of(uint8_t base, uint8_t exponent)
{
	uint16_t start = 1;					/* Start value of pow */
	while (exponent > 0)				/* While exponent is not zero */
	{
		start = start * base;			/* Multiply start with base */
		exponent = exponent - 1;	/* Lower exponent by 1 */
	}
	return start;								/* Return new start value */
}

void flash_led()
{
	uint8_t delay_time = FLASH_DELAY;
	for (; delay_time > 0; delay_time--)	/* Loop for <delay_time> cycles */
	{
		GPIOC->ODR = ~GPIOC->ODR;						/* Reverse GPIOC */
		delay(ONE_SECOND / FLASH_SPEED);		/* Delay for <FLASH_SPEED> cycles */
	}
}