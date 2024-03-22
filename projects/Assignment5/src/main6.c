/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* state.c														 */
/* tim_it.c														 */
/* pwm.c															 */
/* dac.c															 */
/* adc.c															 */
/***************************************/

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#include "./lib/state/state.h"
#include "./lib/tim_it/tim_it.h"
#include "./lib/adc/adc.h"

int main(void)
{
	state_init();			/* Start state logic */
	interrupt_init();	/* Start timer interrupts */
	adc_init();				/* Setup ADC conversion */
	
	switch_state();		/* Start PWM or DAC */
	
	for(;;) 
	{
		//PWR_EnterSleepMode(PWR_SLEEPEntry_WFI); /* Put CPU in sleep mode, project does not support this now sadly */
	}
}
