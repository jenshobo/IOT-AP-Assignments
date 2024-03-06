/***************************************/
/* Code writen for Windesheim IOT 2024 */
/***************************************/
#include "pwm.h"

#define PWM_PERIOD 1000 // 1 ms period
#define PWM_PULSE 800 // 0.8 ms pulse (80% duty cycle)

void pwm_init(void)
{
	// setting pins up
   RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable GPIOB clock
	
   GPIOB->MODER |= GPIO_MODER_MODER0_1; // Set pin 0 to alternate function mode
   GPIOB->AFR[0] |= 0x1; // Select AF2 (TIM2) for pin 0
	
	// setting timers up
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable TIM2 clock

  // Configure TIM2
  TIM2->CR1 &= ~TIM_CR1_CEN; // Disable TIM2
  TIM2->PSC = 0; // No prescaler
  TIM2->ARR = PWM_PERIOD - 1; // Auto-reload value
  TIM2->CCR1 = PWM_PULSE; // Capture/compare register value

  TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM mode 1
  TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Preload enable

  TIM2->CCER |= TIM_CCER_CC1E; // Enable output on channel 1

  TIM2->CR1 |= TIM_CR1_ARPE; // Auto-reload preload enable
  TIM2->EGR |= TIM_EGR_UG; // Generate update event to load the registers

  TIM2->CR1 |= TIM_CR1_CEN; // Enable TIM2
	
}