;------------------------------------------------------
; Alarm System Assembler Program
; File: utilities.asm
; Description: The Utilities Module
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------

	SWITCH code_section

;------------------------------------------------------
; Subroutine isdigit
; Parameters: chr - received in accumulator A/moved to B 
; Returns: TRUE - chr is a digit, FALSE otherwise
; Variables: retval in accumulator A
; Description: Returns TRUE if chr is a digit character
;              and FALSE otherwise.
;------------------------------------------------------
isdigit: pshb   ; save B on stack
   tab          ; save Parameter in B
   ldaa #FALSE  ;   byte retval = FALSE;
   cmpb #'0'    ;   if(chr >= '0' && chr <= '9') retval = TRUE;
   blo ISD_endif
   cmpb #'9'
   bhi ISD_endif
   ldaa #TRUE
ISD_endif:
   pulb         ; restore B
   rts          ; return(retval); // in A



;------------------------------------------------------
; Subroutine: pollgetchar
; Parameters:  none
; Returns: char read from SC0 or NOCHAR if none available
;          Returned in Acc A
; Variables:
;      ptr in X register
;      sum in Accumulator B       
; Description: Checks the RDRF bit to see if a character
;              is available before reading a character using getchar.
;------------------------------------------------------

polgetchar: psha     ; gechar destroys contents of acc A
  ldab #NOCHAR        ;  char chr = NOCHAR;
  
  brclr sc0sr1,%00100000,PGC_endif ; if(SCI0SR1_RDRF==1) 
  jsr [getchar, PCr]  ;                    chr = getchar();
PGC_endif
   pula            ; restore registers
   rts             ; return(chr);  in ACC B
