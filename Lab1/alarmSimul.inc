;---------------------------------
; File: alarmSimul.inc
; Description: Include file for Alarm System Simulation
;              project
;----------------------------------------------
	IFNDEF ALARM_SIMUL_HDR  ; Start of conditional assembly
ALARM_SIMUL_HDR   EQU	1	 ; prevents future inclusion of the file

; for calculating wins
NOCHAR        equ    0xff    
BEL	      equ    '@'   ; 0x07
TRUE          equ    1
FALSE         equ    0
NUMCODES      equ    5
XWINSUM        equ   ('X'+'X'+'X')&$FF  ; sum of three X's
OWINSUM        equ   'O'+'O'+'O'        ; sum of three O's
NL             equ   $0a                ; NEWLINE
CR             equ   $0d                ; carriage return
ASCII_CONV_NUM equ   $30                ; For converting digit to ASCII

	 ENDIF  ; End of conditional assembly
