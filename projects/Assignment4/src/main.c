/******************************************************************************
 * File           : Main program
 * Author         : VNP02
 *****************************************************************************/
//#include "stm32f0xx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "usart.h"

bool assert_strequal( int test, char* b, char* expected, char* message );


//comment the following line to test your fixed point solution instead of the given example
//#define RUN_FLOAT 1


char      buffer[20];  //for printing


#ifdef RUN_FLOAT

typedef   float  fixed;     //note that still one testcase fails because float is not accurate enough!
//typedef   double  fixed;  //more precision floatint point type passes all tests

#define float_to_fixed(a)   (a)   //float does not need conversion

fixed calc_average( fixed* array, int8_t lenght) {
  int8_t hour;
  fixed sum = 0;
  for ( hour=0; hour<lenght; hour++) {
    sum += *array++;
  }
  return sum / lenght;   //float does not need rounding
}

void to_string( fixed number )
{
  sprintf(buffer, "%.1f", number);  //printing takes care of rounding
}

#else
	
//your fixed point arithmetic code goes here

// choose the correct type for fixed
typedef   uint8_t  fixed;	/* uint8_t with point in the center, this gives a minimum resolution of 0.0625, and it's unsigned because we don't go lower than 0 */

// make the correct conversion macro
#define float_to_fixed(a)   ((uint32_t)(a * (1<<4)))    //change this /* 4 because we use a 4:4 system, change this to a define */
#define int_to_fixed(a)			(a<<4)
void to_string( fixed number );

// implement this code yourself
fixed calc_average( fixed* array, int8_t lenght) {
	// your code goes here
	uint16_t sum = 0;
	uint8_t index = 0;
	
	for (; index < lenght; index++)
	{
		sum += array[index];
	}
	sum = (((uint32_t)sum<<4) / int_to_fixed(lenght)) + 1;
	
	return sum; 
}

// implement this code yourself
void to_string( fixed number ) {
	sprintf(buffer, "%d.%1d",
	        number >> 4,  //compute the integer part /* 4 because we use a 4.4 system, change this to a define */
			    ((uint32_t)(number & 15) * 10000 + 16 / 2) / 16001); //compute the fractional part /* (num * 10^4 + 2^4 / 2) / 16001 (no clue why this num, got it by solfing for .5) */
}

#endif // RUN_FLOAT

#define NROFTESTCASES 12
#define MAXGRADES     30

struct testcase
{
	  uint8_t aantalgetallen;
	  float   invoer[ MAXGRADES ];
	  char*   verwacht;
  	char*   melding;
};



struct testcase testcases[ NROFTESTCASES ] = {
    //nrvalues       input                  average          test
/*1*/  { 2, { 1.0,  1.0 },                   "1.0",          "simple" }, 
/*2*/  { 2, {10.0, 10.0 },                   "10.0",         "simple" },
/*3*/  { 2, { 1.0, 10.0 },                   "5.5",          "simple" },
/*4*/  { 5, { 6.0,  7.0, 8.0, 9.0, 10.0 },   "8.0",          "simple" },
/*5*/  { 3, { 5.5,  7.0, 8.0 },              "6.8"/*6.833*/, "rounding" },
/*6*/  { 3, { 5.5,  5.6, 5.6 },              "5.6"/*5,566*/, "rounding" },
/*7*/  { 3, { 5.5,  5.5, 5.6 },              "5.5"/*5,533*/, "rounding" },
/*8*/  { 5, { 1.0,  4.5, 5.6, 9, 9 },        "5.8"/*5.820*/, "rounding" },
/*9*/  { 4, { 6.6,  7.1, 6.6, 7.1 },         "6.9"/*6.850*/, "expected rounding error" },
/*10*/ { 4, { 6.6,  7.1, 6.9, 7.9 },         "7.1"/*7,125*/, "rounding" },
/*11*/ { 13,{10.0, 10.0, 10.0, 10.0, 10.0, 
	           10.0, 10.0, 10.0, 10.0, 10.0, 
             10.0, 10.0, 10.0 },             "10.0",         "overflow" },
/*12*/ { 27,{10.0, 10.0, 10.0, 10.0, 10.0, 
	           10.0, 10.0, 10.0, 10.0, 10.0,
             10.0, 10.0, 10.0, 10.0, 10.0, 
	           10.0, 10.0, 10.0, 10.0, 10.0,
             10.0, 10.0, 10.0, 10.0, 10.0, 
             10.0, 10.0 },                   "10.0",         "overflow" }
};

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{
  uint8_t test, j;
  uint8_t passed = 0;
  fixed   avg;
  fixed   grades[ MAXGRADES ];

  USART_init();
  USART_clearscreen();
#ifdef RUN_FLOAT
  USART_putstr("This is testcode for floating point arithmetic\n");
#else
  USART_putstr("This is testcode for fixed point arithmetic\n");
#endif
  USART_putstr("The output of the testcases is\n\n");

  for ( test=0; test<NROFTESTCASES; test++)
  {
 	  //do each test
	  struct testcase thistest = testcases[test];

	  //fill values array
	  for (j=0; j<thistest.aantalgetallen; j++)
	  {
      grades[j] = float_to_fixed(thistest.invoer[j]);
	  }

    USART_putstr( "TEST: " );
	  USART_putint( test+1 );
    USART_putstr( " " );

    avg = calc_average( grades, thistest.aantalgetallen );
    to_string( avg );
    if ( assert_strequal( test, buffer, thistest.verwacht, thistest.melding ) )
	  {
		  passed++;
	  }
  }

  USART_putstr( "\nYou passed " );
  USART_putint( passed );
  USART_putstr( " of the tests\n" );
  USART_putstr("Ready");

  //ready
  while(1);
}


bool assert_strequal( int test, char* b, char* expected, char* message )
{
	bool pass;
	if ( strncmp( b, expected, 10 ) != 0 )   //check the first 10 digits for equality
	{
		USART_putstr( " FAIL: " );
		USART_putstr( b );
		USART_putstr( " != " );
		USART_putstr( expected );
		USART_putstr( " " );
		USART_putstr( message );
		pass = false;
	}
	else
	{
		USART_putstr( " PASS: " );
		USART_putstr( b );
		USART_putstr( " = " );
		USART_putstr( expected );
		pass = true;
	}
  USART_putstr( "\n" );
	return pass;
}
