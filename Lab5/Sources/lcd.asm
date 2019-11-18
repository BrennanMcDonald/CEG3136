;**************************************************************
;* File: lcd.asm
;* Assembly language routines for C function calls            *
;* for manipulating the LCD
;**************************************************************

; external symbols referenced
            XREF delayms
; internal symbols defined for access
            XDEF data8,lcd_init,clear_lcd, set_lcd_addr
            XDEF type_lcd       
; include derivative specific macros
            INCLUDE 'mc9s12dg256.inc'

; code section
.text:     SECTION
;  Initialize LCD
lcd_init:
	      ldaa	#$ff
	      staa	DDRK		              ; port K = output
       	ldx	  #init_codes 	        ; point to init. codes.
	      pshb            	          ; output instruction command.
       	ldab   	1,x+                ; no. of codes
lcdi1:	ldaa   	1,x+                ; get next code
       	jsr    	write_instr_nibble 	; initiate write pulse.
       	pshd
       	pshx
       	ldd     #5
       	jsr     delayms		;delay 5 ms
       	pulx
       	puld
       	decb                    ; in reset sequence to simplify coding
       	bne    	lcdi1
       	pulb
       	rts

;   write instruction byte B to LCD
instr8:
            tba
;            jsr   sel_inst
            jsr   write_instr_byte
            ldd     #10
            jsr     delayms
            rts

;   write data byte B to LCD
data8:
            tba
;            jsr   sel_data
            jsr   write_data_byte
            ldd     #10
            jsr     delayms
            rts

;   set address to B
set_lcd_addr:
            orab    #$80
            tba
            jsr     write_instr_byte
            ldd     #10
            jsr     delayms
            rts

;   clear LCD
clear_lcd:
            ldaa    #$01
            jsr     write_instr_byte
            ldd     #10
            jsr     delayms
            rts

;	display asciiz string on LCD
;	D -> asciiz string 
type_lcd:
            pshx              ;save X
            tfr     D,X       ;X -> asciiz string
next_char   ldaa	  1,X+		  ;get next char
	          beq	    done		  ;if null, quit
	          jsr	    write_data_byte	;else display it
	          pshx ; delayms changes x (C compiler) - GA
            ldd     #10
            jsr     delayms
            pulx
	          bra	    next_char	;and repeat
done	      pulx              ;restore X
            rts


; write instruction upper nibble
write_instr_nibble:
        anda    #$F0
        lsra
        lsra            ; nibble in PK2-PK5
        oraa    #$02    ; E = 1 in PK1; RS = 0 in PK0
        staa    PORTK
        ldy     #10
win     dey
        bne     win
        anda    #$FC    ; E = 0 in PK1; RS = 0 in PK0
        staa    PORTK
        rts

; write data upper nibble
write_data_nibble:
        anda    #$F0
        lsra
        lsra            ; nibble in PK2-PK5
        oraa    #$03    ; E = 1 in PK1; RS = 1 in PK0
        staa    PORTK
        ldy     #10
wdn     dey
        bne     wdn
        anda    #$FD    ; E = 0 in PK1; RS = 1 in PK0
        staa    PORTK
        rts

; write instruction byte
write_instr_byte:
        psha
        jsr     write_instr_nibble
        pula
        asla
        asla
        asla
        asla
        jsr     write_instr_nibble
        rts

;write data byte
write_data_byte:
        psha
        jsr     write_data_nibble
        pula
        asla
        asla
        asla
        asla
        jsr     write_data_nibble
        rts
        
.rodata SECTION            
; Initialization codes for 4-bit mode      	
; uses only data in high nibble
init_codes: 
        fcb	12		; number of high nibbles
	      fcb	$30		; 1st reset code, must delay 4.1ms after sending
        fcb	$30		; 2nd reste code, must delay 100us after sending
        ;  following 10 nibbles must  delay 40us each after sending
	      fcb $30   ; 3rd reset code,
	      fcb	$20		; 4th reste code,
        fcb	$20   ; 4 bit mode, 2 line, 5X7 dot
	      fcb	$80   ; 4 bit mode, 2 line, 5X7 dot
        fcb	$00		; cursor increment, disable display shift
	      fcb	$60		; cursor increment, disable display shift
        fcb	$00		; display on, cursor off, no blinking
	      fcb	$C0		; display on, cursor off, no blinking
	      fcb	$00		; clear display memory, set cursor to home pos
	      fcb	$10		; clear display memory, set cursor to home pos
