/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* delay.h														 */
/***************************************/

#include "delay.h"	/* Include own header file */

void delay(const uint32_t delay_time)
{
	uint32_t timer = delay_time;
	for (; timer > 0; timer--) { ; }	/* Do nothing for <timer> cycles */
}