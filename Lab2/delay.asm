;------------------------------------------------------
; Alarm System Simulation Assembler Program
; File: delay.asm
; Description: The Delay Module
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------

; Some definitions

	SWITCH code_section

;------------------------------------------------------
; Subroutine setDelay
; Parameters: cnt - accumulator D
; Returns: nothing
; Global Variables: delayCount
; Description: Intialises the delayCount 
;              variable.
;------------------------------------------------------
setDelay: 
   std delayCount
   rts


;------------------------------------------------------
; Subroutine: polldelay
; Parameters:  none
; Returns: TRUE when delay counter reaches 0 - in accumulator A
; Local Variables
;   retval - acc A cntr - X register
; Global Variables:
;      delayCount
; Description: The subroutine delays for 1 ms, decrements delayCount.
;              If delayCount is zero, return TRUE; FALSE otherwise.
;   Core Clock is set to 24 MHz, so 1 cycle is 41 2/3 ns
;   NOP takes up 1 cycle, thus 41 2/3 ns
;   Need 24 cyles to create 1 microsecond delay
;   8 cycles creates a 333 1/3 nano delay
;	DEX - 1 cycle
;	BNE - 3 cyles - when branch is taken
;	Need 4 NOP
;   Run Loop 3000 times to create a 1 ms delay   
;------------------------------------------------------
; Stack Usage:
	OFFSET 0  ; to setup offset into stack
D15mH EQU 17
D15mL EQU 250

DR15mH  RMB 1
DR15mL  RMB 1

PDLY_VARSIZE:
PDLY_PR_Y   DS.W 1 ; preserve Y
PDLY_PR_X   DS.W 1 ; preserve X
PDLY_PR_B   DS.B 1 ; preserve B
PDLY_RA     DS.W 1 ; return address


REALDELAY:                ;DELAY SUBROUTINE
   LDAA  #D15mH       ;LOAD FIRST LAYER DELAY COUNT
   STAA  DR15mH       ;
D2:                   ;
   LDAA  #D15mL       ;LOAD SECOND LAYER DELAY COUNT
   STAA  DR15mL       ;
D1:                   ;
   DEC   DR15mL       ;DECREMENT SECOND LAYER COUNT
   NOP                ;NOP DELAY
   NOP                ;
   BNE   D1           ;BACK TO START OF SECOND LAYER IF NOT ZERO
   DEC   DR15mH       ;IF SECOND LAYER ZERO DECREMENT FIRST LAYER
   BNE   D2           ;IF FIRST LAYER NOT ZERO GO BACK RELOAD FRIST LAYER
   RTS                ;RETURN TO FROM SUBROUTINE WEHN LAYER ONE IS ZERO

polldelay: pshb
   pshx
   pshy
   ; Complete this routine
   ldy delayCount

whileStart:
   nop
   nop
   nop
   nop
   dey
   bne whileStart
   ldx delayCount
   dex
   beq complete
   lda #FALSE
   bra return
complete:
   lda #TRUE
return:
   stx delayCount

   ; restore registers and stack
   puly
   pulx
   pulb
   rts

delayms: pshb
   pshx
   pshy
   ; Complete this routine
   pshd
   puly

whileStartms:
   nop
   nop
   nop
   nop
   dey
   bne whileStartms
   ldx delayCount
   dex
   beq complete
   lda #FALSE
   bra return
completems:
   lda #TRUE
returnms:
   stx delayCount

   ; restore registers and stack
   puly
   pulx
   pulb
   rts

;------------------------------------------------------
; Global variables
;------------------------------------------------------
   switch globalVar
delayCount ds.w 1   ; 2 byte delay counter
