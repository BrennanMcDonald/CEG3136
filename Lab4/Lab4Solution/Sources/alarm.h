/*------------------------------------------------
 * File: alarm.h
 * Description: Include file with definitions for 
 *              the Alarm System Simulation project
--------------------------------------------------*/
#include <stddef.h>
#include <mc9s12dg256.h>
/* Notes on mc9s12dg256.h:
   1) the type "byte" is defined as "unsigned char"
*/


/*************************Some Definitions**********************/
// for calculating wins - The following should be translated to 
// Assembler EQU directives
#define NOCHAR 0xff
#define BEL 0x07
#define TRUE 1
#define FALSE 0
#define ASCII_CONV_NUM 0x30  // For converting digit to ASCII
#define SPACE ' '            // Space character
#define NUMCODES 5
#define NEWLINE "\n"
#define BIT0 0b00000001
#define BIT1 0b00000010
#define BIT2 0b00000100
#define BIT3 0b00001000
#define BIT4 0b00010000
#define BIT5 0b00100000
#define BIT6 0b01000000
#define BIT7 0b10000000
#define HIGH_TEMP 270    // High temperature for turning on alarm


// Definitions files
#include <ctype.h>  // Standard C include file (for isdigit)
#include "config.h" // Configuration Module
#include "armed.h" // Armed Module
#include "switches.h"  // Switches Module
#include "keyPad.h" // KeyPad Module
#include "delay.h" // Delay Module
#include "lcdDisp.h"  // LCD Display Module
#include "SegDisp.h"  // Segment Display Module
#include "siren.h"    // Siren Module
