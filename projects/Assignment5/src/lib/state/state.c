/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* state.h														 */
/***************************************/

#include "state.h"
void state_led_init(void);
void state_it_init(void);

void state_init(void)
{
	state_it_init();
	state_led_init();
}

void state_led_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	/* GPIOC Periph clock enable */
	
	GPIOC->MODER |= GPIO_MODER_MODER9_0;	/* Set PC9 output */
}

void state_it_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;	/* GPIOA Periph clcok enable */
	
	EXTI->IMR |= EXTI_IMR_MR0;					/* Set GPIO0 pin mask */
	EXTI->RTSR |= EXTI_RTSR_TR0;				/* Set GPIO0 rising edge interrupt trigger */
	
	NVIC_EnableIRQ(EXTI0_1_IRQn);				/* Enable EXTI0_1 interrupts */
	NVIC_SetPriority(EXTI0_1_IRQn,0);
}

void switch_state(void)
{
	static bool state = false;
	
	if (state)
	{
		GPIOC->BSRR = GPIO_BSRR_BR_9;
		dac_dest();
		pwm_init();
	}
	else
	{
		GPIOC->BSRR = GPIO_BSRR_BS_9;
		pwm_dest();
		dac_init();
	}
	
	state = !state;
}

void delay(const uint32_t time)
{
	volatile uint32_t timer = 0;
	for (; timer < time; timer++) { ; }
}
