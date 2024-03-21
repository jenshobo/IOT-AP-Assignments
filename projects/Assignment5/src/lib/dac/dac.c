/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* dac.h															 */
/***************************************/

#include "dac.h"

//void dac_gpio_init(void);				/* Private methodes */
//void dac_signal_init(void);

void dac_init(void)
{
	//dac_gpio_init();
	//dac_signal_init();
}
/*
void dac_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void dac_signal_init(void)
{
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);
}*/
