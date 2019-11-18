/*-------------------------------------------------------------
 * File: armed.c
 * Description: This file contains the Amred module for the
 *              Alarm System Project.
-----------------------------------------------------------------*/

#include "alarmExtern.h"  // Definitions file

// Prototypes of local functions
void systemArmed(void);

// Constants
#define ARMDELAY 15000  // delay for arming and disarming
#define BEEPDELAY 1000

// Armed Module (armed.c)
#define CODEMSG	"Code?"
#define ARMING "*** Arming ***"
#define ARMED	"*** Armed ***"
#define DISARMING	"-- Disarming --"

// Prototypes of local functions
void triggerAlarm(void);
byte checkCode(byte);
byte isCodeValid(int);

/*------------------------
 * Function: enableAlarm
 * Parameters: none
 * Returns: nothing
 * Description:
 *     Gets user to enter a valid alarm code to arm
 *     the alarm system.  Delays 15 seconds (to allow user
 *     to leave; the alarm can be disarmed during this period),
 *     monitors for trigger events (a, b, c, d, e).  When 'a'
 *     is detected, 15 seconds are allowed to enter an alarm code to
 *     disarm the system; otherwise the alarm is triggered. For other
 *     trigger events, the alarm is triggered instantly.  The alarm
 *     system can be turned off after being triggered with an alarm
 *     code.
 *-----------------------*/
void enableAlarm(void)
{
   byte input;  // input from user
   byte codeValid;  // valid code found
   int delayCount;  // Counting 100 ms delays of segDisp
   char ch;

   // Get a valid code to arm the system
   printLCDStr(CODEMSG, 1);
   codeValid = FALSE;
   while(!codeValid) 
   {
     input = readKey();
     codeValid = checkCode(input);
   }
   printLCDStr(ARMING,1);
   
   // Delay 10 seconds using segDisp 100 ms delays
   codeValid = FALSE;
   delayCount = 100;  //10sec delay
   setCharDisplay('1',2); 
   setCharDisplay('0',3);
   while(delayCount)  // loop if delayCount not zero
   {
      // Update Display
      segDisp();   // 100 ms display
      delayCount--;
      if(delayCount%10 == 0)
      {
         ch = 0x30+delayCount/10;
         setCharDisplay(' ',2); 
         setCharDisplay(ch,3);
      }
      // Check input
      input = pollReadKey();  // check if alarm code entered to disarm
      if(isdigit(input) || input == '#') 
      {
         codeValid = checkCode(input);
         if(codeValid) delayCount = 0;  // break out of loop
      }
   }
   clearDisp();
   segDisp();
   if(!codeValid) systemArmed();
}

void systemArmed() 
{ 
   byte input;  // input from user
   byte codeValid = FALSE;  // valid code found
   int delayCount;  // Counting 100 ms delays of segDisp
   char ch;

   // Loop to monitor trigger events and alarm code to disable
   // codeValid is TRUE if valid alarm code entered
   if(!codeValid) printLCDStr(ARMED,1);   
   while(!codeValid)
   {
       input = pollReadKey();
       if(isdigit(input) || input == '#') codeValid = checkCode(input);
       else if(getSwStatus() & 0b00000001) // Front door opened - delay before alarm
       {
           printLCDStr(DISARMING,1);
              // Delay 10 seconds
           codeValid = FALSE;
           delayCount = 100;  //10 sec delay
           setCharDisplay('1',2); 
           setCharDisplay('0',3);
           while(!codeValid) 
	         {
              // Update Display
              segDisp();
              delayCount--;
              if(delayCount%10 == 0)
              {
                 ch = 0x30+delayCount/10;
                 setCharDisplay(' ',2); 
                 setCharDisplay(ch,3);
              }
	            // Check Input
              if(!delayCount)  // 0 means delay is done
              { 
                 clearDisp();
                 triggerAlarm();
                 codeValid = TRUE;
              }
              else
              {
                 input = pollReadKey();  // check if alarm code entered to disarm
                 if(isdigit(input) || input == '#') 
                     codeValid = checkCode(input); 
              }              
	         }
	         clearDisp();
	         segDisp();	         
       }
       else if((getSwStatus() & 0b11111110)) // other door/window opened
       {
           triggerAlarm();
           codeValid = TRUE;
       }
       // ignore all other input
   }
}


/*----------------------------
 * Functions: checkCode
 * Parameters: input - input character
 * Returns: TRUE - alarm code detected
 *          FALSE - alarm code not detected
 * Descriptions: Creates alarm code using digits entered until
 *               4 digits are seen. After 4th digit, see if
 *               alarm code is valid using isCodeValid().
 *----------------------------*/

byte checkCode(byte input)
{
   static int mult = 1000; // current multiplier of digit
   static int alarmCode = 0;   // alarm code value
   byte retval = FALSE;

   if(isdigit(input))
   {
      alarmCode = alarmCode + (input-ASCII_CONV_NUM)*mult;
      mult = mult/10;
      if(mult == 0) 
      {
         retval = isCodeValid(alarmCode);
         alarmCode = 0;
         mult = 1000;
      }
   }
   else
   {
      alarmCode = 0;
      mult = 1000;
   }
   
   return(retval);
}
/*----------------------------
 * Functions: isCodeValid
 * Parameters: alarmCode - integer alarmCode
 * Returns: TRUE - alarm code valid
 *          FALSE - alarm code not valid
 * Descriptions: Checks to see if alarm code is in the
 *               alarmCodes array.
 *----------------------------*/
byte isCodeValid(int alarmCode)
{
   int *ptr;  // pointer to alarmCodes
   byte cnt = NUMCODES;
   byte retval = FALSE;
   ptr = alarmCodes;
   do
   {
      if(*ptr++ == alarmCode)
      {
         retval = TRUE;
         break;
      }
      cnt--;
   } while(cnt != 0);
   return(retval);
}

/*----------------------------
 * Functions: triggerAlarm
 * Parameters: none
 * Returns: nothing
 * Descriptions: Repeatedly sends a bel character to the
 *               terminal until a valid alarm code is entered.
 *----------------------------*/

void triggerAlarm()
{
   byte done = FALSE; // wait code is given
   volatile int doneInput;    // Wait until delay done
   byte input;
   byte dispA = FALSE; // Display Alarm
   while(!done)
   {
       if(!dispA) 
       {
           setCharDisplay('A',0); 
           dispA = TRUE;
       }
       else
       {
           setCharDisplay(' ',0); 
           dispA = FALSE;
       } 
       doneInput = 10;
       while(doneInput) 
       {
          segDisp();  // displays characters - uses up 100ms
          input = pollReadKey();  // check if code entered to disarm
          if(isdigit(input) || input == '#') done = checkCode(input);
          doneInput--;
      }
   }
   clearDisp();
   segDisp();
}
