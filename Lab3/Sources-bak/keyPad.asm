;----------------------------------------------------------------------
; File: Keypad.asm
; Author:

; Description:
;  This contains the code for reading the
;  16-key keypad attached to Port A
;  See the schematic of the connection in the
;  design document.
;
;  The following subroutines are provided by the module
;
; char pollReadKey(): to poll keypad for a keypress
;                 Checks keypad for 2 ms for a keypress, and
;                 returns NOKEY if no keypress is found, otherwise
;                 the value returned will correspond to the
;                 ASCII code for the key, i.e. 0-9, *, # and A-D
; void initkey(): Initialises Port A for the keypad
;
; char readKey(): to read the key on the keypad
;                 The value returned will correspond to the
;                 ASCII code for the key, i.e. 0-9, *, # and A-D
;---------------------------------------------------------------------


            XREF delayms
            
            XDEF pollReadKey, initKeyPad, readKey    

            NOLIST
            INCLUDE 'mc9s12dg256.inc'
            LIST


**************EQUATES**********

.data SECTION

;-----Conversion table
NUMKEYS	EQU	16	; Number of keys on the keypad
BADCODE 	EQU	$FF 	; returned of translation is unsuccessful
NOKEY		EQU 	$00   ; No key pressed during poll period
POLLCOUNT	EQU	1     ; Number of loops to create 1 ms poll time

COLS  EQU PORTA
ROWS  EQU PORTA
LED   EQU PORTB
ROW0  EQU %00010000
ROW1  EQU %00100000
ROW2  EQU %01000000
ROW3  EQU %10000000
COLM  EQU %00001111
ROWM  EQU %11110000

PDELAY  RMB 1

KCODE0  FCB $31,$32,$33,$41    ;"123A"
KCODE1  FCB $34,$35,$36,$42    ;"456B"
KCODE2  FCB $37,$38,$39,$43    ;"789C"
KCODE3  FCB $2A,$30,$23,$44    ;"*0#D"
.rodata SECTION  ; Constant data


.text SECTION  ; place in code section
;-----------------------------------------------------------	
; Subroutine: initKeyPad
;
; Description: 
; 	Initiliases PORT A
;-----------------------------------------------------------	
initKeyPad:        ;
   ;STAA  DDRB         ;MAKE PORTB OUTPUT
   ;lDAA  #$02         ;
   ;STAA  DDRJ         ;ENABLE LED ARRAY ON PORTB OUTPUT
   ;LDAA  #$00         ;
   ;STAA  PTJ          ;
   CLR   DDRA
   LDAA  #$FF
   LDAA  #$F0         ;MAKE PORT A HIGH NIBLE OUTPUT
   STAA  DDRA         ;LOW NIBLE INPUT
   LDAA  #$0F         ;
   STAA  DDRP

   ;STAA  PTP          ;TURN OFF 7SEG LED
   ;LDAA  #$00         ;
   ;STAA  PORTB        ;INITIALIZE PORT B

	
    rts

;-----------------------------------------------------------    
; Subroutine: ch <- pollReadKey
; Parameters: none
; Local variable:
; Returns
;       ch: NOKEY when no key pressed,
;       otherwise, ASCII Code in accumulator B

; Description:
;  Loops for a period of 2ms, checking to see if
;  key is pressed. Calls readKey to read key if keypress 
;  detected (and debounced) on Port A and get ASCII code for
;  key pressed.
;-----------------------------------------------------------
; Stack Usage
	OFFSET 0  ; to setup offset into stack

pollReadKey:                  ;TEST TO MAKE SURE NO BUTTON PRESSED
   LDAA  #ROWM        ;
   STAA  ROWS         ;SET ROWS HIGH
   LDAA  COLS         ;CAPTURE PORT A
   ANDA  #COLM        ;MASK OUT ROWS
   CMPA  #$00         ;
   LBNE  pollReadKey           ;IF COLUMS IS ZERO NO BUTTON PRESSED
                      ;DO NOT MOVE ON UNTILL NO BUTTON IS PRESSED
debounce:
   LDD   #1                  ;
   JSR   delayms      ;CALL 15mS DELAY
   LDAA  COLS         ;
   ANDA  #COLM        ;
   CMPA  #$00         ;IF COLS !=0 THEN A BUTTON IS PRESSED
   BNE   OVER         ;
   BRA   debounce           ;IF NO BUTTON PRESSED KEEP CHECKING
OVER:                 ;
   JSR   delayms      ;DEBOUCE DELAY
   LDAA  COLS         ;READ PORT A
   ANDA  #COLM        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR PRESS AFTER DEBOUNCE
   BNE   OVER1        ;IF PRESSED GO FIND WHAT ROW
   LBRA  debounce;IF NO PRESS G $200AFTER DEBOUNCE GO BACK
