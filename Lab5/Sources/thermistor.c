/*--------------------------------------------
File: thermistor.c
Description:  Thermistor Module
              Uses Timer Channel 6
---------------------------------------------*/

#include "mc9s12dg256.h"
#include "thermistor.h"
#include "delay.h"

#define ATD_TIMEOUT 7500  // For 10 ms delay (1 1/3 microSec/tick). 

static int hold;

void initThermistor(void) {
  // Sets up the ATD
  ATD0CTL2 = 0xC2; // ADC On, Fast clear on, ISR On
  delayms(20);
  ATD0CTL3 = 0x08; // 1 AD conversion/sequence
  ATD0CTL4 = 0x77; // 10bit, 16 AD clocks/conversion, clock 0.50
  ATD0CTL5 = 0x85; // start conversion pin 05
  
  // Sets up timer channel to generate interrupts
  // Assume that timer is enabled elsewhere with 1 1/3 microsec ticks
  // for controlling displays
	TIOS |= 0b00001000; // Set ouput compare for TC3
	TIE |= 0b00001000; // Enable interrupt on TC3
	
	TC3 = TCNT + ATD_TIMEOUT; // enables timeout on channel 3 
}

int getTemp(void) {
  return (hold / 2.048) * 10;
}

/*-------------------------------------------------
Interrupt: atdd_isr
Description: Thermistor interrupt service routine to 
             read results upon conversion.
---------------------------------------------------*/
void interrupt VectorNumber_Vatd0 atdread_isr(void) {
  hold = ATD0DR0;
}

/*-------------------------------------------------
Interrupt: atdt_isr
Description: Thermistor interrupt service routine to
             sample results every 100ms.
---------------------------------------------------*/
void interrupt VectorNumber_Vtimch3 atdtimer_isr(void)
{
  static byte count = 10;  // preserve between invocations
  
  
  if (count > 0) {
    count--;
  } else {
    ATD0CTL5 = 0x85; // start conversion pin 05
    count = 10;  // flip the count
  }
  
	// Set up next interrupt (also clears the interrupt)
	TC3 = TC3 + ATD_TIMEOUT;
}
