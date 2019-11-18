;------------------------------------------------------
; Alarm System Simulation Assembler Program
; File: delay.asm
; Description: The Delay Module
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------

; internal symbols defined for access
            XDEF setDelay, pollDelay, delayMs       
; include derivative specific macros
            NOLIST
            INCLUDE 'alarm.inc'
            LIST
            
; code section
.text:     SECTION

;------------------------------------------------------
; Subroutine setDelay
; Parameters: cnt - accumulator D
; Returns: nothing
; Global Variables: delayCount
; Description: Intialises the delayCount 
;              variable.
;------------------------------------------------------
setDelay: 

   ; Complete this subroutine
   std delayCount ; delayCount = cnt;
   rts


;------------------------------------------------------
; Subroutine: pollDelay
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
;  DEX - 1 cycle
;  BNE - 3 cyles - when branch is taken
;  Need 4 NOP
;   Run Loop 3000 times to create a 1 ms delay   
;------------------------------------------------------
; Stack Usage:
   OFFSET 0  ; to setup offset into stack
PDLY_VARSIZE:
PDLY_PR_Y   DS.W 1 ; preserve Y
PDLY_PR_X   DS.W 1 ; preserve X
PDLY_PR_B   DS.B 1 ; preserve B
PDLY_RA     DS.W 1 ; return address

pollDelay: pshb
   pshx
   pshy


   ; Complete this routine

   ldaa #FALSE       ; byte retval = FALSE;
   ldx #3000         ; short cntr = 3000;
   ldy delayCount    ; short delay = delayCount;
delay1ms             ; do
                     ; {
   nop               ;   (void)0;
   nop               ;   (void)0;
   nop               ;   (void)0;
   nop               ;   (void)0;
   dex               ;   cntr--;
   bne delay1ms      ; } while(cntr != 0);
after1ms:            ;
   dey		     ; delay--;
   bne pdly_endif1   ; if(delayCount == 0) {
   ldaa #TRUE        ;   retval = TRUE;
pdly_endif1:         ; }
                     ; return(retval);
   sty delayCount    ; delayCount = delay;
   ; restore registers and stack
   puly
   pulx
   pulb
   rts

;------------------------------------------------------
; Subroutine delayms
; Parameters: num - accumulator D
; Returns: nothing
; Global Variables: delayCount
; Description: Intialises the delayCount 
;              variable provided by the keypad
;	       and delays for num ms
;------------------------------------------------------
; Stack Usage:
   OFFSET 0  ; to setup offset into stack
DLM_VARSIZE:
DLM_PR_D   DS.W 1 ; preserve D
DLM_PR_A   DS.W 1 ; preserve A
DLM_RA     DS.W 1 ; return address

delayMs: pshd
   psha

   jsr setDelay
delms_while:
   jsr pollDelay
   tsta
   beq delms_while

   pula
   puld
   rts
   
;------------------------------------------------------
; Global variables
;------------------------------------------------------
.data SECTION

delayCount ds.w 1   ; 2 byte delay counter