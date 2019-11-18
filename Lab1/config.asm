;------------------------------------------------------
; Alarm System Simulation Assembler Program
; File: config.asm - the CONFIGURATION Module
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------

        SWITCH code_section ; include in the code
;-----------------------------------
; Subroutine - configCodes
; Parameters: none
; Returns: nothing
; Local Variables:   ix,  input, flag - on stack
; Description: Gets user to select alarm code to update/disable. Calls
;              setcode to update the alarm code.
;------------------------------------------------------
; Stack Usage
	OFFSET 0 ; to setup offsets into stack
CFG_IX   DS.B 1   ; ix
CFG_INPUT DS.B 1  ; input
CFG_FLAG DS.B 1   ; flag
CFG_VARSIZE:
CFB_PR_D	DS.W 1	; preserve D 
CFG_RA	DS.W 1	; return address

configCodes: pshd
      ; byte ix;  // index into array
      ; byte input; // input from user.
      ; byte flag;
      leas -CFG_VARSIZE,SP
cfg_if1: jsr enterMstCode ; if(enterMstCode())
      tsta
      beq cfg_endif1
cfg_loop:               ;     do {
      ldd #CONFIGMSG    ;          printf(CONFIGMSG);
      jsr [printf,PCr]
      jsr [getchar,PCr] ;          input = getchar();
      stab CFG_INPUT,SP ;
      movb #TRUE,CFG_FLAG,SP;      flag = TRUE;
cfg_if2:
      ldaa CFG_INPUT,SP ;          if(input == 'a')
      cmpa #'a'
      bne cfg_elseif2
      ldaa #0           ;               setcode(0);
      jsr setcode
      bra cfg_endif2
cfg_elseif2:
      cmpa #'1'         ;           else if( input>='1' && input <= '4')
      blo cfg_else2
      cmpa #'4'
      bhi cfg_else2
      suba #ASCII_CONV_NUM  ;       {   ix = input-ASCII_CONV_NUM;
      bsr setcode           ;           setcode(ix); }
      bra cfg_endif2
cfg_else2:              ;           else      
      ldd #CERRMSG      ;           { printf(CERRMSG);
      jsr [printf,PCr]  ;
      movb #FALSE,CFG_FLAG,SP ;       flag = FALSE; }
cfg_endif2:
      tst CFG_FLAG,SP   ;       } while(!flag);
      beq cfg_loop
cfg_endif1:
      leas CFG_VARSIZE,SP
      puld
      rts

;--------------------------------
; Subroutine: enterMstCode
; Parameters: none
; Returns: TRUE - valid code entered, FALSE otherwise - Acc A.
; Description: Prompts user for the 4 digit master alarm code.
;-------------------------------
; Stack Usage
	OFFSET 0 ; to setup offsets into stack
EMC_RETVAL  DS.B 1   ; retval
EMC_I       DS.B 1   ; i
EMC_INPUT   DS.B 1   ; input
EMC_ALARMCODE DS.W 1 ; alarmCode
EMC_MULT    DS.W 1   ; mult
EMC_VARSIZE:
EMC_PR_Y    DS.W 1   ; preserve Y
EMC_PR_X    DS.W 1   ; preserve X
EMC_PR_B    DS.B 1   ; preserve B
EMC_RA	    DS.W 1   ; return address

enterMstCode pshb
   pshx
   pshy
   leas -EMC_VARSIZE,SP
   movb #FALSE,EMC_RETVAL,SP  ; byte retval = FALSE;
                              ; byte i;
                              ; byte input;
   movw #0,EMC_ALARMCODE,SP   ; int alarmCode = 0;
   movw #1000,EMC_MULT,SP     ; int mult = 1000;
   
   ldd #MSTCDMSG              ; printf(MSTCDMSG);
   jsr [printf, PCr]
   clr EMC_I,SP
emc_for:                      ; for(i=0 ; i<4 ; i++)
   jsr [getchar, PCr]         ; {
   stab EMC_INPUT,SP          ;    input = getchar();
emc_if1:
   tba
   jsr isdigit                ;    if(!isdigit(input))
   tsta
   beq emc_endfor             ;         break;
emc_else1:                    ;    else {
   ldab EMC_INPUT,SP          ;       alarmCode = alarmCode + mult*(input-ASCII_CONV_NUM);
   subb #ASCII_CONV_NUM
   clra
   ldy  EMC_MULT,SP
   emul
   addd EMC_ALARMCODE,SP
   std EMC_ALARMCODE,SP
   ldd EMC_MULT,SP            ;       mult = mult/10;
   ldx #10
   idiv
   stx EMC_MULT,SP
emc_if2: cpx #0               ;       if(mult == 0)  {
   bne emc_endif2
emc_if3: ldd alarmCodes      ;            if(alarmCode == alarmCodes[0]) 
   cpd EMC_ALARMCODE,SP
   bne emc_endif3
   movb #TRUE,EMC_RETVAL,SP   ;                 retval = TRUE;
emc_endif3:
emc_endif2:                   ;       }
emc_endif1:                   ;    }
   ldaa EMC_I,SP
   inca
   staa EMC_I,SP
   cmpa #4
   blo emc_for
emc_endfor:                   ; }
   ldaa EMC_RETVAL,SP         ; return(retval);
   leas EMC_VARSIZE,SP
   puly
   pulx
   pulb
   rts

;---------------------------------
; Subroutine; setcode (ix)
; Parameters
;        ix - in accumulator a
; Local variables
;        flag, i, input, digit, alarmCode, mult - on stack
; Description: Prompts user for a 4 digit alarm code to
;              update the alarm code at index ix. If 'd'
;              is entered the alarm code is disabled.  It
;              is not allowed to diable the master
;              alarm code.void setcode(byte ix).
;------------------------------------------------------
; Stack Usage
	OFFSET 0 ; to setup offsets into stack
