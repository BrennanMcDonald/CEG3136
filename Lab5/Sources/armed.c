/*-------------------------------------------------------------
 * File: armed.c
 * Description: This file contains the Amred module for the
 *              Alarm System Project.
-----------------------------------------------------------------*/

#include "alarmExtern.h"  // Definitions file
#include "stdio.h"

// Constants
#define ARMDELAY 10000  // delay for arming and disarming = 10 seconds
#define BEEPDELAY 1000

// Armed Module (armed.c)
#define CODEMSG	"Code?"
#define ARMING "*** Arming ***"
#define ARMED	"*** Armed ***"
#define DISARMING	"-- Disarming --"

// Prototypes of local functions
void systemArmed(void);
void triggerAlarm(void);
byte checkCode(byte);
byte isCodeValid(int);
void displayNum(int);

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
   volatile int delayCount;  // Counting 10 sec delays of segDisp

   // Get a valid code to arm the system
   printLCDStr(CODEMSG, 1);
   codeValid = FALSE;
   while(!codeValid) 
   {
     input = readKey();
     codeValid = checkCode(input);
   }
   printLCDStr(ARMING,1);
   // Stop displaying temperature
   displayTempFlag = FALSE;
   clearDisp();
   // Delay 10 seconds using segDisp 100 ms delays
   codeValid = FALSE;
   setCounter(&delayCount); // enable counter
   delayCount = ARMDELAY;  //10sec delay
   while(delayCount>0)  // loop if delayCount not zero
   {
      // Update Display
      if(delayCount%1000 == 0) // every 1000 ms (1 sec)
         displayNum(delayCount/1000);
      // Check input
      input = pollReadKey();  // check if alarm code entered to disarm adds 1ms delay
      if(isdigit(input) || input == '#') 
      {
         codeValid = checkCode(input);
         if(codeValid) delayCount = 0;  // break out of loop
      }
   }
   setCounter(NULL);  // Disable counter
   clearDisp();
   // Start displaying temperature
   displayTempFlag = TRUE;
   if(!codeValid) systemArmed();
}

void systemArmed() 
{ 
   byte input;  // input from user
   byte codeValid = FALSE;  // valid code found
   volatile int delayCount;  // Counting 100 ms delays of segDisp

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
           // Stop Displaying temperature
           displayTempFlag = FALSE;
           clearDisp();
              // Delay 10 seconds
           codeValid = FALSE;
           setCounter(&delayCount);   // Enable counter
           delayCount = ARMDELAY;  //10 sec delay
           while(!codeValid) 
	         {
              // Update Display
              if(delayCount%1000 == 0)                 
                 displayNum(delayCount/1000);
	            // Check Input
              if(delayCount<=0)  // 0 means delay is done
              { 
                 clearDisp();
	               displayTempFlag = TRUE;
                 triggerAlarm();   // Note counter also disabled by triggerAlarm
                 codeValid = TRUE;
              }
              else
              {
                 input = pollReadKey();  // check if alarm code entered to disarm
                 if(isdigit(input) || input == '#') 
                     codeValid = checkCode(input); 
              }              
	         }
	         setCounter(NULL);   // Disable Counter
	         clearDisp();
	         // Start displaying temperature
	         displayTempFlag = TRUE;
       }
       else if((getSwStatus() & 0b11111110)) // other door/window opened
       {
           triggerAlarm();
           codeValid = TRUE;
       }
       // ignore all other input
       //Check temperature and sound alarm if too high
       if(getTemp() >= HIGH_TEMP) 
       {
           triggerAlarm();
           codeValid = TRUE;
       }
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
   byte input;
   turnOnSiren();
   while(!done)
   {
      input = pollReadKey();  // check if code entered to disarm; 1ms delay
      if(isdigit(input) || input == '#') 
             done = checkCode(input);
   }
   turnOffSiren();
}

/*-------------------------------------------
Function: displayNum
Paramter: num - number to display, must be < 99
Description: Displays a 2 digit number on 7-segment displays 2 and 3.
---------------------------------------------*/

void displayNum(int num) 
{
   char dig1, dig2, ch;
   if(num > 99) return; // display nothing if number not valid
   dig2 = num%10;   // units
   dig1 = num/10;   // tens
   ch = 0x30+dig1;
   if(dig1 == 0) setCharDisplay(' ',2);
   else setCharDisplay(ch,2);
   ch = 0x30+dig2; 
   setCharDisplay(ch,3);  
}
