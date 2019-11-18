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
      if(getTemp() >= HIGH_TEMP) triggerAlarm();
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
   initThermistor(); 
   initLCD();   // need to initialise with interrupts running
                // since delay module is used.
   
   // Configure PORT P, Bit 4 to manage temperature LED.
   // Setup Port M
   DDRP |= BIT4 | BIT5; // set pin 4 to output
   PTP &= ~BIT4; // turn off Red LED
   PTP |= BIT5; // turn on Blue LED
   
   // Configure Timer Channel 6 for interrupt every 200 ms
   TIOS |= BIT6; // set TC6 to output-compare
	 TC6 = TCNT + TEN_MS; // Set TC2 for one ms delay
	 TIE |= BIT6; // enable interrupt timer channel 6
	 displayTempFlag = TRUE;   
	 
	 // Turn of LEDs
	 PTJ |= BIT1;
}

/*----------------------------------------------------
Interrupt: tc6_isr
Description: This service routine displays temperature
             on the 7-segment display.
-------------------------------------------------------*/
void interrupt VectorNumber_Vtimch6 tc6_isr(void) 
{
    static int count = 20;  // need to count 20 - 10-ms times
    int temperature;
    count--;
    if(count == 0) 
    {
        temperature = getTemp();
        if(temperature >= HIGH_TEMP)
        {
          PTP |= BIT4;  // Turn on RED
          PTP &= ~BIT5; // Turn off Bleu
       }
        else 
        {
          PTP &= ~BIT4;  // Turn off Red
          PTP |= BIT5;   // Turn on Bleu
        }
        if(displayTempFlag) // check that its enabled
        {
            setCharDisplay(' ',3);  // blank last display
            displayTemp(temperature); // display the temperature
        }
        count = 20;      // reset count
    }
    TC6 = TC6+TEN_MS; // reading TC2 resets interrupt      
}

/*---------------------------------------------
Function: displayTemp
Description:  Setups the codes (calling setCharDisplay)
              for the temperature passed.
---------------------------------------------------*/
void displayTemp(int num) 
{
   byte ch;
   // tenth of degree
   ch = (byte)(num%10);  // get tenth
   ch = ch | 0x30; // convert to ASCII
   setCharDisplay(ch,2); // sets code for 3rd display
   turnOnDP(1);
   // units
   num = num/10;  
   ch = (byte)(num%10);  // get degree units
   ch = ch | 0x30; // convert to ASCII
   setCharDisplay(ch,1); // sets code for 2nd display 
   // 10's of degrees
   num = num/10;
   if(num != 0) 
   {
      ch = (byte)num;  // get 10's of degrees
      ch = ch | 0x30; // convert to ASCII
      setCharDisplay(ch,0); // sets code for 1rst display 
   } 
   else setCharDisplay(' ',0);
}