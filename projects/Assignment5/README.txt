+---------------- - -
| Working requirements:
+---------------- - -
| [*] PWM
| [*] DAC
| [*] ADC (including LED)
| [*] Sleep mode
|
+---------------- - -
| Non-working requirements:
+---------------- - -
| N.A.
|
+---------------- - -

+---------------- - -
| Pin layout:
+---------------- - -
| [*] PWM == PA4
| [*] DAC == PA4
| [*] ADC == PC1
| [*] LED == build-in or PC9
|
+---------------- - -

+---------------- - -
| Timers used:
+---------------- - -
| [*] Systick
| 	- Reading ADC conversion
|
| [*] TIM6
| 	- Generate sample rate interrupt (8KHz)
|
| [*] TIM14
| 	- Generate PWM signal (60KHz)
|
+---------------- - -
| Interrrupts used:
+---------------- - -
| [*] SysTick_Handler
| 	- Reading ADC conversion
|
| [*] TIM6_DAC_IRQHandler
| 	- Reading WAV sample
|	- Setting PWM and DAC
|
| [*] EXTI0_1_IRQHandler
| 	- Switch PWM and DAC state
|
+---------------- - -

+---------------- - -
| Global variables:
+---------------- - -
| N.A.
|
+---------------- - -