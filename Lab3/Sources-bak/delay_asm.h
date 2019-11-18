                                                           /*
----------------------
File: KeyPad_asm.h
Description:  Header file to use the KeyPad Module
-----------------------
*/
#ifndef _DELAY_ASM_H
#define _DELAY_ASM_H
//C Prototypes to assembler subroutines
void polldelay(void);
void delayms(void);

// Some Definitions
#define NOKEY 0  // See KeyPad.asm
#endif /* _KEYPAD_ASM_H */