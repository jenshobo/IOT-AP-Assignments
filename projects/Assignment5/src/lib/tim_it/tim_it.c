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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);					/* Enable TIM6 peripheral clock */
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				/* Set clock devision */
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;	/* Set counter mode upwards */
	TIM_TimeBaseStructure.TIM_Period 				= IT_PERIOD - 1;			/* Set clock period - 1 */
	TIM_TimeBaseStructure.TIM_Prescaler 		= IT_PRESCALER - 1;		/* Set clock prescaler - 1 */
	
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);								/* Initialize TIM6 */
	
  NVIC_InitStructure.NVIC_IRQChannel         = TIM6_DAC_IRQn;		/* Enable TIM6 interrupt */
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;								/* Set priority */
  NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
	
  NVIC_Init(&NVIC_InitStructure);																/* Initialize interrupt routine */
	
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);										/* Enable TIM6 interrupts */
	
	TIM_Cmd(TIM6, ENABLE);																				/* Start TIM6 */
	
	SysTick_Config(IT_SYSTICK);																		/* Start systick */
}

void map_prescaler(uint16_t value)
{
	TIM6->PSC = REMAP(value) + 1;	/* Set TIM6 prescaler to new value remapped */
}
