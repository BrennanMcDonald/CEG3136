/*------------------------------------------------
File: siren.c

Description: The Siren module.
-------------------------------------------------*/
#include "mc9s12dg256.h"
 
//Definitions
#define HIGH_MS 300   // 300 * 1 1/3 micro-sec =  0.400 ms 
#define LOW_MS 600   // 600 * 1 1/3 micro-sec = 0.800 ms

// Prototypes of local functions
void interrupt VectorNumber_Vtimch5 sirenISR (void);


void initSiren()
{
   TIOS |= 0b00100000;  // Set TC5 to output-compare
}

#define HIGH 1
#define LOW 0
int levelTC5;  // level on TC5
void turnOnSiren()
{
   TCTL1 |= 0b00001100; // Sets high on pin 5 at output-compare event 
   CFORC = 0b00100000; // Force an event on TC5 (i.e high on pin 5)
   levelTC5 = HIGH;
   TCTL1 &= 0b11110111; // Set to toggle
   TC5 = TCNT + HIGH_MS;
   TIE |= 0b00100000;  // Enable Interrupt.
}

void turnOffSiren()
{
   TIE &= 0b11011111;  // Disable Interrupt.
   TCTL1 |= 0b00001000; 
   TCTL1 &= 0b11111011; // Sets low on pin 5 at output-compare event 
   CFORC = 0b00100000; // Force an event on TC5 (i.e low on pin 5)
}

void interrupt VectorNumber_Vtimch5 sirenISR ()
{
   if(levelTC5 == HIGH)
   {
      TC5 += LOW_MS;
      levelTC5 = LOW;
   }
   else
   {
      TC5 += HIGH_MS;
      levelTC5 = HIGH;
   }
}



