;**************************************************************
;* LBE_Dragon12_Plus_Rev3                                     *
;* Assembly language routines for C function calls            *
;* Learning By Example Using C                                *
;* -- Programming the Dragon12-Plus Using CodeWarrior         *
;* by Richard E. Haskell                                      *
;* Copyright 2008                                             *
;**************************************************************


; export symbols
            XDEF asm_main, PLL_init

; include derivative specific macros
            INCLUDE 'mc9s12dg256.inc'

; code section
MyCode:     SECTION

asm_main:

PLL_init:
          movb    #$02,SYNR         ;PLLOSC = 48 MHz
          movb    #$00,REFDV
          clr     CLKSEL
          movb    #$F1,PLLCTL
pll1:     brclr   CRGFLG,#$08,pll1  ;wait for PLL to lock
          movb    #$80,CLKSEL       ;select PLLCLK
          rts

