;------------------------------------------------------
; Alarm System Assembler Program
; File: armed.asm
; Description: The Armed Module
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------

        SWITCH code_section
ARMDELAY  equ 3000; 15000
BEEPDELAY equ 1000

;-------------------------------------------
; Subroutine: enableAlarm
; Parameters: none
; Returns: nothing
; Variables
;       input, codeValid, delayFlag - on stack
; Description:
;     Gets user to enter a valid alarm code to arm
;     the alarm system.  Delays 15 seconds (to allow user
;     to leave; the alarm can be disarmed during this period),
;     monitors for trigger events (a, b, c, d, e).  When 'a'
;     is detected, 15 seconds are allowed to enter an alarm code to
;     disarm the system; otherwise the alarm is triggered. For other
;     trigger events, the alarm is triggered instantly.  The alarm
;     system can be turned off after being triggered with an alarm
;     code.
;------------------------------------------------------
; Stack Usage:
	OFFSET 0  ; to setup offset into stack
EAL_INPUT      DS.B 1  ; input
EAL_CODEVALID  DS.B 1 ; codeValid
EAL_DELAYFLAG  DS.B 1 ; delayFlag
EAL_VARSIZE:
EAL_PR_D	      DS.W 1 ; preserve D
EAL_RA         DS.W 1 ; return address

enableAlarm:  pshd
   leas  -EAL_VARSIZE,SP        ;byte input;  // input from user
                                ;byte codeValid;  // valid alarm code found
                                ;byte delayFlag;
   ;// Get a valid alarm code to arm the system
   ldd #CODEMSG                 ; printf(CODEMSG);
   jsr [printf, PCr]
   movb #FALSE,EAL_CODEVALID,SP ; codeValid = FALSE;
eal_while1:
   tst EAL_CODEVALID,SP         ; while(!codeValid) 
   bne eal_endwhile1            ; {
   jsr readKey                  ;   input = readKey();
   stab EAL_INPUT,SP
   tba
   jsr checkCode                ;     codeValid = checkCode(input);
   staa EAL_CODEVALID,SP
   bra eal_while1
eal_endwhile1                   ; }

   ldd #ARMING                   ; printf(ARMING);
   jsr [printf,PCr]
   ; // Delay 1500 ms, i.e. 15 seconds
   ldd #ARMDELAY                 ; setDelay(ARMDELAY);
   jsr setDelay
   movb #FALSE,EAL_CODEVALID,SP ; codeValid = FALSE;
   movb #FALSE,EAL_DELAYFLAG,SP ; delayFlag = FALSE;
eal_while2:                     ; while(!delayFlag) 
   tst EAL_DELAYFLAG,SP         ; {
   bne eal_endwhile2
   jsr polldelay                ;   delayFlag = delay(); 
   staa EAL_DELAYFLAG,SP
   jsr pollreadKey              ;   input = pollreadKey();  // check if code entered to disarm
   stab EAL_INPUT,SP
   tba
eal_if1:
   cmpa #'#'                    ;   if(isdigit(input) || input == '#') 
   beq eal_blk1
   jsr isdigit
   tsta
   bne eal_blk1
   bra eal_endif1   
eal_blk1:                       ;    {
   ldaa EAL_INPUT,SP            
   jsr checkCode                ;        codeValid = checkCode(input);
   staa EAL_CODEVALID,SP
eal_if2:
   tsta                         ;        if(codeValid) 
   beq eal_endif2
   movb #TRUE,EAL_DELAYFLAG,SP  ;            delayFlag = TRUE;  // break out of loop
eal_endif2:
eal_endif1:                     ;    }
   bra eal_while2               
eal_endwhile2                   ; }

   ;// Loop to monitor trigger events and alarm code to disable
   ;// codeValid is TRUE if valid alarm code entered during delay
eal_if3:			; if(!codeValid)
   tst EAL_CODEVALID,SP
   bne eal_endif3
   ldd #ARMED                   ;        printf(ARMED)
   jsr [printf, PCr]
