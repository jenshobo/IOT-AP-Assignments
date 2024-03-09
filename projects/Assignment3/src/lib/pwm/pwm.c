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
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_2);//2);	/* Set alternate function source */
}
void init_led_timers(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef       TIM_OCInitStructure;
  
  //[..] To use the Timer in Output Compare mode, the following steps are mandatory:
  
  //(#) Enable TIM clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  //(#) Configure the Time base unit as described in the first part of this 
  //    driver, if needed, else the Timer will run with the default 
  //    configuration:
  //    (++) Autoreload value = 0xFFFF.
  //    (++) Prescaler value = 0x0000.
  //    (++) Counter mode = Up counting.
  //    (++) Clock Division = TIM_CKD_DIV1.
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period        = Period - 1; // 200 Hz (0.2 KHz, 5ms)
  TIM_TimeBaseStructure.TIM_Prescaler     = (SystemCoreClock / 20000) - 1;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  //(#) Fill the TIM_OCInitStruct with the desired parameters including:
  //    (++) The TIM Output Compare mode: TIM_OCMode.
  //    (++) TIM Output State: TIM_OutputState.
  //    (++) TIM Pulse value: TIM_Pulse.
  //    (++) TIM Output Compare Polarity : TIM_OCPolarity.
  TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse       = Start_Percentage;
  TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
  
  //(#) Call TIM_OCxInit(TIMx, &TIM_OCInitStruct) to configure the desired 
  //    channel with the corresponding configuration.
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	
	// this code is not needed here
	// set duty cycle to <Start_Percentage> (aka <Start_Percentage>% on, rest off)
	//TIM_SetCompare1(TIM3, Start_Percentage);
	//TIM_SetCompare2(TIM3, Start_Percentage);
	//TIM_SetCompare3(TIM3, Start_Percentage);
  //TIM_SetCompare4(TIM3, Start_Percentage);
		
	//TIM_SetCompare3(TIM2, Start_Percentage);
	//TIM_SetCompare4(TIM2, Start_Percentage);

  //(#) Call the TIM_Cmd(ENABLE) function to enable the TIM counter.
  TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void init_interrupt_timer(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 				= 100 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler     = (SystemCoreClock / 200) - 1; // 20 Hz (0.02 KHz, 50ms)
	
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM14, ENABLE);
	
	TIM14->DIER |= TIM_DIER_CC1IE; // enable interrupt on capture compare
	
	NVIC_EnableIRQ(TIM14_IRQn);
	NVIC_ClearPendingIRQ(TIM14_IRQn);
}
