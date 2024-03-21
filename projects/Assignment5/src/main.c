/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* pwm.c															 */
/* dac.h															 */
/***************************************/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "./lib/pwm/pwm.h"
#include "./lib/dac/dac.h"

int main(void)
{
	pwm_init();
	//dac_init();
	
	for(;;) { ; }	/* Idle loop */
}

/* TODO (in order):
 * Implement DAC
 * Implement button interrupt
 * Implement state change
 * Fix PWM sound
 */
