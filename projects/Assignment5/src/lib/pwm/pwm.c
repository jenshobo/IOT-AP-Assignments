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
	pwm_gpio_init();
	pwm_signal_init();
}

void pwm_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_4);
}

void pwm_signal_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef				TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 				= PERIOD - 1;
	TIM_TimeBaseStructure.TIM_Prescaler 		= PRESCALER - 1;
	
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse       = START_PERCENTAGE;
  TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
	
  TIM_OC1Init(TIM14, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM14, ENABLE);
}
