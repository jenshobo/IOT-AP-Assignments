//--------------------------------------------------------------
// File     : stm32_ub_spi2_hd.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32_UB_SPI2_HD_H
#define __STM32_UB_SPI2_HD_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_spi.h"



typedef enum {
  SPI_FIRST_BYTE = 0,  // erstes Byte (von mehreren)
  SPI_LAST_BYTE,       // letztes Byte (von mehreren)
  SPI_OTHER_BYTE,      // nicht erstes und nicht letztes Byte
  SPI_SINGLE_BYTE      // ein einzelnes Byte
}SPI2_Byte_t;


//--------------------------------------------------------------
// SPI-Clock
// Grundfrequenz (SPI2)= APB1 (APB1=42MHz)
// Mögliche Vorteiler = 2,4,8,16,32,64,128,256
//--------------------------------------------------------------

//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_2   // Frq = 21 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_4   // Frq = 10,5 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_8   // Frq = 5.25 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_16  // Frq = 2.625 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_32  // Frq = 1.3125 MHz
#define SPI2_VORTEILER     SPI_BaudRatePrescaler_64  // Frq = 656.2 kHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_128 // Frq = 328.1 kHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_256 // Frq = 164.0 kHz




//--------------------------------------------------------------
// Struktur eines SPI-Pins
//--------------------------------------------------------------
typedef struct {
  GPIO_TypeDef* PORT;     // Port
  const uint16_t PIN;     // Pin
  const uint32_t CLK;     // Clock
  const uint8_t SOURCE;   // Source
}SPI2_PIN_t; 

//--------------------------------------------------------------
// Struktur vom SPI-Device (im Half-Duplex-Mode)
//--------------------------------------------------------------
typedef struct {
  SPI2_PIN_t  SCK;        // SCK-Pin
  SPI2_PIN_t  DIO;        // DIO-Pin
}SPI2_DEV_t;


//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
ErrorStatus UB_SPI2_HD_Init(void);
void UB_SPI2_HD_SendByte(uint8_t wert);
uint8_t UB_SPI2_HD_ReceiveByte(SPI2_Byte_t byte_nr);


//pvvz
void updateDisplay(void);
//pvvz


//--------------------------------------------------------------
#endif // __STM32_UB_SPI2_HD_H
