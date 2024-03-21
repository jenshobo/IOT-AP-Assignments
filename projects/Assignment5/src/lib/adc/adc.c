/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
/* Please see the following file(s)		 */
/* for used includes, defines and/or	 */
/* consts, if any.										 */
/*																		 */
/* adc.h															 */
/***************************************/

#include "adc.h"

void adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	// (#) Enable the ADC interface clock using
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	// (#) ADC pins configuration
	// (++) Enable the clock for the ADC GPIOs using the following function:
	// RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);
	// (++) Configure these ADC pins in analog mode using GPIO_Init();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// (#) Configure the ADC conversion resolution, data alignment, external
	// trigger and edge, scan direction and Enable/Disable the continuous mode
	// using the ADC_Init() function.
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure);
	// Calibrate ADC before enabling
	ADC_GetCalibrationFactor(ADC1);
	// (#) Activate the ADC peripheral using ADC_Cmd() function.
	ADC_Cmd(ADC1, ENABLE);
	// Wait until ADC enabled
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN) == RESET);
}
