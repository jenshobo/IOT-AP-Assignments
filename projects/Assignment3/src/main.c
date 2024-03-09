/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* stm32f0_it.c												 */
/* pwm.c															 */
/***************************************/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "./lib/pwm/pwm.h"

int main(void)
{
  pwm_init(); 	/* Start timers */
	for(;;) { ; }	/* Idle loop */
}
