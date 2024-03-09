//--------------------------------------------------------------
// File     : stm32_ub_tm1638.c
//
// BASED ON : STM32_UB_SPI2_HD
//            see: https://mikrocontroller.bplaced.net/wordpress/?page_id=464
//
// CPU      : STM32F0
// Funktion : Digital-IO Platine (Chip=TM1638)
//            OUT = 8x rote LED
//                  8x 7Segment
//            IN  = 8x Button
//
// Hinweis  : Settings :
//            Half-Duplex, FRQ-Max = 1MHz
//            SPI2 [CLK=PB13, DIO=PB15]
//            STB = PB12 (Chip-Select)
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_tm1638.h"
#include "stm32_ub_spi2_hd.h"


//--------------------------------------------------------------
// interne Funktionen
//-------------------------------------------------------------- 
void P_TM1638_initIO(void);
void P_TM1638_CS(BitAction wert);
void P_TM1638_initSeq(void);
void P_TM1638_SendCMD(uint8_t cmd);
void P_TM1638_WriteRAM(uint8_t adr, uint8_t wert);
uint8_t P_TM1638_ReadKEY(void);
void P_TM1638_Delay(volatile uint32_t nCount);
 


//--------------------------------------------------------------
// 7Segment Font (digits 0-9, A-F, OFF)
//--------------------------------------------------------------
const uint8_t HEX_7SEG [] = {
  0x3F,	// 0
  0x06,	// 1
  0x5B,	// 2
  0x4F,	// 3
  0x66,	// 4
  0x6D,	// 5
  0x7D,	// 6
  0x07,	// 7
  0x7F,	// 8
  0x6F,	// 9
  0x77,	// A
  0x7C,	// B
  0x39,	// C
  0x5E, // D
  0x79,	// E
  0x71,	// F
  0x00  // Off
};

// get segments from digit     : [0...15, 16..31 with decimal point, 32=OFF]
uint8_t digit2segment( uint8_t digit )
{
	uint8_t segments = 0;
	if ( digit < 16 )
		segments = HEX_7SEG[ digit ];
	else if ( digit < 32 )
		segments |= 0x80; //add point
	else
		segments = HEX_7SEG[ 16 ]; //off
	
	return segments;
}


//--------------------------------------------------------------
// Initialisierung vom TM1638
// Return_wert :
//  -> ERROR   , wenn Initialisierung fehlgeschlagen
//  -> SUCCESS , wenn Initialisierung ok war 
//--------------------------------------------------------------
ErrorStatus UB_TM1638_Init(void)
{
  ErrorStatus ret_wert=ERROR;
  // Init der Chip-Select-Leitung
  P_TM1638_initIO();
  // ChipSelect auf Hi
  P_TM1638_CS(Bit_SET);
  //-------------------------------
  // init vom SPI-2 (Half-Duplex)
  // im Mode-3, LSB-First
  //-------------------------------
  ret_wert=UB_SPI2_HD_Init();
  // Auswertung
  if(ret_wert==SUCCESS)
  {
    // init Sequenz
    P_TM1638_initSeq();
  }  

  return(ret_wert);
}


//--------------------------------------------------------------
// schaltet das Display komplett AUS
// (alle 7Segment und alle LEDs)
//--------------------------------------------------------------
void UB_TM1638_Display_Off(void)
{
  // Display OFF
  P_TM1638_SendCMD(TM1638_CMD_04_OFF);  
}


//--------------------------------------------------------------
// schaltet das Display EIN
// (alle 7Segment und alle LEDs)
// pwm : [0...7] = Helligkeit vom Display [0=minimum]
//--------------------------------------------------------------
void UB_TM1638_Display_On(uint8_t pwm)
{
  if(pwm>7) pwm=7;

  // Display ON
  P_TM1638_SendCMD(TM1638_CMD_04_ON | pwm);
}


//--------------------------------------------------------------
// schaltet eine LED ein
// led_nr : [0...7]
//--------------------------------------------------------------
void UB_TM1638_LED_On(uint8_t led_nr)
{
  uint8_t adr,wert;

  if(led_nr>7) led_nr=7;

  adr=(led_nr<<1)+1; // LED0=1, LED1=3, LED2=5, LED7=15
  wert=1; // farbe = rot

  P_TM1638_WriteRAM(adr,wert);
}