eal_endif3:
eal_while3                      ;  while(!codeValid)
   tst EAL_CODEVALID,SP         ; {
   bne eal_endwhile3
   jsr pollReadKey              ;    input = pollReadKey();
   stab EAL_INPUT,SP
   tba
eal_elseif
   cmpa #'#'                    ;    if(isdigit(input) || input == '#') 
   beq eal_blk2
   jsr isdigit
   tsta
   bne eal_blk2
   bra eal_elseifA  
eal_blk2:      
   ldaa EAL_INPUT,SP             ;        codeValid = checkCode(input);
   bsr checkCode                
   staa EAL_CODEVALID,SP 
   bra eal_endelseif    
eal_elseifA:
   jsr getSwStatus               ;   else if(getSwStatus() & 0b00000001) // Front door opened
   anda #%00000001
   beq eal_elseifB               ;   {
   ldd #DISARMING                ;      printf(DISARMING);
   jsr [printf, PCr]
   ldd #ARMDELAY                 ;      setDelay(ARMDELAY);
   jsr setDelay
eal_while4:                      ;      while(!codeValid)
   ldaa EAL_CODEVALID,SP         ;      {
   bne eal_endwhile4 
eal_if4:
   jsr pollDelay                 ;         if(pollDelay())
   tsta  
   beq eal_else4                 ;         { 
   jsr triggerAlarm              ;            triggerAlarm();
   movb #TRUE,EAL_CODEVALID,SP   ;            codeValid = TRUE;           
   bra eal_endif4                ;         }
eal_else4                        ;         else {
   jsr pollReadKey               ;            input = pollReadKey();  // check if alarm code entered to disarm
   stab EAL_INPUT,SP
eal_if5:
   tba                           ;            if(isdigit(input) || input == '#')
   cmpa #'#' 
   beq eal_blk3
   jsr isdigit
   tsta
   bne eal_blk3
   bra eal_endif5   
eal_blk3:  
   ldaa EAL_INPUT,SP
   bsr checkCode                ;                 codeValid = checkCode(input);
   staa EAL_CODEVALID,SP 
eal_endif5:
eal_endif4:                     ;          }
   bra eal_while4
eal_endwhile4:                  ;        }
eal_endelseifA                  ;      }
   bra eal_endelseif;      
eal_elseifB:
   jsr getSwStatus              ;      else if(getSwStatus() & 0b11111110) // other door/window opened
   anda #%11111110              ;      
   beq eal_endelseifB           ;      {
   jsr triggerAlarm             ;          triggerAlarm();
   movb #TRUE,EAL_CODEVALID,SP  ;          codeValid = TRUE;
eal_endelseifB:                 ;      }
   ;    // ignore all other input
eal_endelseif:
    bra eal_while3
eal_endwhile3                   ; }
    leas EAL_VARSIZE,SP
    puld
    rts


;------------------------------------------------------
; Subroutine: checkCode
; Parameters: input - accumulator A
; Returns: TRUE when a valid alarm code is detected, FALSE otherwise - stored in 
;          accumulator A
; Local Variables: retval - on stack
; Global Variables:
;       mult - initilased to 1000 in inithw (Alarm System Module)
;       alarmCode - initialised to 0 in inithw (Alarm System Module)
; Descriptions: Creates alarm code using digits entered until
;               4 digits are seen. After 4th digit, see if
;               alarm code is valid using isCodeValid().
;------------------------------------------------------
; Stack usage
	OFFSET 0
CKC_INPUT  DS.B 1 ; parameter input
CKC_RETVAL DS.B 1 ; variable retval
CKC_VARSIZE
CKC_PR_B	  DS.B 1 ; preserve B
CKC_PR_X   DS.W 1 ; preserve X
CKC_PR_Y   DS.W 1 ; preserve Y
CKC_RA	  DS.W 1 ; return address

checkCode: pshy
   pshx
   pshb
   leas -CKC_VARSIZE,SP       
                              ; static int mult = 1000; // current multiplier of digit
                              ; static int alarmCode = 0;   // alarm code value
   movb #FALSE,CKC_RETVAL,SP  ; byte retval = FALSE;
   staa CKC_INPUT,SP          ; save paramater value
   
   jsr isdigit                ; if(isdigit(input))
   tsta
   beq ckc_else               ; {
   ldaa CKC_INPUT,SP          ;    alarmCode = alarmCode + (input-ASCII_CONV_NUM)*mult
   suba #ASCII_CONV_NUM
   tab                        
   clra
   ldy mult
   emul                       ; //*mult - result in D
   addd alarmCode
   std alarmCode
   ldd mult		      ;    mult = mult/10;
   ldx #10
   idiv
   stx mult
   ldd mult                   ;    if(mult == 0) 
   bne ckc_endif1             ;    {
   ldd alarmcode              ;
   bsr isCodeValid            ;       retval = isCodeValid(alarmCode);
   staa CKC_RETVAL,SP
   ldd #0                     ;       alarmCode = 0;
   std alarmCode 
   ldd #1000                  ;       mult = 1000;
   std mult     
ckc_endif1:                   ;     }
   bra ckc_endif              ; }
ckc_else:                     ; else {
   ldd #0                     ;       alarmCode = 0;
   std alarmCode 
   ldd #1000                  ;       mult = 1000;
   std mult                   ; }
