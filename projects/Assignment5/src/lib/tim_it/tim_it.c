/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* tim_it.h														 */
/***************************************/

#include "tim_it.h"

void interrupt_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef        NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period 				= IT_PERIOD - 1;
	TIM_TimeBaseStructure.TIM_Prescaler 		= IT_PRESCALER - 1;
	
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel         = TIM6_DAC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM6, ENABLE);
	
	SysTick_Config(SystemCoreClock / 10);
}

void map_prescaler(uint16_t value)
{
	/* value = value
	 * low1  = 0
	 * high1 = 65535
	 * low2  = IT_PRESCALER_BOT
	 * high2 = IT_PRESCALER_TOP
	 */
	TIM6->PSC = REMAP(value) + 1;
}
