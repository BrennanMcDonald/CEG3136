/*-------------------------------------------------------------
 * File:  switches.c
 * Description: This file contains the Switches module for the
 *              Alarm System Simulation project.
-----------------------------------------------------------------*/
#include "switches.h"  // Definitions file

/*----------------------------------------
 * Function: initSwitches
 * Parameters: none
 * Returns: nothing
 * Description: Initialises the port for monitoring the switches.
 *----------------------------------------*/
void initSwitches()
{         
   DDRH = 0; // set to input (switches)
   PERH = 0; // Disable pull-up/pull-down 
}

/*------------------------
 * Function: getSwStatus
 * Parameters:  none
 * Returns: An 8 bit code that indicates which
 *          switches are opened (bit set to 1).
 * Description: Checks status of switches and 
 *              returns bytes that shows their
 *              status.      
 *---------------------------*/
byte getSwStatus()
{
    return(PTH);
}
