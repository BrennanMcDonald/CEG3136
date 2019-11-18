
;------------------------------------------------------
; Alarm Simulation Assembler Program
; File: alarmSimul.asm (Alarm System Simulation Module)
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------
 NOLIST ; turn off listing to hide register definitions
 INCLUDE reg9s12.inc  ; Definitions for the mioccrocontroller registers
 LIST ; turn listing back on

; Some definitions
; Location of the register block
Regblk:       equ    $0000 
 INCLUDE sections.inc
 INCLUDE alarmSimul.inc

; Dbug12 subroutines
putchar        equ   $EE86
getchar        equ   $EE84
printf         equ   $EE88
writeEEByte    equ   $EEA6

        switch code_section
;------------------------------------------------------
; Alarm Simulation Module

; Main routine
; Variables: select - in register B (set by getchar)
; Description: The main routine for running the game.
;              Initialises things (via initgb) and the
;              loops forever playing games.
;------------------------------------------------------
        lds #STACK       ; Not reflected in C
        bsr inithw       ; initiliase the hardware
        ; byte select - in register B
   			;do
mainloop:  			; {
        ldd #MENU          ;   printf(MENU);
        jsr [printf,PCr] 
        jsr [getchar,PCr]  ;   select = getchar();  // getchar is debug 12 routine
	pshb ; save b
        pulb
        cmpb #'c'          ;   if(select == 'c') configCodes();
        bne mnElseif
        jsr configCodes
        bra mnEndif
mnElseif cmpb #'a'         ;   else if(select == 'a') enableAlarm();
        bne mnElse
        jsr enableAlarm
        bra mnEndif
mnElse                     ;   else /*do nothing*/;
mnEndif:
        bra mainloop       ; } while(1);  // loop forever
        swi                ; never reach here - infinite loop

;------------------------------------------------------
; Subroutine: inithw
; No parameters
; Variables: ptx - index register X
;            pty - index register Y
; Description: First setup up the microcontroller setting up the clock, 
;             shutting down the COP watchdog timer, and initialising 
;             the SCI serial interface. Initialises global variables also.
;------------------------------------------------------
inithw:
; -- Initialise the hardware
; Initialise the Phase-Lock-Loop (se page 34 of Dragon 12 Manual
;       The crystal freq. on the DRAGON12 Plus board is 8 MHz so the default bus speed is 2 MHz
;       In order to set the bus speed high than 4 MHz the PLL must be initialized
;
;       The math used to set the PLL frequency is:
;        
;       PLLCLK = CrystalFreq * 2 * (initSYNR+1) / (initREFDV+1)
;       
;       If CrystalFreq = 8Mhz on DRAGON12 Plus board
;         initSYNR     = 5    PLL multiplier will be 6
;         initREFDV    = 0    PLL divisor will be 1

;       PLLCLK = 4*2*6/1 = 48MHz
;       The bus speed = PLLCLK / 2 = 24 MHz
;
;      
;********PLL code for 24MHz bus speed from a 4/8/16 crystal
        sei
        ldx #Regblk
        bclr Clksel,x,%10000000  ; clear bit 7, clock derived from oscclk
        bset Pllctl,x,%01000000  ; Turn PLL on, bit 6 =1 PLL on, bit 6=0 PLL off
        ldaa #$05                ; 5+1=6 multiplier 
        staa Synr,x
;        ldaa #$03                ; divisor=3+1=4, 16 *6 /4 = 24Mhz for 16 MHz crystal
        ldaa #$01                ; divisor=1+1=2,  8 *6 /2 = 24Mhz for  8 MHz crystal
;        ldaa #$00                ; divisor=0+1=1,  4 *6 /1 = 24Mhz for  4 MHz crystal

        staa Refdv,x
wait_b3:
        brclr Crgflg,x, %00001000 wait_b3  ; Wait until bit 3 = 1
        bset Clksel,x, %10000000

        ; Setup Serial port
        ldd #156
        std Sc0bdh   ; Sets up the baud rate
        ldaa #$0c
        staa Sc0cr2  ; Enables serial interface
        
        ; Setup the data in the RAM
        ; For the Configuration Module
        movw #0,alarmCode
        movw #1000,mult
        rts

   switch globalConst

;-------------------------------------------------------------------------
; Data Structures
; The following data is stored in EEPROM 
; Following is data array used by testWin 
;   int alarmCodes[NUMCODES] = { 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF }; 
;------------------------------------------------------
alarmCodes dc.w $0000, $FFFF, $FFFF, $FFFF, $FFFF  ; note this will be updated in ROM

; Message strings
MENU     dc.b   "CEG3136 Alarm",NL,CR,"c-Config a-Arm",NL,CR,$00
NEWLINE  dc.b   NL,CR,$00

 
;----------
; Include other modules here
;-----------
 INCLUDE	config.asm
 INCLUDE	armed.asm
 INCLUDE	delay.asm
 INCLUDE	utilities.asm

   switch code_section
ENDCODE ;  used to define where the dataEEPROM section starts
        end                ; end of program
