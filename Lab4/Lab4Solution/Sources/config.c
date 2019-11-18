/*-------------------------------------------------------------
 * File:  config.c
 * Description: This file contains the Configuration module for the 
 *              Alarm System Project project.
-----------------------------------------------------------------*/
#include "alarmExtern.h"  // Definitions file

// Some definitions
#define MSTCDMSG "Master code?"
#define CONFIGMSG "a:mstr 1-4:other"
#define CERRMSG "Bad entry"
#define GET_CODE_MSG "Code or 'd'"
#define ERR_MST_MSG "Cannot disable"

// Prototypes of local functions
byte enterMstCode(void);
void setcode(byte);
int writeToEE(int, int);
int initEE(int, int);

/*---------------------
 * Function: configCodes
 * Parameters: none
 * Returns: nothing
 * Description: Gets user to select alarm code to update/disable. Call
 *              setcode to update the alarm code.
 * ---------------------*/
void configCodes()
{
   byte ix;  // index into array
   byte input; // input from user.
   byte flag;

   if(enterMstCode())
     do
     {
        printLCDStr(CONFIGMSG,1);
        input = readKey();
        flag = TRUE;
        if(input == 'a') setcode(0);
        else if( input>='1' && input <= '4')
        {
          ix = input-ASCII_CONV_NUM;
          setcode(ix);
        }
        else 
        {
           printLCDStr(CERRMSG,1);
           delayms(1000); // one second delay
           flag = FALSE;
        }
     } while(!flag);
}

/*--------------------------------
 * Function: enterMstCode
 * Parameters: none
 * Returns: TRUE - valid code entered, FALSE otherwise.
 * Description: Prompts user for the 4 digit master alarm code.
 *-------------------------------*/
byte enterMstCode(void)
{
   byte retval = FALSE;
   byte i;
   byte input;
   int alarmCode = 0;
   int mult = 1000;
   
   printLCDStr(MSTCDMSG,1);
   for(i=0 ; i<4 ; i++)
   {
      input = readKey();
      if(!isdigit(input)) break;
      else
      {
        alarmCode = alarmCode + mult*(input-ASCII_CONV_NUM);
        mult = mult/10;
        if(mult == 0)
        {
          if(alarmCode == alarmCodes[0]) retval = TRUE;
        }
      }
   }
   return(retval);
}

/*--------------------------------
 * Function: setcode
 * Parameters
 *         ix - index of alarm code to update
 * Description: Prompts user for a 4 digit alarm code to
 *              update the alarm code at index ix. If 'd'
 *              is entered the alarm code is disabled.  It
 *              is not allowed to diable the master
 *              alarm code.
 *-------------------------------*/
void setcode(byte ix)
{
   byte flag = TRUE;
   byte i;
   byte input;
   int digit;
   int alarmCode=0;
   int mult=1000; // multiplier

   do
   {
       printLCDStr(GET_CODE_MSG,1);
       for(i=0 ; i< 4 ; i++)
       {
          input = readKey();
          if(input == 'd') 
          {
             if(ix == 0) 
             {
                printLCDStr(ERR_MST_MSG,1);
                delayms(1000); // delay one second
                break;
             }
             else
             {
                alarmCode = 0xffff;
                flag = FALSE;
                break;
             }
          }
          else if(isdigit(input))
          {
               digit = input - ASCII_CONV_NUM;
               alarmCode = alarmCode + digit * mult;
               mult = mult/10;
               if(mult == 0) flag = FALSE;
          }
          else
          {
              printLCDStr(CERRMSG,1);
              delayms(1000); // delay one second
              break;
          }
       }
   } while(flag);
   if(writeToEE(ix, alarmCode)) /* do nothing */;
}

/*------------------------------------
 * Function: initCodes
 * Description: If the alarm codes are not
 *              initialised (i.e. matercode is
 *              0xFFFF), initialise codes
 *              (that is, set master code
 *               to 0x0000).
 * --------------------------------*/