ckc_endif:
   
   ldaa CKC_RETVAL,SP         ; return(retval);
   ; Restore registers and stack
   leas CKC_VARSIZE,SP
   pulb
   pulx
   puly
   rts      


;------------------------------------------------------
; Subroutine: isCodeValid
; Parameters: alarmCode stored in register D
; Local Variables
;   ptr - pointer to array - in register X
;   cnt, retval - on the stack.
; Returns: TRUE/FALSE - Returned in accumulator A 
; Description: Checks to see if alarm code is in the
;              alarmCodes array.
;------------------------------------------------------

; Stack usage
	OFFSET 0
CDV_ALARMCODE   DS.W 1 ; alarmCode
CDV_CNT    DS.B 1 ; cnt
CDV_RETVAL DS.B 1 ; retval
CDV_VARSIZE:
CDV_PR_X   DS.W 1 ; preserve x register
CDV_RA     DS.W 1 ; return address

isCodeValid: pshx
   leas -CDV_VARSIZE,SP
   std CDV_ALARMCODE,SP
   ; int *ptr;  // pointer to alarmCodes
   movb #NUMCODES,CDV_CNT,SP ; byte cnt = 5;
   movb #FALSE,CDV_RETVAL,SP ; byte retval = FALSE;
   ldx #alarmCodes           ; ptr = alarmCodes;
cdv_while                    ; do
   ldd 2,X+                  ; {
   cpd CDV_ALARMCODE,SP      ;    if(*ptr++ == alarmCode)
   bne cdv_endif             ;    {
   movb #TRUE,CDV_RETVAL,SP  ;      retval = TRUE;
   bra cdv_endwhile          ;      break;
cdv_endif:                   ;    }
   dec CDV_CNT,SP            ;   cnt--;
   bne cdv_while             ; } while(cnt != 0); 
cdv_endwhile:
   ldaa CDV_RETVAL,SP         ;   return(retval);
   ; restore registers and stack
   leas CDV_VARSIZE,SP 
   pulx
   rts

;----------------------------
; Subroutine: triggerAlarm
; Parameters: none
; Returns: nothing
; Local Variables: retval, dobel, input - on stack
; Description: Repeatedly sends a bel character to the
;              terminal until a valid alarm code is entered.
;----------------------------
; Stack usage
	OFFSET 0
TRA_DONE   DS.W 1 ; done
TRA_DONEINPUT  DS.B 1 ; doneInput
TRA_INPUT  DS.B 1 ; input
TRA_VARSIZE:
TRA_PR_D   DS.W 1 ; preserve D register
TRA_RA     DS.W 1 ; return address

triggerAlarm: pshd
   leas -TRA_VARSIZE,SP
   movb #FALSE,TRA_DONE,SP   ; byte done = FALSE;
                             ; byte dobel;
                             ; byte input;
tra_while:                   ; while(!done)
   tst TRA_DONE,SP         ; {
   bne tra_endwhile
   ldb #BEL                  ;    putchar(BEL);
   clra
   jsr [putchar, PCr]
   ldd #BEEPDELAY            ;    setDelay(BEEPDELAY);   // 1 sec between beeps
   jsr setDelay
   movb #FALSE,TRA_DONEINPUT,SP ; doneInput = FALSE;
tra_while2:                  ;    while(!doneInput) 
   tst TRA_DONEINPUT,SP      ;    {
   bne tra_endwhile2
   jsr polldelay             ;       doneInput = delay();
   staa TRA_DONEINPUT,SP
   jsr pollReadKey           ;       input = pollReadKey();  // check if code entered to disarm
   stab TRA_INPUT,SP
   tba
   cmpa #'#'                 ;       if(isdigit(input) || input == '#') 
   beq tra_blk1
   jsr isdigit
   tsta
   bne tra_blk1
   bra tra_endif   
tra_blk1:
   ldaa TRA_INPUT,SP
   jsr checkCode             ;                done = checkCode(input);
   staa TRA_DONE,SP 
tra_endif: 
   bra tra_while2
tra_endwhile2                ;    }
   bra tra_while
tra_endwhile                 ; }
   leas TRA_VARSIZE,SP
   puld
   rts

;-------------------------------------------------------------------------
; Data Structures
;-------------------------------------------------------------------------
	SWITCH globalConst
; Message strings
CODEMSG dc.b  "Code",NL,CR,$00
ARMING  dc.b  "*** Arming ***",NL,CR,$00
ARMED	dc.b  "*** Armed ***",NL,CR,$00
DISARMING dc.b  "-- Disarming --",NL,CR,$00

   switch globalVar
mult dc.w 1000
alarmCode dc.w 0
