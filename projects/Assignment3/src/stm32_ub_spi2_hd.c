//--------------------------------------------------------------
// File     : stm32_ub_spi2_hd.c
//
// BASED ON : STM32_UB_SPI2_HD
//            see: https://mikrocontroller.bplaced.net/wordpress/?page_id=464
//
// CPU      : STM32F0
// Funktion : SPI-LoLevel-Funktionen (SPI-2) Half-Duplex-Mode
//
// Hinweis  : Pinbelegungen
//            SPI2 : SCK : PB13 
//                   DIO : PB15
//                   NSS : PB12 
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_spi2_hd.h"


//--------------------------------------------------------------
// Definition von SPI2
//--------------------------------------------------------------
SPI2_DEV_t SPI2DEV = {
// PORT , PIN       , Clock              , Source 
  {GPIOB,GPIO_Pin_13,RCC_AHBPeriph_GPIOB,GPIO_PinSource13}, // SCK an PB13
  {GPIOB,GPIO_Pin_15,RCC_AHBPeriph_GPIOB,GPIO_PinSource15}, // DIO an PB15
};



//--------------------------------------------------------------
// Init von SPI2 (im Half-Duplex-Mode)
// Return_wert :
//  -> ERROR   , wenn SPI schon mit anderem Mode initialisiert
//  -> SUCCESS , wenn SPI init ok war
//--------------------------------------------------------------
ErrorStatus UB_SPI2_HD_Init(void)
{
  ErrorStatus        ret_wert=ERROR;
  static uint8_t     init_ok=0;
  GPIO_InitTypeDef   GPIO_InitStructure;
  SPI_InitTypeDef    SPI_InitStructure;

  // initialisierung darf nur einmal gemacht werden
  if(init_ok!=0) {
    return(ret_wert);
  }

  // SPI-Clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  

  // Clock Enable der Pins
  RCC_AHBPeriphClockCmd(SPI2DEV.SCK.CLK, ENABLE);
  RCC_AHBPeriphClockCmd(SPI2DEV.DIO.CLK, ENABLE);

  // SPI Alternative-Funktions mit den IO-Pins verbinden
  GPIO_PinAFConfig(SPI2DEV.SCK.PORT, SPI2DEV.SCK.SOURCE, GPIO_AF_0);
  GPIO_PinAFConfig(SPI2DEV.DIO.PORT, SPI2DEV.DIO.SOURCE, GPIO_AF_0);

  // SPI als Alternative-Funktion
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  // SCK-Pin
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin   = SPI2DEV.SCK.PIN;
  GPIO_Init(SPI2DEV.SCK.PORT, &GPIO_InitStructure);
  // DIO-Pin is open drain
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin   = SPI2DEV.DIO.PIN;
  GPIO_Init(SPI2DEV.DIO.PORT, &GPIO_InitStructure);

  // SPI-Konfiguration (Half-Duplex)
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;

  // CPOL=1, CPHA=1
  SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;

  SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI2_VORTEILER;

  // LSB-First
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure); 

  // SPI enable
  SPI_Cmd(SPI2, ENABLE); 

  // init Mode speichern
  init_ok=1;
  ret_wert=SUCCESS;

  return(ret_wert);
}


//--------------------------------------------------------------
// sendet ein Byte per SPI2 (im Half-Duplex-Mode per DIO)
// ChipSelect-Signal muss von rufender Funktion gemacht werden
//--------------------------------------------------------------
void UB_SPI2_HD_SendByte(uint8_t wert)
{ 
  // warte bis senden fertig
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

  // byte senden
  SPI_SendData8(SPI2, wert);
}


//--------------------------------------------------------------
// empfängt ein Byte per SPI2 (im Half-Duplex-Mode per DIO)
// ChipSelect-Signal muss von rufender Funktion gemacht werden
// byte_nr : SPI_FIRST_BYTE  = erstes Byte (von mehreren)
//           SPI_LAST_BYTE   = letztes Byte (von mehreren)
//           SPI_OTHER_BYTE  = nicht erstes und nicht letztes Byte
//           SPI_SINGLE_BYTE = ein einzelnes Byte
//--------------------------------------------------------------
uint8_t UB_SPI2_HD_ReceiveByte(SPI2_Byte_t byte_nr)
{
  uint8_t ret_wert=0;

  if((byte_nr==SPI_FIRST_BYTE) || (byte_nr==SPI_SINGLE_BYTE)) {
    // warte bis senden fertig
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    // umschalten auf Receive
    SPI_BiDirectionalLineConfig(SPI2, SPI_Direction_Rx);
  }

  // warte bis empfang fertig
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  // Daten einlesen
  ret_wert=SPI_ReceiveData8(SPI2);

  if((byte_nr==SPI_LAST_BYTE) || (byte_nr==SPI_SINGLE_BYTE)) {
    // zurueckschalten auf Transmit
    SPI_BiDirectionalLineConfig(SPI2, SPI_Direction_Tx);
  }

  return(ret_wert);
}
