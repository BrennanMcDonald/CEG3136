;-------------------------------------------------------------
; Alarm System Assembler Program
; File:  switches.asm
; Description: This file contains the Switches module for the
;              Alarm System project.
;-----------------------------------------------------------------*/
; Include header files
 include "sections.inc"
 include "reg9s12.inc"  ; Defines EQU's for Peripheral Ports

 SWITCH code_section  ; place in code section
;----------------------------------------
; Subroutine: initSwitches
; Parameters: none
; Returns: nothing
; Description: Initialises the port for monitoring the switches
;              and controlling LEDs.
;----------------------------------------
initSwitches:        
   clr  DDRH         ; DDRH = 0; // set to input (switches)
   movb #$ff,PERH     ; PERH = 0xff; // Enable pull-up/pull-down 
   clr  PPSH     ; PPSH = 0x00; // pull-up device connected to H
                     ;             // switches ground the pins when closed.
   rts

;------------------------
; Subrooutine: getSwStatus
; Parameters:  none
; Returns: Acc A - An 8 bit code that indicates which
;          switches are opened (bit set to 1).
; Description: Checks status of switches and 
;              returns bytes that shows their
;              status.      
;---------------------------
getSwStatus:
    ldaa PTH   ;return(PTH);
    rts