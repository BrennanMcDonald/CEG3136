// Example 1a: Turn on every other segment on 7-seg display
#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"

#include "main_asm.h" /* interface to the assembly module */


void main2(void) {
  /* put your own code here */
  PLL_init();        // set system clock frequency to 24 MHz 
  DDRB  = 0xff;       // Port B is output
  DDRJ  = 0xff;       // Port J is output
  DDRP  = 0xff;       // Port P is output
  PTJ = 0x00;         // enable LED
  PTP = 0x00;         // enable all 7-segment displays
  // turn on every other led and segment on 7-seg displays
  PORTB   = 0x55;        

  for(;;) {} /* wait forever */
}
