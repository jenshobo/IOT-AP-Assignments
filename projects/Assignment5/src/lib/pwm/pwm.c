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

void pwm_gpio_init(void);		/* Private methode(s) */
void pwm_signal_init(void);

void pwm_init(void)
{
	pwm_gpio_init();		/* Initialize output pin for PWM use */
	pwm_signal_init();	/* Initialize TIM14 */
}

void pwm_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);		/* Enable GPIOA peripheral clock (if not yet set) */
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;					/* Set GPIO alternate function */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;							/* Use pin 4 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;		/* Set speed high */
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);								/* Initialize GPIOA */
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_4);	/* Setup alternate function */
}

void pwm_signal_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef				TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);					/* Enable TIM14 peripheral clock */
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				/* Set clock devision */
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;	/* Set clock counter upwards */
	TIM_TimeBaseStructure.TIM_Period 				= PERIOD - 1;					/* Set clock period */
	TIM_TimeBaseStructure.TIM_Prescaler 		= PRESCALER - 1;			/* Set clock prescaler */
	
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);							/* Initialize TIM14 */
	
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;				/* Set PWM mode */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	/* Set output mode */
  TIM_OCInitStructure.TIM_Pulse       = START_PERCENTAGE;				/* Set period percentage */
  TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;		/* Set polarity */
	
  TIM_OC1Init(TIM14, &TIM_OCInitStructure);											/* initialize PWM */
	
	TIM_Cmd(TIM14, ENABLE);																				/* Start TIM14 */
}

void pwm_dest(void)
{
	TIM_Cmd(TIM14, DISABLE);	/* Disable TIM14 */
}