//--------------------------------------------------------------
// schaltet eine LED aus
// led_nr : [0...7]
//--------------------------------------------------------------
void UB_TM1638_LED_Off(uint8_t led_nr)
{
  uint8_t adr,wert;

  if(led_nr>7) led_nr=7;

  adr=(led_nr<<1)+1; // LED0=1, LED1=3, LED2=5, LED7=15
  wert=0; // farbe = aus

  P_TM1638_WriteRAM(adr,wert);
}


//--------------------------------------------------------------
// gibt einen 8bit Wert an den LEDs aus
// wert : [0...255]
//--------------------------------------------------------------
void UB_TM1638_LED_Value(uint8_t wert)
{
  if((wert&0x01)==0) UB_TM1638_LED_Off(0); else UB_TM1638_LED_On(0);
  if((wert&0x02)==0) UB_TM1638_LED_Off(1); else UB_TM1638_LED_On(1);
  if((wert&0x04)==0) UB_TM1638_LED_Off(2); else UB_TM1638_LED_On(2);
  if((wert&0x08)==0) UB_TM1638_LED_Off(3); else UB_TM1638_LED_On(3);
  if((wert&0x10)==0) UB_TM1638_LED_Off(4); else UB_TM1638_LED_On(4);
  if((wert&0x20)==0) UB_TM1638_LED_Off(5); else UB_TM1638_LED_On(5);
  if((wert&0x40)==0) UB_TM1638_LED_Off(6); else UB_TM1638_LED_On(6);
  if((wert&0x80)==0) UB_TM1638_LED_Off(7); else UB_TM1638_LED_On(7);
}


//--------------------------------------------------------------
// gibt eine einzelne HEX-Ziffer an einer 7Segment aus
// (oder schaltet eine 7Segment dunkel)
// segment_nr : [0...7]
// ziffer     : [0...15, 16..31 with decimal point, 32=OFF]
//--------------------------------------------------------------
void UB_TM1638_7Seg_Ziffer(uint8_t segment_nr, uint8_t ziffer)
{
  uint8_t adr,wert;

  if ( segment_nr>7 )
		segment_nr=7;

  adr=(segment_nr<<1); // Seg0=0, Seg1=2, Seg2=4, Seg7=14
  wert = digit2segment(ziffer);

  P_TM1638_WriteRAM(adr,wert);
}


//--------------------------------------------------------------
// gibt eine Zahl als Dezimalwert
// an der 7Segment-Anzeige aus
//--------------------------------------------------------------
void UB_TM1638_7Seg_Dec(uint32_t wert)
{
  uint8_t n;

  if(wert>99999999) wert=99999999;

  for(n=0;n<8;n++)
  {
    UB_TM1638_7Seg_Ziffer(7-n,wert % 10);
    wert /= 10;
  }
}


//--------------------------------------------------------------
// gibt eine Zahl als Hexwert
// an der 7Segment-Anzeige aus
//--------------------------------------------------------------
void UB_TM1638_7Seg_Hex(uint32_t wert)
{
  uint8_t n;

  for(n=0;n<8;n++) {
    UB_TM1638_7Seg_Ziffer(7-n,(wert & 0x0F));
    wert >>= 4;
  }
}


//--------------------------------------------------------------
// gibt den Status der 8 Buttons
// als 8bit Wert zurück
// ret_wert : [0...255] 0=kein Button betaetigt
//--------------------------------------------------------------
uint8_t UB_MT1638_Get_Key(void)
{
  uint8_t ret_wert=0;

  ret_wert=P_TM1638_ReadKEY();

  return(ret_wert);
}


//--------------------------------------------------------------
// interne Funktion
// Init der ChipSelect-Leitung
//--------------------------------------------------------------
void P_TM1638_initIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // Init der Chip-Select-Leitung
  RCC_AHBPeriphClockCmd( TM1638_CS_GPIO_CLK, ENABLE );

  GPIO_InitStructure.GPIO_Pin = TM1638_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TM1638_CS_GPIO_PORT, &GPIO_InitStructure);
}