void initCodes()
{
    if(alarmCodes[0] == 0xFFFF)  // Assume erased
    {
      if(initEE(0,0x0000)) /*do nothing*/;  // initialises other word writes on success
    }
}

/*--------------------------------
 * Function: initEE
 * Parameters
 *         ix - index of alarm code to update
 *         code - code to store 
 * Description: Stores and integer alarm code to alarmcode
 *              array at index ix. Assume that the array
 *              is in EEPROM. Used for first write to the
 *              EEPROM.
 *-------------------------------*/
// Defines for use with controlling the EEPROM
#define ACCERR 0x10
#define PVIOL 0x20
#define CCIF 0x40
#define CBEIF 0x80
#define SECTOR_MODIFY 0x60
#define PROG 0x20

int initEE(int ix, int code)
{
   int retVal = TRUE;  // assume that write is successful
   int *eepromAddr = &alarmCodes[ix];
   
   ESTAT = ACCERR | PVIOL; // Clear error flags
   if(ESTAT & CBEIF)  // checks that command buffer is empty
   {
      *eepromAddr = code;    // Write data word aligned address
      ECMD = PROG;              // Write program command
      ESTAT = CBEIF;            // Write 1 to CBEIF to lauch command
      if(ESTAT & (ACCERR|PVIOL) != 0) retVal = FALSE; // Flag the error
      else while(!(ESTAT & CCIF)) ;  // wait until command complete      
   } 
   else retVal = FALSE; // Flag error - command buffer not empty
   return(retVal);
}

/*--------------------------------
 * Function: writeToEE
 * Parameters
 *         ix - index of alarm code to update
 *         code - code to store 
 * Description: Stores and integer alarm code to alarmcode
 *              array at index ix. Assume that the array
 *              is in EEPROM. Need to modify sector (4 bytes).
 *-------------------------------*/
int writeToEE(int ix, int code)
{
   int retVal = TRUE;  // assume that write is successful
   int *eepromAddr;
   int newcodes[2];
   // Detemine which four bytes need modifying
   if(ix < 2) // ix is 0 or 1
   {
      eepromAddr = &alarmCodes[0];
      newcodes[0] = alarmCodes[0];
      newcodes[1] = alarmCodes[1];
      newcodes[ix] = code;  // this is the modification
   } 
   else if(ix < 4)  // ix is 2 or 3 
   {
      eepromAddr = &alarmCodes[2];
      newcodes[0] = alarmCodes[2];
      newcodes[1] = alarmCodes[3];
      newcodes[ix-2] = code;  // this is the modification
   } 
   else
   {
      eepromAddr = &alarmCodes[4];
      newcodes[0] = code;
      newcodes[1] = 0xFFFF; // no 5th value in the array
   }
   
   ESTAT = ACCERR | PVIOL; // Clear error flags
   if(ESTAT & CBEIF)  // checks that command buffer is empty
   {
      // first word
      *eepromAddr = newcodes[0];    // Write data word aligned address
      ECMD = SECTOR_MODIFY;     // Erases 2 words, write one word
      ESTAT = CBEIF;            // Write 1 to CBEIF to lauch command
      if(ESTAT & (ACCERR|PVIOL) != 0) retVal = FALSE; // Flag the error
      else 
      {
         while(!(ESTAT & CCIF)) ;  // wait until command complete      
         *(eepromAddr+1) = newcodes[1];    // Write data word aligned address
         ECMD = PROG;              // Write program command
         ESTAT = CBEIF;            // Write 1 to CBEIF to lauch command
         if(ESTAT & (ACCERR|PVIOL) != 0) retVal = FALSE; // Flag the error
         else while(!(ESTAT & CCIF)) ;  // wait until command complete      
      }
   } 
   else retVal = FALSE; // Flag error - command buffer not empty
   return(retVal);
}



