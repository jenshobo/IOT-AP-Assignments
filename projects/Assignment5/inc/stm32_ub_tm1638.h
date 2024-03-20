//--------------------------------------------------------------
// File     : stm32_ub_tm1638.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32_UB_TM1638_H
#define __STM32_UB_TM1638_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f0xx.h"

//--------------------------------------------------------------
// ChipSelect-Pin vom TM1638
//--------------------------------------------------------------
#define TM1638_CS_PIN         GPIO_Pin_12
#define TM1638_CS_GPIO_PORT   GPIOB
#define TM1638_CS_GPIO_CLK    RCC_AHBPeriph_GPIOB


//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
#define TM1638_INIT_DELAY     5000000 // kleine Pause beim init (>3000000)
#define TM1638_DELAY_A        500     // (>100)
#define TM1638_DELAY_B        1000    // (>400)
#define TM1638_DELAY_C        500     // (>200)
#define TM1638_DELAY_D        500     // (>100)
#define TM1638_MAX_RAM_ADR    0x0F    // max ram adresse


//--------------------------------------------------------------
// TM1638 Kommandos
//--------------------------------------------------------------
#define TM1638_CMD_02_FIX     0x44  // FixAdr, WriteData
#define TM1638_CMD_02_KEY     0x42  // Keyscan
#define TM1638_CMD_03         0xC0  // Ram-Adr [C0...CF]
#define TM1638_CMD_04_OFF     0x80  // Display OFF
#define TM1638_CMD_04_ON      0x88  // Display ON [88...8F]
#define TM1638_CMD_16         0x40  // Auto address increment

//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
ErrorStatus UB_TM1638_Init(void);
void UB_TM1638_Display_Off(void);
void UB_TM1638_Display_On(uint8_t pwm);
void UB_TM1638_LED_On(uint8_t led_nr);
void UB_TM1638_LED_Off(uint8_t led_nr);
void UB_TM1638_LED_Value(uint8_t wert);
void UB_TM1638_7Seg_Ziffer(uint8_t segment_nr, uint8_t ziffer);
void UB_TM1638_7Seg_Dec(uint32_t wert);
void UB_TM1638_7Seg_Hex(uint32_t wert);
uint8_t UB_MT1638_Get_Key(void);

//--------------------------------------------------------------
#endif // __STM32_UB_TM1638_H
