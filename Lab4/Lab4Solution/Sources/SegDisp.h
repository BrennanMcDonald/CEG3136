/*----------------
File: SegDisp.h
Description: Header file for Segment Display Module
--------------------*/
#include "mc9s12dg256.h"
// Function Prototypes - Entry Points
void initDisp(void);
void clearDisp(void);
void setCharDisplay(char, byte );
void turnOnDP(int);
void turnOffDP(int);