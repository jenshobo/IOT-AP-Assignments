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

/******************************************************************************/
/* Some contect for this, truthfully, questionable code.											*/
/* Oke, So I got the TIM2 and TIM3 working on the required hertz (see pwm.h)  */
/* but for TIM14 I could not get it to work properly. 												*/
/* Acording to my math, which is probably sub-par, TIM14 should work with the */
/* required hertz (again, see pwm.h), but the timer interrupt appears to go 	*/
/* too fast, I tried changing the prescaler and period values but the timer		*/
/* stayed the same speed, so I believe the issue is that the interrupt is			*/
/* being called as soon as possible, resulting in a timer which is correctly 	*/
/* set up to still be bad. 																										*/
/* 																																						*/
/* Due to the lack of time I regretfully have to make due with this timer and */
/* thus you'll find a softwarematicly made timer (line 145 to line 155). 			*/
/* This little bit of code almost give the end result as seen on the					*/
/* assigment, it's just a little bit faster than required. But again, I am 		*/
/* running out of time, so this will have to do sadly.												*/
/******************************************************************************/

void TIM14_IRQHandler(void)
{
	#define max_wait   65355
	
	#define first_led  0
	#define second_led 1
	#define third_led  2
	#define forth_led  3
	#define fifth_led  4
	#define sixth_led  5
	
	#define milestone_stepsize 15
	#define max_milestone      150
	
	#define step_size 2
	
	static uint8_t values[] = { START_PERCENTAGE, START_PERCENTAGE, START_PERCENTAGE, START_PERCENTAGE, START_PERCENTAGE, START_PERCENTAGE };
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
	
	if (counter <= milestone_stepsize)
	{
		values[first_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 2)
	{
		values[first_led] -= step_size;
		values[second_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 3)
	{
		values[first_led] += step_size;
		values[second_led] -= step_size;
		values[third_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 4)
	{
		values[second_led] += step_size;
		values[third_led] -= step_size;
		values[forth_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 5)
	{
		values[third_led] += step_size;
		values[forth_led] -= step_size;
		values[fifth_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 6)
	{
		values[forth_led] += step_size;
		values[fifth_led] -= step_size;
		values[sixth_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 7)
	{
		values[fifth_led] += step_size;
		values[sixth_led] -= step_size;
	}
	else if (counter <= milestone_stepsize * 8)
	{
		values[sixth_led] += step_size;	
	}
	
	TIM_SetCompare1(TIM3, values[third_led ]);
	TIM_SetCompare2(TIM3, values[forth_led ]);
	TIM_SetCompare3(TIM3, values[first_led ]);
  TIM_SetCompare4(TIM3, values[second_led]);
	TIM_SetCompare3(TIM2, values[fifth_led ]);
	TIM_SetCompare4(TIM2, values[sixth_led ]);
	
	if (counter >= max_milestone)
	{
		values[first_led ] = START_PERCENTAGE;
		values[second_led] = START_PERCENTAGE;
		values[third_led ] = START_PERCENTAGE;
		values[forth_led ] = START_PERCENTAGE;
		values[sixth_led ] = START_PERCENTAGE;
		values[sixth_led ] = START_PERCENTAGE;
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
