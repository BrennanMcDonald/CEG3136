;--------------------------------------
; File: sections.inc
; Description: Defines the sections for the project.
;              Note the use of the symbol SECTIONS_DEFINED
;              for conditional assembly into modules.
;----------------------------------------

	IFNDEF SECTIONS_DEFINED  ; Start of conditional assembly
SECTIONS_DEFINED   EQU	1	 ; prevents future inclusion of the file

; Define addresses of various sections
VARIABLES EQU $3000   ; $3000 - $3FFF
PROGRAM   EQU $2000  ; $2000 - $2FFF
STACK     EQU $2000  ; $1000 - $1FFF

;----------------------------------------
; Global Variable section
; Use the DS - define storage directive
;              to define space for 
;              global variables and data
;              structures.
;----------------------------------------
globalVar SECTION
	ORG VARIABLES   ; places section in RAM
;-----------------------------------------
; Code section
; Enter assembly instructions (HCS12) to create
; executable code.
;-----------------------------------------
code_section SECTION
	ORG PROGRAM  ; places section in RAM - simulates ROM

;------------------------------------------
; Global constants
; In simple programs (single module) global constants are 
; simply placed at the end of code and not section is
; explicitly defined.
;--------------------------------------------
globalConst SECTION
	ORG ENDCODE ;--ENDCODE is defined on the second pass of the assembler

;----------------------------------------------
; Defining the start of the globalConst Section
; The following should be added to the end of the 
; main module
;----------------------------------------------
;	SWITCH code_section 
;ENDCODE	

	 ENDIF  ; End of conditional assembly
