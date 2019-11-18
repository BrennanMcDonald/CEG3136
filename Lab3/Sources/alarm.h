/*------------------------------------------------
 * File: alarm.h
 * Description: Include file with definitions for 
 *              the Alarm System Simulation project
--------------------------------------------------*/

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


// Definitions files
#include <ctype.h>  // Standard C include file (for isdigit)
#include "config.h" // Configuration Module
#include "armed.h" // Armed Module
#include "switches.h"  // Switches Module
#include "keyPad_asm.h" // KeyPad Module
#include "delay_asm.h" // Delay Module
#include "lcdDisp.h"  // LCD Display Module
#include "SegDisp.h"  // Segment Display Module
