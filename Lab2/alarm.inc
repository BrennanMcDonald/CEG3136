;---------------------------------
; File: alarmSimul.inc
; Description: Include file for Alarm System Simulation
;              project
;----------------------------------------------
	IFNDEF ALARM_SIMUL_HDR  ; Start of conditional assembly
ALARM_SIMUL_HDR   EQU	1	 ; prevents future inclusion of the file

; for calculating wins

NOCHAR:         equ $FF
BEL:            equ $07
TRUE:           equ 1
FALSE:          equ 0
ASCII_CONV_NUM: equ $30  ; For converting digit to ASCII
SPACE:          equ 32            ; Space character DECIMAL:32
NUMCODES:       equ 5
NEWLINE equ 10           ;New Line (NL) DECIMAL:10

	 ENDIF  ; End of conditional assembly
