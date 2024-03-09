/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* pwm.h															 */
/***************************************/
#include "pwm.h"

void init_GPIO(void);		/* Private methode(s) */
void init_led_timers(void);
void init_interrupt_timer(void);

void pwm_init(void)
{
	init_GPIO();
	init_led_timers();
	init_interrupt_timer();
}

void init_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;									/* Data type for storing information */

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);		/* Enable GPIOB peripheral clock */
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;					/* Set GPIO to alternate function mode */
  GPIO_InitStructure.GPIO_Pin = 0x0C33;									/* Set pin PB0, PB1, PB4, PB5, PB10 and PB11 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2; 	/* Set to medium speed */
  GPIO_Init(GPIOB, &GPIO_InitStructure);								/* Initialize pins */
	
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0,  GPIO_AF_1);	/* Set alternate function source */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1,  GPIO_AF_1);	/* Set alternate function source */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4,  GPIO_AF_1);	/* Set alternate function source */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5,  GPIO_AF_1);	/* Set alternate function source */
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_2);	/* Set alternate function source */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_2);	/* Set alternate function source */
}
void init_led_timers(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;								/* Data type for storing information */
  TIM_OCInitTypeDef       TIM_OCInitStructure;									/* Data type for storing information */
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);					/* Enable TIM3 peripheral clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);					/* Enable TIM4 peripheral clock */
  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				/* Set clock devision */
  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;	/* Set counter mode */
  TIM_TimeBaseStructure.TIM_Period        = PERIOD - 1;					/* Set period */
  TIM_TimeBaseStructure.TIM_Prescaler     = LED_PRESCALER - 1; 	/* Set prescaler (See pwm.h for calculation)*/
	
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);								/* Set settings for TIM3 */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);								/* Set seetings for TIM4 */
  
  TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;				/* Set PWM mode */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	/* Enable output */
  TIM_OCInitStructure.TIM_Pulse       = START_PERCENTAGE;				/* Set Duty cycle */
  TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;		/* Set polarity */
	
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);											/* Set TIM3 output channel 1 */
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);											/* Set TIM3 output channel 2 */
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);											/* Set TIM3 output channel 3 */
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);											/* Set TIM3 output channel 4 */
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);											/* Set TIM3 output channel 3 */
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);											/* Set TIM3 output channel 4 */

  TIM_Cmd(TIM3, ENABLE);																				/* Start TIM3 */
	TIM_Cmd(TIM2, ENABLE);																				/* Start TIM2 */
}

void init_interrupt_timer(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;								/* Data type for storing information */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);					/* Enable TIM14 peripheral clock */
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				/* Set clock devision */
  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;	/* Set counter mode */
	TIM_TimeBaseStructure.TIM_Period 				= PERIOD - 1;					/* Set period */
  TIM_TimeBaseStructure.TIM_Prescaler     = MASK_PRESCALER - 1;	/* Set prescaler (See pwm.h for calculation)*/
	
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);							/* Set settings for TIM14 */
	
	TIM_Cmd(TIM14, ENABLE);																				/* Start TIM14 */
	
	TIM_SetCompare1(TIM14, PERIOD);																/* Set duty cycle to 100% */
	TIM14->DIER |= TIM_DIER_CC1IE; 																/* Snable interrupt on capture compare */
	
	NVIC_EnableIRQ(TIM14_IRQn); 																	/* Enable overal interrupt for TIM14 */
	NVIC_ClearPendingIRQ(TIM14_IRQn);															/* If set, clear interrupt flag */
}