OVER1:                ;
   LDAA  #ROW0        ;MAKE HIGH ROW0 THE REST GROUNDED
   STAA  ROWS         ;
   MOVB  #$08,PDELAY  ;SET COUNT TO PROVIDE SHORT DELAY FOR STABILITY
   LBRA readKey
   rts

;-----------------------------------------------------------	
; Subroutine: ch <- readKey
; Arguments: none
; Local variable: 
;	ch - ASCII Code in accumulator B

; Description:
;  Main subroutine that reads a code from the
;  keyboard using the subroutine readKeybrd.  The
;  code is then translated with the subroutine
;  translate to get the corresponding ASCII code.
;-----------------------------------------------------------	
; Stack Usage
	OFFSET 0  ; to setup offset into stack

readKey:             ;AFTER CHANGING THE PORT A OUTPUT
   DEC   PDELAY       ;DECREMENT COUNT
   LBNE   readKey ;IF COUNT NOT ZERO KEEP DECREMENTING
   LDAA  COLS         ;READ PORTA
   ANDA  #COLM        ;MASK OUT ROWS
   CMPA  #$00         ;IS INPUT ZERO?
   BNE   R0           ;IF COLUMS NOT ZERO THEN BUTTON IS IN ROW 0
   LDAA  #ROW1        ;IF ZERO THEN BUTTON NOT IN ROW0
   STAA  ROWS         ;TURN ON ROW 1 TURN OFF ALL OTHERS
   MOVB  #$08,PDELAY  ;SHORT DELAY TO STABALIZE
P2:                   ;AFTER CHANGING THE PORT A OUTPUT
   DEC   PDELAY       ;DECREMENT COUNT
   BNE   P2           ;IF COUNT NOT ZERO KEEP DECREMENTING
   LDAA  COLS         ;READ PORT A
   ANDA  #COLM        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR KEY PRESS
   BNE   R1           ;IF PRESSED KEY IS IN ROW1
   LDAA  #ROW2        ;IF ZERO BUTTON NOT IN ROW1
   STAA  ROWS         ;TURN ON ROW2 ALL OTHERS OFF
   MOVB  #$08,PDELAY  ;SHORT DELAY TO STABALIZE PORTA
P3:                   ;
   DEC   PDELAY       ;DECREMENT COUNT
   BNE   P3           ;DELAY LOOP
   LDAA  COLS         ;READ PORTA
   ANDA  #COLM        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR PRESS
   BNE   R2           ;IF FOUND KEY IS IN ROW2
   LDAA  #ROW3        ;IF ZERO MOVE TO ROW3
   STAA  ROWS         ;TURN ON ROW3 ALL OTHERS OFF
   MOVB  #$08,PDELAY  ;SHORT DELAY TO STABALIZE OUTPUT
P4:                   ;
   DEC   PDELAY       ;DECREMENT DELAY
   BNE   P4           ;DELAY LOOP
   LDAA  COLS         ;READ PORT A
   ANDA  #COLM        ;MASK OUT ROWS
   CMPA  #$00         ;CHECK FOR PRESS
   BNE   R3           ;IF FOUND KEY IN ROW3
   LBRA   debounce           ;IF ROW NOT FOUND GO BACK TO START
R0:                   ;
   LDX   #KCODE0      ;LOAD PONTER TO ROW0 ARRAY
   BRA   FIND         ;GO FIND COLUMN
R1:                   ;
   LDX   #KCODE1      ;LOAD POINTER TO ROW1 ARRAY
   BRA   FIND         ;GO FIND COUMN
R2:                   ;
   LDX   #KCODE2      ;LOAD PINTER TO ROW2
   BRA   FIND         ;GO FIND COLUMN
R3:                   ;
   LDX   #KCODE3      ;LOAD POINTER TO ROW3
   BRA   FIND         ;GO FIND COLUMN
FIND:                 ;
   ANDA  #COLM        ;MASK OUT ROWS
   COMA               ;INVERT COLUMN
SHIFT:                ;
   LSRA               ;LOGICAL SHIFT RIGHT PORTA
   BCC   MATCH        ;IF CARY CLEAR COLUM IS FOUND
   INX                ;IF CARY NOT CLEAR INCREMENT POINTER TO ROW ARRAY
   BRA   SHIFT        ;SHIFT RIGHT UNTIL CARY IS CLEAR.
MATCH:                ;
   LDAB  0,X          ;LOAD ASCII FROM ROW ARARAY    
    rts		           ;  return(ch); 

