/*------------------------------------------------------------------------------- 
   File: keyPad.h
   Description:  Contains definitions and prototypes for the Keypad Module
------------------------------------------------------------------------------*/
#ifndef _KEYPAD_H
#define _KEYPAD_H

//C Prototypes to assembler subroutines - Entry Points
void initKeyPad(void);
char pollReadKey(void);
char readKey(void);

// Some Definitions
#define NOKEY 0  // See KeyPad.c - to indicate no key pressed
#define BADCODE 0xFF // indicates that key code was not mapped to ASCII char


#endif /* _KEYPAD_H */