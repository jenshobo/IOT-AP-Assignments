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

#include "./lib/state/state.h"
#include "./lib/tim_it/tim_it.h"
#include "./lib/pwm/pwm.h"
#include "./lib/dac/dac.h"

int main(void)
{
	state_init();
	interrupt_init();
	pwm_init();
	
	for(;;) { ; }	/* Idle loop */
}

/* TODO:
 * Add third timer for ADC (10Hz)
 * Add ADC for reading potentiometer
 * Add interrupt routine to change TIM6 speed (50% - 200%, 30KHz - 120KHz)
 */
