/*----------------------
File: KeyPad_asm.h
Description:  Header file to use the KeyPad Module
-----------------------*/

#ifndef _KEYPAD_ASM_H
#define _KEYPAD_ASM_H

//C Prototypes to assembler subroutines - Entry Points
void initKeyPad(void);
byte pollReadKey(void);
byte readKey(void);

// Some Definitions
#define NOKEY 0
#define ROW1 0b11101111
#define ROW2 0b11101111
#define ROW3 0b10111111
#define ROW4 0b01111111
#define NUMKEYS 16
#define BADCODE 0xFF
#define POLLCOUNT 1     // See KeyPad.asm

#endif /* _KEYPAD_ASM_H */