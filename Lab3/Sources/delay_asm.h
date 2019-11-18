/*----------------------
File: Delay_asm.h
Description:  Header file to use the Delay Module
-----------------------*/

#ifndef _DELAY_ASM_H
#define _DELAY_ASM_H

//C Prototypes to assembler subroutines - Entry Points
void delayms(int);
void setDelay(int);
int polldelay(void);

#endif /* _DELAY_ASM_H */