SETC_IX   DS.B 1  ; ix
SETC_FLAG DS.B 1  ; flag
SETC_I    DS.B 1  ; i
SETC_INPUT DS.B 1 ; input 
SETC_DIGIT DS.W 1 ; digit
SETC_ALARMCODE DS.W 1  ; alarmCode
SETC_MULT DS.W 1  ; mult
SETC_VARSIZE:
SETC_PR_D DS.W 1	; preserve D
SETC_PR_X DS.W 1	; preserve D 
SETC_PR_Y DS.W 1	; preserve D  
SETC_RA	DS.W 1	; return address

setcode: pshy       ; {
         pshx
         pshd
      leas -SETC_VARSIZE,SP   ; make room for variables
      movb #TRUE, SETC_FLAG   ; byte flag = TRUE;
                              ; byte i;
                              ; byte input;
                              ; int digit;
                              ; int mult;
                              ; int alarmCode;
      movw #1000,SETC_MULT,SP ; int mult=1000; // multiplier
      staa SETC_IX,SP         ; save parameter value
setc_loop:                    ; do {
      movw #0,SETC_ALARMCODE,SP   ;  alarmCode=0;
      movw #1000,SETC_MULT,SP ;      mult=1000;
      ldd #GET_CODE_MSG       ;      printf(GET_CODE_MSG);
      jsr [printf, PCr]
      clr SETC_I,SP           ;      for(i=0 ; i< 4 ; i++)
setc_for:                     ;      {
      jsr [getchar, PCr]      ;         input = getchar();
      stab SETC_INPUT,SP
setc_if cmpb #'d'             ;         if(input == 'd')
      bne setc_elseif         ;         { 
setc_if2 ldaa SETC_IX,SP      ;            if(ix == 0) 
      cmpa #0
      bne setc_else2
      ldd #ERR_MST_MSG        ;               printf(ERR_MST_MSG);
      jsr [printf,PCr]
      bra setc_endif2
setc_else2                    ;            else {
      movw #$ffff,SETC_ALARMCODE,SP ;            alarmCode = 0xffff;
      movb #FALSE,SETC_FLAG,SP;                  flag = FALSE;
      bra setc_endfor          ;                 break; 
setc_endif2                   ;             }
      bra setc_endif          ;         }
setc_elseif:
      ldaa SETC_INPUT,SP      ;         else if(isdigit(input))
      jsr isdigit
      tsta
      beq setc_else
      ldab SETC_INPUT,SP      ;         {  digit = input - ASCII_CONV_NUM;
      subb #ASCII_CONV_NUM
      clra
      std SETC_DIGIT,SP       ;            alarmCode = alarmCode + digit * mult;
      ldy SETC_MULT,SP
      EMUL                    ; // Result digit*mult is in D
      addd SETC_ALARMCODE,SP
      std SETC_ALARMCODE,SP
      ldd SETC_MULT,SP        ;            mult = mult/10;
      ldx #10
      idiv
      stx SETC_MULT,SP
      cpx #0                  ;            if(mult == 0)
      bne setc_endif          ;             
      movb #FALSE,SETC_FLAG,SP ;                flag = FALSE;
      bra setc_endif          ;         }
setc_else:                    ;         else {
      ldd #CERRMSG            ;                printf(CERRMSG);
      jsr [printf, PCr]
      bra setc_endfor         ;                break;
                              ;         }
setc_endif:
      ldaa SETC_I,SP
      inca
      staa SETC_I,SP
      cmpa #4
      blo setc_for 
setc_endfor:                       ;   }
      tst SETC_FLAG,SP        ; } while(flag);
      bne setc_loop
      lda SETC_IX,SP   ; writeToEE( (int) &alarmCodes[ix], alarmCode);
      lsla  ; double index value - 2 bytes/element
      ldx #alarmCodes
      leax a,x
      ldd SETC_ALARMCODE,SP
      bsr writeToEE
      leas SETC_VARSIZE,SP    ; skip over variables
      puld                    ; restore registers
      pulx
      puly
      rts
;---------------------------------
; Subroutine: writeToEE()
; Parameters: address - in x register
;             alarmCode    - in d register
; Variables: none
; Description:
;     Write the alarm code in EEProm. writeEEByte() is a 
;     function avaible in Debug12.
;------------------------------------------------------
; Stack Usage
	OFFSET 0 ; to setup offsets into stack
WREE_PR_D DS.W 1	; preserve D - alarmCode
WREE_PR_X DS.W 1	; preserve X - address 
WREE_RA	   DS.W 1	; return address

writeToEE:  pshx
            pshd
            ; Do the first byte
            ldab WREE_PR_D,SP   ;  writeEEByte(address, (byte)((alarmCode&0xff00)>>8) );
            pshd   ; save argument on stack
            tfr x,d ; first argument passed in D
            call [writeEEByte, PCr]
            puld  ; remove argument
            ; Now for the second byte
            ldab WREE_PR_D+1,SP  ; writeEEByte(address+1, (byte)(alarmCode&0xff) );
            pshd  ; save argument on stack
            tfr x,d     ; get address - first argument passed in D
            addd #1 ; address+1
            call [writeEEByte, PCr]
            puld   ; remove argument
            ; All done - time to leave
            puld   ; restore D
            pulx   ; restore X
            rts
        
   switch globalConst
MSTCDMSG    dc.b "Master code",NL,CR,$00
CONFIGMSG   dc.b "a:mstr 1-4:other",NL,CR,$00
CERRMSG     dc.b "Bad entry",NL,CR,$00
GET_CODE_MSG dc.b "Code or 'd'",NL,CR,$00
ERR_MST_MSG dc.b "Cannot disable",NL,CR,$00

