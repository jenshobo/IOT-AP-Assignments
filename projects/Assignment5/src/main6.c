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
#include "./lib/pwm/pwm.h"
#include "./lib/dac/dac.h"
#include "./lib/adc/adc.h"

int main(void)
{
	state_init();
	interrupt_init();
	pwm_init();
	adc_init();
	
	for(;;) 
	{
		//PWR_EnterSleepMode(PWR_SLEEPEntry_WFI); // shit breaks when this is enabled due to the project not having the correct startup files, move everything over to a good one... again.
	}
}

/* TODO:
 * Add Sleep mode in main for loop
 * Add .txt explaining everything
 */
