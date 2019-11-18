/*------------------------------------------------------
File: Delay.c
Description:  Delay module
              Uses Timer Channel 0
-------------------------------------------------------*/

#include "mc9s12dg256.h"
#include <stddef.h>
#include "Delay.h"
// Some definitions
#define ONETENTH_MS 75	// number for timer to increment in 0.1 ms (75*1 1/3 micro-sec)
// Global Variables
static volatile int timeCounter; // Module global variable for blocking delay
static volatile int *countPtr = NULL;  // Pointer to counter in other module 
static volatile int isrCounter; 

/*----------------------------------------------------
Function: initDelay
Description: initilises the timer channel 1 for counting
             milliseconds - see tc0_isr.
------------------------------------------------------*/
void initDelay(void) 
{
	TIOS_IOS0 = 1; // set TC0 to output-compare
	TIE_C0I = 0x01; // enable interrupt channel 0
	TC0 = TCNT + ONETENTH_MS; // Set TC0 for one ms delay
	isrCounter = 10;  // to count 1 ms in the ISR
}

/*----------------------------------------------------
Function: setCounter
Description: Sets the address of external counter.
             Should be called with null (0) to disable the
             external counter. The contents of the
             counter is decremented every millisecond.
------------------------------------------------------*/
void setCounter(volatile int *extCounterPtr) 
{     
    countPtr = extCounterPtr;
}

/*----------------------------------------------------
Function: delayms(num)
Description: Delays 1 millisecond (blocks until delay
             is over).
------------------------------------------------------*/
void delayms(int num) 
{
    while(num != 0) 
    {
       timeCounter = 1;
       while(timeCounter) /*wait*/;
       num--; 
    }
}

/*----------------------------------------------------
Interrupt: tc0_isr
Description: This service routine increments the counter
             variable timeCounter every 1ms. It resets
             the timer channel.
-------------------------------------------------------*/
void interrupt VectorNumber_Vtimch0 tco_isr(void) 
{    
    isrCounter--;
    if(isrCounter == 0)
    {
       isrCounter = 10;
       timeCounter--;
       if(countPtr != NULL) (*countPtr)--;
    }
    TC0 = TC0+ONETENTH_MS; // reading TC0 resets interrupt      
}