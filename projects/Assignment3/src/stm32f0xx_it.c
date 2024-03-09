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
#include "./lib/pwm/pwm.h"

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
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles TIM1 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM14_IRQHandler(void)
{
	#define max_wait 32678
	
	static uint8_t values[] = { Start_Percentage, Start_Percentage, Start_Percentage, Start_Percentage, Start_Percentage, Start_Percentage };
	static uint16_t counter = 0;
	
	static uint16_t wait = 0;
	
	if (wait >= max_wait)
	{
		wait = 0;
	}
	else
	{
		wait++;
		return;
	}
	
	NVIC_ClearPendingIRQ(TIM14_IRQn);
	

	/*
	70% - 70% - 70% - 70% - 70% - 70% = 0   steps
	70% - 70% - 70% - 70% - 70% - 40% = 15  steps
	70% - 70% - 70% - 70% - 40% - 10% = 30  steps
	70% - 70% - 70% - 40% - 10% - 40% = 45  steps
	70% - 70% - 40% - 10% - 40% - 70% = 60  steps
	70% - 40% - 10% - 40% - 70% - 70% = 75  steps
	40% - 10% - 40% - 70% - 70% - 70% = 90  steps
	10% - 40% - 70% - 70% - 70% - 70% = 105 steps
	40% - 70% - 70% - 70% - 70% - 70% = 120 steps
	70% - 70% - 70% - 70% - 70% - 70% = 135 steps
	*/
	
	if (counter <= 15)
	{
		values[0] -= 2;
	}
	else if (counter <= 30)
	{
		values[0] -= 2;
		values[1] -= 2;
	}
	else if (counter <= 45)
	{
		values[0] += 2;
		values[1] -= 2;
		values[2] -= 2;
	}
	else if (counter <= 60)
	{
		values[1] += 2;
		values[2] -= 2;
		values[3] -= 2;
	}
	else if (counter <= 75)
	{
		values[2] += 2;
		values[3] -= 2;
		values[4] -= 2;
	}
	else if (counter <= 90)
	{
		values[3] += 2;
		values[4] -= 2;
		values[5] -= 2;
	}
	else if (counter <= 105)
	{
		values[4] += 2;
		values[5] -= 2;
	}
	else if (counter <= 120)
	{
		values[5] += 2;	
	}
	
	TIM_SetCompare1(TIM3, values[2]);
	TIM_SetCompare2(TIM3, values[3]);
	TIM_SetCompare3(TIM3, values[0]);
  TIM_SetCompare4(TIM3, values[1]);
	TIM_SetCompare3(TIM2, values[4]);
	TIM_SetCompare4(TIM2, values[5]);
	
	if (counter >= 150)
	{
		values[0] = Start_Percentage;
		values[1] = Start_Percentage;
		values[2] = Start_Percentage;
		values[3] = Start_Percentage;
		values[4] = Start_Percentage;
		values[5] = Start_Percentage;
		counter = 0;
	}
	else
	{
		counter++;
	}
	
	NVIC_ClearPendingIRQ(TIM14_IRQn);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