//--------------------------------------------------------------
// interne Funktion
// Pegel von ChipSelect einstellen
//--------------------------------------------------------------
void P_TM1638_CS( BitAction wert ) {
  if(wert==Bit_RESET) {
    TM1638_CS_GPIO_PORT->BRR = TM1638_CS_PIN;
  }
  else {
    TM1638_CS_GPIO_PORT->BSRR = TM1638_CS_PIN;
  }
}


//--------------------------------------------------------------
// interne Funktion
// init Sequenz
//--------------------------------------------------------------
void P_TM1638_initSeq(void)
{
  uint8_t n;

  // kleine Pause
  P_TM1638_Delay(TM1638_INIT_DELAY);
  // init Sequenz
  P_TM1638_SendCMD(TM1638_CMD_02_FIX);
  // RAM loeschen
  for(n=0;n<=TM1638_MAX_RAM_ADR;n++) {
    P_TM1638_WriteRAM(n,0x00);
  }
  // Display OFF
  P_TM1638_SendCMD(TM1638_CMD_04_OFF);
}


//--------------------------------------------------------------
// interne Funktion
// sendet ein Kommando an den TM1638
//--------------------------------------------------------------
void P_TM1638_SendCMD(uint8_t cmd)
{
  // ChipSelect auf Lo
  P_TM1638_CS(Bit_RESET); 

  // Kommando senden
  UB_SPI2_HD_SendByte(cmd);

  P_TM1638_Delay(TM1638_DELAY_A); // wichtig

  // ChipSelect auf Hi
  P_TM1638_CS(Bit_SET); 
}


//--------------------------------------------------------------
// interne Funktion
// beschreibt eine RAM-Adresse vom TM1638
//--------------------------------------------------------------
void P_TM1638_WriteRAM(uint8_t adr, uint8_t wert)
{
  // max adresse pruefen
  if(adr>TM1638_MAX_RAM_ADR) return;

  // ChipSelect auf Lo
  P_TM1638_CS(Bit_RESET); 

  // Adresse senden
  UB_SPI2_HD_SendByte(TM1638_CMD_03 | adr);

  // Wert senden
  UB_SPI2_HD_SendByte(wert);

  P_TM1638_Delay(TM1638_DELAY_B); // wichtig

  // ChipSelect auf Hi
  P_TM1638_CS(Bit_SET);
}


//--------------------------------------------------------------
// interne Funktion
// auslesen der Tasten vom TM1638
//--------------------------------------------------------------
uint8_t P_TM1638_ReadKEY(void)
{
  uint8_t ret_wert=0;
  uint8_t wert;

  // ChipSelect auf Lo
  P_TM1638_CS(Bit_RESET);

  // Keyscan senden
  UB_SPI2_HD_SendByte(TM1638_CMD_02_KEY);

  P_TM1638_Delay(TM1638_DELAY_C); // wichtig

  // 4Byte Key-Daten auslesen
  wert=UB_SPI2_HD_ReceiveByte(SPI_FIRST_BYTE); // erstes Byte
  ret_wert|=wert;
  wert=UB_SPI2_HD_ReceiveByte(SPI_OTHER_BYTE); // mittleres Byte
  ret_wert|=(wert<<1);
  wert=UB_SPI2_HD_ReceiveByte(SPI_OTHER_BYTE); // mittleres Byte
  ret_wert|=(wert<<2);
  wert=UB_SPI2_HD_ReceiveByte(SPI_LAST_BYTE);  // letztes Byte
  ret_wert|=(wert<<3);

  P_TM1638_Delay(TM1638_DELAY_D);

  // ChipSelect auf Hi
  P_TM1638_CS(Bit_SET);

  // Wichtig : Adresse wieder auf 0 setzen
  P_TM1638_SendCMD(TM1638_CMD_03);

  return(ret_wert);
}


//--------------------------------------------------------------
// interne Funktion
// kleine Pause (ohne Timer)
//--------------------------------------------------------------
void P_TM1638_Delay(volatile uint32_t nCount)
{
  while(nCount--)
  {
  }
}
