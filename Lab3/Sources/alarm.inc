;                      /*************************Some Definitions**********************/
;// for calculating wins - The following should be translated to 
;// Assembler EQU directives
;#define NOCHAR 0xff
;#define BEL 0x07
;#define TRUE 1
;#define FALSE 0
;#define ASCII_CONV_NUM 0x30  // For converting digit to ASCII
;#define SPACE ' '            // Space character
;#define NUMCODES 5
;#define NEWLINE "\n"

NOCHAR:         equ $FF
BEL:            equ $07
TRUE:           equ 1
FALSE:          equ 0
ASCII_CONV_NUM: equ $30  ; For converting digit to ASCII
SPACE:          equ 32            ; Space character DECIMAL:32
NUMCODES:       equ 5
NEWLINE equ 10           ;New Line (NL) DECIMAL:10