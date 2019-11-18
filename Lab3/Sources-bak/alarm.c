/*-------------------------------------------------------------
 * File:  alarm.c  - Alarm System Module
 * Description: The design of the assembler code is achieved using
 *              a C program.  This program is designed to create a
 *              Alarm System on the Dragon 12 Trainer card (i.e.
 *              the HCS12 Microcontroller).  The main objective of this
 *              program is to explore programming of the HC12 CPU.
-----------------------------------------------------------------*/
#include "main_asm.h"
#include "alarm.h"  // Definitions file
#include "string.h"

/*--------------Global Data Structures--------------------------*/
// The following data structures need not be located in RAM - They are 
// readonly

// Alarm codes - needs to be placed in EEPROM
#pragma DATA_SEG EEPROM_DATA
int alarmCodes[NUMCODES] = { 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
#pragma DATA_SEG DEFAULT 

// Although these are defines, the strings must be stored somewhere
// in memory.  This means that the symbolic constants (such as WELCOME)
// represent the address to the strings. Need to store them in the
// EEPROM (read-only) memory
#define MENU1 "CEG Alarm System"
#define MENU2 "c-Config a-Arm"

/*------------------------------------
 * Function: main
 * Description: The main routine for running the game.
 *              Initializes things (via initgb) and then
 *              loops forever playing games.
 * --------------------------------*/
void main()
{
   byte select;
   PLL_init();
   // Initialisation 
   initCodes();  
   initKeyPad();
   initSwitches();
   initLCD();
   initDisp();
   asm cli;
   // main loop
   for(;;)  // loop forever
   {
      printLCDStr(MENU1,0);
      printLCDStr(MENU2,1);
      select = readKey();
      if(select == 'c') configCodes();
      else if(select == 'a') enableAlarm();
      else /* do nothing */;
   }
}

