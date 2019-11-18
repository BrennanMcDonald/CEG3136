/*--------------------------------------------
File: SegDisp.c
Description:  Segment Display Module
---------------------------------------------*/

#include <stdtypes.h>
#include "mc9s12dg256.h"
#include "SegDisp.h"
#include "Delay_asm.h"

#define LCD_DISP_ROW 2
#define LCD_DISP_COL 16
#define ASCII_SPACE 32

#define ZERO 0x3F
#define ONE  0x06
#define TWO 0x5b
#define THREE 0x4F
#define FOUR 0x6D
#define FIVE  0x66
#define SIX 0x7D
#define SEVEN 0x07
#define EIGHT 0xFF
#define NINE 0x6F

char arr[4]  = {0x00, 0x00, 0x00, 0x00};

/*---------------------------------------------
Function: initDisp
Description: initializes hardware for the 
             7-segment displays.
-----------------------------------------------*/
void initDisp(void) 
{
   // Complete this function
  DDRB =0xFF;
  DDRP = 0x0F;
  clearDisp();

}

/*---------------------------------------------
Function: clearDisp
Description: Clears all displays.
-----------------------------------------------*/
void clearDisp(void) 
{
	// Complete this function
	int i = 0;
      PORTB = 0x00;
   PTP = 0x11;
  
   while(i<4)
   {
    
    arr[i] = 0x00;
    i++;
   } 

}

/*---------------------------------------------
Function: setCharDisplay
Description: Receives an ASCII character (ch)
             and translates
             it to the corresponding code to 
             display on 7-segment display.  Code
             is stored in appropriate element of
             codes for identified display (dispNum).
-----------------------------------------------*/


void setCharDisplay(char ch, byte dispNum) 
{
	// Complete this function

      switch(ch){
  case '0' :
        arr[(int)dispNum]=0x3F;
        break;
  case '1' :
        arr[(int)dispNum]=0x06;
        break;
  case '2' :
        arr[(int)dispNum]=0x5B;
        break;
  case '3' :
        arr[(int)dispNum]=0x4F;
        break;
  case '4' :
        arr[(int)dispNum]=0x66;
        break;
  case '5' :
        arr[(int)dispNum]=0x6D;
        break;
  case '6' :
        arr[(int)dispNum]=0x7D;
        break;
  case '7' :
        arr[(int)dispNum]=0x07;
        break;  
  case '8' :
        arr[(int)dispNum]=0x7F;
        break;
  case '9' :
        arr[(int)dispNum]=0x67;
        break;
  default:
        arr[(int)dispNum]= 0x00;
        break;
        
}
}

/*---------------------------------------------
Function: segDisp
Description: Displays the codes in the code display table 
             (contains four character codes) on the 4 displays 
             for a period of 100 milliseconds by displaying 
             the characters on the displays for 5 millisecond 
             periods.
-----------------------------------------------*/
void segDisp(void) 
{
  int x;
    for(x=0;x<5;x++) {
      PORTB= arr[0];
        PTP=0xE;
        delayMs(5);
        
        PORTB= arr[1];
        PTP=0xD;
        delayMs(5);
        
        PORTB= arr[2];
        PTP=0xB;
        delayMs(5);
        
        PORTB= arr[3];
        PTP=0x7;
        delayMs(5);  
    }
}