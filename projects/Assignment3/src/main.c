/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following files for  */
/* the implementation and explanation: */
/*																		 */
/* Bla Bla Bla												 */
/***************************************/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "./lib/pwm/pwm.h"

int main(void)
{
  // Initialize User Button on STM32F0-Discovery
  //STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

  pwm_init();
	
	for(;;) { ; }
}
