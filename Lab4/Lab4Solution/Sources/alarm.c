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
int displayTempFlag;  // TRUE - display temp, FALSE - Do not display temp.

// Although these are defines, the strings must be stored somewhere
// in memory.  This means that the symbolic constants (such as WELCOME)
// represent the address to the strings. Need to store them in the
// EEPROM (read-only) memory
#define MENU1 "CEG Alarm System"
#define MENU2 "c-Config a-Arm"
// For configuring Channel 6 to display temperature
#define TEN_MS 7500  // 7500 * 1.3333 micro-sec = 10 ms


// Prototypes
void initMain(void);
void displayTemp(int); 


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
   initMain();
   
   // main loop
   for(;;)  // loop forever
   {
      printLCDStr(MENU1,0);
      printLCDStr(MENU2,1);
      select = pollReadKey();
      if(select == 'c') configCodes();
      else if(select == 'a') enableAlarm();
      else /* do nothing */;
   }
}

/*------------------------------------
 * Function: intMain
 * Description: Main initialisation to 
 *              initialise modules and 
 *              the Alarm Module.
 * --------------------------------*/
void initMain()
{
   // Initialisation 
   initCodes();  
   initKeyPad();
   initSwitches();
   initDisp();
      // Setup the timer
   TSCR1 = 0b10010000;  // Enable the timer and enable fast clear
   TSCR2 = 0b00000101;  // Setup prescaler to 32, for 1 1/3 micro-sec. tick
   initSiren(); 
   initDelay(); 
   asm cli;
   initLCD();   // need to initialise with interrupts running
                // since delay module is used.
   
}

