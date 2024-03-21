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

#include "./lib/tim_it/tim_it.h"
#include "./lib/pwm/pwm.h"
#include "./lib/dac/dac.h"

//#define USE_DAC 1 // comment out to use PWM, otherwise DAC is used

int main(void)
{
	interrupt_init();
	
	#ifndef USE_DAC
	pwm_init();
	#else
	dac_init();
	#endif
	
	for(;;) { ; }	/* Idle loop */
}

/* TODO (in order):
 * Implement button interrupt
 * Implement state change
 */
