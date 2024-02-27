/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* queue.h														 */
/***************************************/

#include "queue.h"	/* Include own header file */

char queue[QUEUE_SIZE];			/* Queue array */
uint8_t start_pointer = 0;	/* Start position of existing queue */
uint8_t end_pointer = 0;		/* End position of existing queue */

void queue_init(void)
{
	led_matrix_init();	/* Initialize led_matrix */
}

void queue_push(char character)
{
	if (queue_get_new_position(end_pointer) == start_pointer)	/* If queue is empty */
	{
		flash_led();																						/* Flash led matrix */
		return;																									/* Return out of methode, can't add item */
	}
	
	queue[end_pointer] = character;														/* Place item in queue */
	
	end_pointer = queue_get_new_position(end_pointer);				/* Move <end_pointer> to next in queue */
	set_matrix(end_pointer, start_pointer);										/* Set led_matrix */
}

char queue_pop(void)
{
	char character = ' ';
	
	if (queue_get_length() <= 0)														/* If queue is empty */
	{	return '\0';	}																				/* Return '\0' */
	character = queue[start_pointer];												/* Get item from queue */
	
	start_pointer = queue_get_new_position(start_pointer);	/* Move <start_pointer> to next in queue */
	set_matrix(end_pointer, start_pointer);									/* Set led_matrix */
	
	return character;																				/* Return found character */
}

uint8_t queue_get_length(void)
{
	int16_t difference = start_pointer - end_pointer;	/* Calculate difference */
	if (difference < 0)																/* If difference < 0 */
	{	difference = difference + QUEUE_SIZE - 1;	}			/* Offset difference to compensate */
	return difference;																/* Return difference, aka length */
}

uint8_t queue_get_new_position(uint8_t pointer)
{
	return pointer >= QUEUE_SIZE - 1 ? 0 : pointer + 1;	/* Return next position in queue */
}