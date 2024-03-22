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

void dac_gpio_init(void);				/* Private methodes */
void dac_signal_init(void);

void dac_init(void)
{
	dac_gpio_init();		/* Initialize output pin for DAC use */
	dac_signal_init();	/* Initialize DAC mode */
}

void dac_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	/* Enable GPIOA peripheral clock (if not yet set) */
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;						/* Use pin 4 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;				/* Use analoge in/out mode */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		/* Disable pull-up */
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);							/* Initialize GPIOA */
}

void dac_signal_init(void)
{
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);						/* Enable DAC peripheral clock */
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;							/* Set trigger to none */
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;	/* Enable output buffer */
	
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);									/* Initialize DAC */
	
	DAC_Cmd(DAC_Channel_1, ENABLE);																/* Start DAC */
}

void dac_dest(void)
{
	DAC_Cmd(DAC_Channel_1, DISABLE);	/* Disable DAc */
}
