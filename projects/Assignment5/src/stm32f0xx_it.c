/**
  ******************************************************************************
  * @file    stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "STM32F0_discovery.h"

#include "./../data/sound_data.h"
#include "./lib/state/state.h"
#include "./lib/tim_it/tim_it.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	static uint16_t adc;
	
	ADC_StartOfConversion(ADC1);															/* Start conversion */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);		/* Wait for result */
	adc = ADC_GetConversionValue(ADC1);												/* Get result */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOSEQ) == RESET);	/* Wait for completion */
	
	map_prescaler(adc);																				/* Set result */
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles ADC1 and COMP global interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_COMP_IRQHandler(void)
{
  if(ADC_GetITStatus(ADC1, ADC_IT_AWD) != RESET)
  {
    ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
    
    // Turn on Window Watchdog indicator
    STM_EVAL_LEDOn(LED4);
  }
}

void TIM6_DAC_IRQHandler(void)
{
	static uint16_t index = 0;
	
	if (TIM6->SR & TIM_SR_UIF != 0)
	{
		TIM6->SR &= ~TIM_SR_UIF;																/* Reset interrupt flag */
		
		TIM_SetCompare1(TIM14, test_data[index]);								/* set PWM value */
		DAC_SetChannel1Data(DAC_Align_12b_R, test_data[index]);	/* set DAC value */
		
		index++;
	
		if (index > test_length)																/* If end of array is reached */
		{	
			index = 0;																						/* Reset and play again */
		}
	}
}


void EXTI0_1_IRQHandler(void)
{
	delay(1000);							/* act as debounce */
	EXTI->PR |= EXTI_PR_PR0;	/* Clear Pending flag */
	
	switch_state();						/* Switch between PWM and DAC */
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
