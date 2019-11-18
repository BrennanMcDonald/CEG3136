*
*
*  HC12 i/o register locations (9s12dp256)
*

	ifndef REG9S12	; include only if not yet included

REG9S12	EQU 1	; for testing inclusion of this file
*
Porta:          equ 0   ;port a = address lines a8 - a15
Portb:          equ 1   ;port b = address lines a0 - a7
Ddra:           equ 2   ;port a direction register
Ddrb:           equ 3   ;port a direction register

Porte:          equ 8   ;port e = mode,irqandcontrolsignals
Ddre:           equ 9   ;port e direction register
Pear:           equ $a  ;port e assignments
Mode:           equ $b  ;mode register
Pucr:           equ $c  ;port pull-up control register
Rdriv:          equ $d  ;port reduced drive control register
Ebictl:		equ $e  ;e stretch control

Initrm:         equ $10 ;ram location register
Initrg:         equ $11 ;register location register
Initee:         equ $12 ;eeprom location register
Misc:           equ $13 ;miscellaneous mapping control
Mtst0:          equ $14 ; reserved
Itcr:           equ $15 ;interrupt test control register
Itest:          equ $16 ;interrupt test register
Mtst1:          equ $17 ; reserved

Partidh:		equ $1a ;part id high
Partidl:		equ $1b ;part id low
Memsiz0:		equ $1c ;memory size
Memsiz1:		equ $1d ;memory size
Intcr:          equ $1e ;interrupt control register
Hprio:          equ $1f ;high priority reg

Bkpct0:         equ $28 ;break control register
Bkpct1:         equ $29 ;break control register
Bkp0x:          equ $2a ; break 0 index register
Bkp0h:          equ $2b ; break 0 pointer high
Brp0l:          equ $2c ; break 0 pointer low
Bkp1x:          equ $2d ; break 1 index register
Bkp1h:          equ $2e ; break 1 pointer high
Brp1l:          equ $2f ; break 1 pointer low
Ppage:		equ $30 ;program page register

Portk:		equ $32 ;port k data
Ddrk:			equ $33 ;port k direction
Synr:           equ $34 ; synthesizer / multiplier register
Refdv:          equ $35 ; reference divider register
Ctflg:          equ $36 ; reserved
Crgflg:         equ $37 ; pll flags register
Crgint:         equ $38 ; pll interrupt register
Clksel:         equ $39 ; clock select register
Pllctl:         equ $3a ; pll control register
Rtictl:         equ $3b ;real time interrupt control
Copctl:         equ $3c ;watchdog control
Forbyp:         equ $3d ;
Ctctl:          equ $3e ;
Armcop:         equ $3f ;cop reset register

Tios:           equ $40 ;timer input/output select
Cforc:          equ $41 ;timer compare force
Oc7m:           equ $42 ;timer output compare 7 mask
Oc7d:           equ $43 ;timer output compare 7 data
Tcnt:           equ $44 ;timer counter register hi
*Tcnt:          equ $45 ;timer counter register lo
Tscr:           equ $46 ;timer system control register
Ttov:           equ $47 ;reserved
Tctl1:          equ $48 ;timer control register 1
Tctl2:          equ $49 ;timer control register 2
Tctl3:          equ $4a ;timer control register 3
Tctl4:          equ $4b ;timer control register 4
Tmsk1:          equ $4c ;timer interrupt mask 1
Tmsk2:          equ $4d ;timer interrupt mask 2
Tflg1:          equ $4e ;timer flags 1
Tflg2:          equ $4f ;timer flags 2
Tc0:            equ $50 ;timer capture/compare register 0
Tc1:            equ $52 ;timer capture/compare register 1
Tc2:            equ $54 ;timer capture/compare register 2
Tc3:            equ $56 ;timer capture/compare register 3
Tc4:            equ $58 ;timer capture/compare register 4
Tc5:            equ $5a ;timer capture/compare register 5
Tc6:            equ $5c ;timer capture/compare register 6
Tc7:            equ $5e ;timer capture/compare register 7
Pactl:          equ $60 ;pulse accumulator controls
Paflg:          equ $61 ;pulse accumulator flags
Pacn3:          equ $62 ;pulse accumulator counter 3
Pacn2:          equ $63 ;pulse accumulator counter 2
Pacn1:          equ $64 ;pulse accumulator counter 1
Pacn0:          equ $65 ;pulse accumulator counter 0
Mcctl:          equ $66 ;modulus down conunter control
Mcflg:          equ $67 ;down counter flags
Icpar:          equ $68 ;input pulse accumulator control
Dlyct:          equ $69 ;delay count to down counter
Icovw:          equ $6a ;input control overwrite register
Icsys:          equ $6b ;input control system control

Timtst:         equ $6d ;timer test register

Pbctl:          equ $70 ; pulse accumulator b control
Pbflg:          equ $71 ; pulse accumulator b flags
Pa3h:           equ $72 ; pulse accumulator holding register 3
Pa2h:           equ $73 ; pulse accumulator holding register 2
Pa1h:           equ $74 ; pulse accumulator holding register 1
Pa0h:           equ $75 ; pulse accumulator holding register 0
Mccnt:          equ $76 ; modulus down counter register
*Mccntl:        equ $77 ; low byte
Tcoh:           equ $78 ; capture 0 holding register
Tc1h:           equ $7a ; capture 1 holding register
Tc2h:           equ $7c ; capture 2 holding register
Tc3h:           equ $7e ; capture 3 holding register

Atd0ctl0:       equ $80 ;adc control 0 (reserved)
Atd0ctl1:       equ $81 ;adc control 1 (reserved)
Atd0ctl2:       equ $82 ;adc control 2
Atd0ctl3:       equ $83 ;adc control 3
Atd0ctl4:       equ $84 ;adc control 4
Atd0ctl5:       equ $85 ;adc control 5
Atd0stat:       equ $86 ;adc status register hi
*Atd0stat       equ $87 ;adc status register lo
Atd0test:       equ $88 ;adc test (reserved)
*Atd0test       equ $89 ;

Atd0dien:		equ $8d ;

Portad0:         equ $8f ;port adc = input only
Adr00h:         equ $90 ;adc result 0 register
Adr01h:         equ $92 ;adc result 1 register
Adr02h:         equ $94 ;adc result 2 register
Adr03h:         equ $96 ;adc result 3 register
Adr04h:         equ $98 ;adc result 4 register
Adr05h:         equ $9a ;adc result 5 register
Adr06h:         equ $9c ;adc result 6 register
Adr07h:         equ $9e ;adc result 7 register

Pwme:			equ $a0 ;pwm enable
Pwmpol:         equ $a1 ;pwm polarity
Pwmclk:         equ $a2 ;pwm clock select register
Pwmprclk:       equ $a3 ;pwm prescale clock select register
Pwmcae:         equ $a4 ;pwm center align select register
Pwmctl:         equ $a5 ;pwm control register
Pwmtst:         equ $a6 ;reserved
Pwmprsc:        equ $a7 ;reserved
Pwmscla:        equ $a8 ;pwm scale a
Pwmsclb:        equ $a9 ;pwm scale b
Pwmscnta:       equ $aa ;reserved
Pwmscntb:       equ $ab ;reserved
Pwmcnt0:        equ $ac ;pwm channel 0 counter
Pwmcnt1:        equ $ad ;pwm channel 1 counter
Pwmcnt2:        equ $ae ;pwm channel 2 counter
Pwmcnt3:        equ $af ;pwm channel 3 counter
Pwmcnt4:        equ $b0 ;pwm channel 4 counter
Pwmcnt5:        equ $b1 ;pwm channel 5 counter
Pwmcnt6:        equ $b2 ;pwm channel 6 counter
Pwmcnt7:        equ $b3 ;pwm channel 7 counter
Pwmper0:        equ $b4 ;pwm channel 0 period
Pwmper1:        equ $b5 ;pwm channel 1 period
Pwmper2:        equ $b6 ;pwm channel 2 period
Pwmper3:        equ $b7 ;pwm channel 3 period
Pwmper4:        equ $b8 ;pwm channel 4 period
Pwmper5:        equ $b9 ;pwm channel 5 period
Pwmper6:        equ $ba ;pwm channel 6 period
Pwmper7:        equ $bb ;pwm channel 7 period
Pwmdty0:        equ $bc ;pwm channel 0 duty cycle
Pwmdty1:        equ $bd ;pwm channel 1 duty cycle
Pwmdty2:        equ $be ;pwm channel 2 duty cycle
Pwmdty3:        equ $bf ;pwm channel 3 duty cycle
Pwmdty4:        equ $c0 ;pwm channel 0 duty cycle
Pwmdty5:        equ $c1 ;pwm channel 1 duty cycle
Pwmdty6:        equ $c2 ;pwm channel 2 duty cycle
Pwmdty7:        equ $c3 ;pwm channel 3 duty cycle
Pwmsdn:         equ $c4 ;pwm shutdown register

Sc0bdh:         equ $c8 ;sci 0 baud reg hi byte
Sc0bdl:         equ $c9 ;sci 0 baud reg lo byte
Sc0cr1:         equ $ca ;sci 0 control1 reg
Sc0cr2:         equ $cb ;sci 0 control2 reg
Sc0sr1:         equ $cc ;sci 0 status reg 1
Sc0sr2:         equ $cd ;sci 0 status reg 2
Sc0drh:         equ $ce ;sci 0 data reg hi
Sc0drl:         equ $cf ;sci 0 data reg lo
Sc1bdh:         equ $d0 ;sci 1 baud reg hi byte
Sc1bdl:         equ $d1 ;sci 1 baud reg lo byte
Sc1cr1:         equ $d2 ;sci 1 control1 reg
Sc1cr2:         equ $d3 ;sci 1 control2 reg
Sc1sr1:         equ $d4 ;sci 1 status reg 1
Sc1sr2:         equ $d5 ;sci 1 status reg 2
Sc1drh:         equ $d6 ;sci 1 data reg hi
Sc1drl:         equ $d7 ;sci 1 data reg lo
Spi0cr1:        equ $d8 ;spi 0 control1 reg
Spi0cr2:        equ $d9 ;spi 0 control2 reg
Spi0br:         equ $da ;spi 0 baud reg
Spi0sr:         equ $db ;spi 0 status reg hi

Sp0dr:          equ $dd ;spi 0 data reg

Ibad:		equ $e0 ;i2c bus address register
Ibfd:		equ $e1 ;i2c bus frequency divider
Ibcr:		equ $e2 ;i2c bus control register
Ibsr:		equ $e3 ;i2c bus status register
Ibdr:		equ $e4 ;i2c bus message data register

Dlcbcr1:	equ $e8 ;bdlc control regsiter 1
Dlcbsvr:	equ $e9 ;bdlc state vector register
Dlcbcr2:	equ $ea ;bdlc control register 2
Dlcbdr:		equ $eb ;bdlc data register
Dlcbard:	equ $ec ;bdlc analog delay register
Dlcbrsr:	equ $ed ;bdlc rate select register
Dlcscr:		equ $ee ;bdlc control register
Dlcbstat:	equ $ef ;bdlc status register
Spi1cr1:        equ $f0 ;spi 1 control1 reg
Spi1cr2:        equ $f1 ;spi 1 control2 reg
Spi1br:         equ $f2 ;spi 1 baud reg
Spi1sr:         equ $f3 ;spi 1 status reg hi

Sp1dr:          equ $f5 ;spi 1 data reg

Spi2cr1:        equ $f8 ;spi 2 control1 reg
Spi2cr2:        equ $f9 ;spi 2 control2 reg
Spi2br:         equ $fa ;spi 2 baud reg
Spi2sr:         equ $fb ;spi 2 status reg hi

Sp2dr:          equ $fd ;spi 2 data reg

Fclkdiv:	equ $100 ;flash clock divider
Fsec:		equ $101 ;flash security register

Fcnfg:		equ $103 ;flash configuration register
Fprot:		equ $104 ;flash protection register
Fstat:		equ $105 ;flash status register
Fcmd:		equ $106 ;flash command register

Eclkdiv:	equ $110 ;eeprom clock divider

Ecnfg:		equ $113 ;eeprom configuration register
Eprot:		equ $114 ;eeprom protection register
Estat:		equ $115 ;eeprom status register
Ecmd:		equ $116 ;eeprom command register

Atd1ctl0:       equ $120 ;adc1 control 0 (reserved)
Atd1ctl1:       equ $121 ;adc1 control 1 (reserved)
Atd1ctl2:       equ $122 ;adc1 control 2
Atd1ctl3:       equ $123 ;adc1 control 3
Atd1ctl4:       equ $124 ;adc1 control 4
Atd1ctl5:       equ $125 ;adc1 control 5
Atd1stat:       equ $126 ;adc1 status register hi
*Atd1stat       equ $127 ;adc1 status register lo
Atd1test:       equ $128 ;adc1 test (reserved)
*Atd1test       equ $129 ;

Atd1dien:	equ $12d ;adc1 input enable register

Portad1:        equ $12f ;port adc1 = input only
Adr10h:         equ $130 ;adc1 result 0 register
Adr11h:         equ $132 ;adc1 result 1 register
Adr12h:         equ $134 ;adc1 result 2 register
Adr13h:         equ $136 ;adc1 result 3 register
Adr14h:         equ $138 ;adc1 result 4 register
Adr15h:         equ $13a ;adc1 result 5 register
Adr16h:         equ $13c ;adc1 result 6 register
Adr17h:         equ $13e ;adc1 result 7 register
Can0ctl0:	equ $140 ;can0 control register 0
Can0ctl1:	equ $141 ;can0 control register 1
Can0btr0:	equ $142 ;can0 bus timing register 0
Can0btr1:	equ $143 ;can0 bus timing register 1
Can0rflg:	equ $144 ;can0 receiver flags
Can0rier:	equ $145 ;can0 receiver interrupt enables
Can0tflg:	equ $146 ;can0 transmit flags
Can0tier:	equ $147 ;can0 transmit interrupt enables
Can0tarq:	equ $148 ;can0 transmit message abort control
Can0taak:	equ $149 ;can0 transmit message abort status
Can0tbel:	equ $14a ;can0 transmit buffer select
Can0idac:	equ $14b ;can0 identfier acceptance control

Can0rerr:	equ $14e ;can0 receive error counter
Can0terr:	equ $14f ;can0 transmit error counter
Can0ida0:	equ $150 ;can0 identifier acceptance register 0
Can0ida1:	equ $151 ;can0 identifier acceptance register 1
Can0ida2:	equ $152 ;can0 identifier acceptance register 2
Can0ida3:	equ $153 ;can0 identifier acceptance register 3
Can0idm0:	equ $154 ;can0 identifier mask register 0
Can0idm1:	equ $155 ;can0 identifier mask register 1
Can0idm2:	equ $156 ;can0 identifier mask register 2
Can0idm3:	equ $157 ;can0 identifier mask register 3
Can0ida4:	equ $158 ;can0 identifier acceptance register 4
Can0ida5:	equ $159 ;can0 identifier acceptance register 5
Can0ida6:	equ $15a ;can0 identifier acceptance register 6
Can0ida7:	equ $15b ;can0 identifier acceptance register 7
Can0idm4:	equ $15c ;can0 identifier mask register 4
Can0idm5:	equ $15d ;can0 identifier mask register 5
Can0idm6:	equ $15e ;can0 identifier mask register 6
Can0idm7:	equ $15f ;can0 identifier mask register 7
Can0rxfg:	equ $160 ;can0 rx foreground buffer thru +$16f
Can0txfg:	equ $170 ;can0 tx foreground buffer thru +$17f

Can1ctl0:	equ $180 ;can1 control register 0
Can1ctl1:	equ $181 ;can1 control register 1
Can1btr0:	equ $182 ;can1 bus timing register 0
Can1btr1:	equ $183 ;can1 bus timing register 1
Can1rflg:	equ $184 ;can1 receiver flags
Can1rier:	equ $185 ;can1 receiver interrupt enables
Can1tflg:	equ $186 ;can1 transmit flags
Can1tier:	equ $187 ;can1 transmit interrupt enables
Can1tarq:	equ $188 ;can1 transmit message abort control
Can1taak:	equ $189 ;can1 transmit message abort status
Can1tbel:	equ $18a ;can1 transmit buffer select
Can1idac:	equ $18b ;can1 identfier acceptance control

Can1rerr:	equ $18e ;can1 receive error counter
Can1terr:	equ $18f ;can1 transmit error counter
Can1ida0:	equ $190 ;can1 identifier acceptance register 0
Can1ida1:	equ $191 ;can1 identifier acceptance register 1
Can1ida2:	equ $192 ;can1 identifier acceptance register 2
Can1ida3:	equ $193 ;can1 identifier acceptance register 3
Can1idm0:	equ $194 ;can1 identifier mask register 0
Can1idm1:	equ $195 ;can1 identifier mask register 1
Can1idm2:	equ $196 ;can1 identifier mask register 2
Can1idm3:	equ $197 ;can1 identifier mask register 3
Can1ida4:	equ $198 ;can1 identifier acceptance register 4
Can1ida5:	equ $199 ;can1 identifier acceptance register 5
Can1ida6:	equ $19a ;can1 identifier acceptance register 6
Can1ida7:	equ $19b ;can1 identifier acceptance register 7
Can1idm4:	equ $19c ;can1 identifier mask register 4
Can1idm5:	equ $19d ;can1 identifier mask register 5
Can1idm6:	equ $19e ;can1 identifier mask register 6
Can1idm7:	equ $19f ;can1 identifier mask register 7
Can1rxfg:	equ $1a0 ;can1 rx foreground buffer thru +$1af
Can1txfg:	equ $1b0 ;can1 tx foreground buffer thru +$1bf

Can2ctl0:	equ $1c0 ;can2 control register 0
Can2ctl1:	equ $1c1 ;can2 control register 1
Can2btr0:	equ $1c2 ;can2 bus timing register 0
Can2btr1:	equ $1c3 ;can2 bus timing register 1
Can2rflg:	equ $1c4 ;can2 receiver flags
Can2rier:	equ $1c5 ;can2 receiver interrupt enables
Can2tflg:	equ $1c6 ;can2 transmit flags
Can2tier:	equ $1c7 ;can2 transmit interrupt enables
Can2tarq:	equ $1c8 ;can2 transmit message abort control
Can2taak:	equ $1c9 ;can2 transmit message abort status
Can2tbel:	equ $1ca ;can2 transmit buffer select
Can2idac:	equ $1cb ;can2 identfier acceptance control

Can2rerr:	equ $1ce ;can2 receive error counter
Can2terr:	equ $1cf ;can2 transmit error counter
Can2ida0:	equ $1d0 ;can2 identifier acceptance register 0
Can2ida1:	equ $1d1 ;can2 identifier acceptance register 1
Can2ida2:	equ $1d2 ;can2 identifier acceptance register 2
Can2ida3:	equ $1d3 ;can2 identifier acceptance register 3
Can2idm0:	equ $1d4 ;can2 identifier mask register 0
Can2idm1:	equ $1d5 ;can2 identifier mask register 1
Can2idm2:	equ $1d6 ;can2 identifier mask register 2
Can2idm3:	equ $1d7 ;can2 identifier mask register 3
Can2ida4:	equ $1d8 ;can2 identifier acceptance register 4
Can2ida5:	equ $1d9 ;can2 identifier acceptance register 5
Can2ida6:	equ $1da ;can2 identifier acceptance register 6
Can2ida7:	equ $1db ;can2 identifier acceptance register 7
Can2idm4:	equ $1dc ;can2 identifier mask register 4
Can2idm5:	equ $1dd ;can2 identifier mask register 5
Can2idm6:	equ $1de ;can2 identifier mask register 6
Can2idm7:	equ $1df ;can2 identifier mask register 7
Can2rxfg:	equ $1e0 ;can2 rx foreground buffer thru +$1ef
Can2txfg:	equ $1f0 ;can2 tx foreground buffer thru +$1ff

Can3ctl0:	equ $200 ;can3 control register 0
Can3ctl1:	equ $201 ;can3 control register 1
Can3btr0:	equ $202 ;can3 bus timing register 0
Can3btr1:	equ $203 ;can3 bus timing register 1
Can3rflg:	equ $204 ;can3 receiver flags
Can3rier:	equ $205 ;can3 receiver interrupt enables
Can3tflg:	equ $206 ;can3 transmit flags
Can3tier:	equ $207 ;can3 transmit interrupt enables
Can3tarq:	equ $208 ;can3 transmit message abort control
Can3taak:	equ $209 ;can3 transmit message abort status
Can3tbel:	equ $20a ;can3 transmit buffer select
Can3idac:	equ $20b ;can3 identfier acceptance control

Can3rerr:	equ $20e ;can3 receive error counter
Can3terr:	equ $20f ;can3 transmit error counter
Can3ida0:	equ $210 ;can3 identifier acceptance register 0
Can3ida1:	equ $211 ;can3 identifier acceptance register 1
Can3ida2:	equ $212 ;can3 identifier acceptance register 2
Can3ida3:	equ $213 ;can3 identifier acceptance register 3
Can3idm0:	equ $214 ;can3 identifier mask register 0
Can3idm1:	equ $215 ;can3 identifier mask register 1
Can3idm2:	equ $216 ;can3 identifier mask register 2
Can3idm3:	equ $217 ;can3 identifier mask register 3
Can3ida4:	equ $218 ;can3 identifier acceptance register 4
Can3ida5:	equ $219 ;can3 identifier acceptance register 5
Can3ida6:	equ $21a ;can3 identifier acceptance register 6
Can3ida7:	equ $21b ;can3 identifier acceptance register 7
Can3idm4:	equ $21c ;can3 identifier mask register 4
Can3idm5:	equ $21d ;can3 identifier mask register 5
Can3idm6:	equ $21e ;can3 identifier mask register 6
Can3idm7:	equ $21f ;can3 identifier mask register 7
Can3rxfg:	equ $220 ;can3 rx foreground buffer thru +$22f
Can3txfg:	equ $230 ;can3 tx foreground buffer thru +$23f

Ptt:		equ $240 ;portt data register
Ptit:		equ $241 ;portt input register
Ddrt:		equ $242 ;portt direction register
Rdrt:		equ $243 ;portt reduced drive register
Pert:		equ $244 ;portt pull device enable
Ppst:		equ $245 ;portt pull polarity select

Pts:		equ $248 ;ports data register
Ptis:		equ $249 ;ports input register
Ddrs:		equ $24a ;ports direction register
Rdrs:		equ $24b ;ports reduced drive register
Pers:		equ $24c ;ports pull device enable
Ppss:		equ $24d ;ports pull polarity select
Woms:		equ $24e ;ports wired or mode register

Ptm:		equ $250 ;portm data register
Ptim:		equ $251 ;portm input register
Ddrm:		equ $252 ;portm direction register
Rdrm:		equ $253 ;portm reduced drive register
Perm:		equ $254 ;portm pull device enable
Ppsm:		equ $255 ;portm pull polarity select
Womm:		equ $256 ;portm wired or mode register
Modrr:		equ $257 ;portm module routing register
Ptp:		equ $258 ;portp data register
Ptip:		equ $259 ;portp input register
Ddrp:		equ $25a ;portp direction register
Rdrp:		equ $25b ;portp reduced drive register
Perp:		equ $25c ;portp pull device enable
Ppsp:		equ $25d ;portp pull polarity select
Piep:		equ $25e ;portp interrupt enable register
Pifp:		equ $25f ;portp interrupt flag register
Pth:		equ $260 ;porth data register
Ptih:		equ $261 ;porth input register
Ddrh:		equ $262 ;porth direction register
Rdrh:		equ $263 ;porth reduced drive register
Perh:		equ $264 ;porth pull device enable
Ppsh:		equ $265 ;porth pull polarity select
Pieh:		equ $266 ;porth interrupt enable register
Pifh:		equ $267 ;porth interrupt flag register
Ptj:		equ $268 ;portp data register
Ptij:		equ $269 ;portp input register
Ddrj:		equ $26a ;portp direction register
Rdrj:		equ $26b ;portp reduced drive register
Perj:		equ $26c ;portp pull device enable
Ppsj:		equ $26d ;portp pull polarity select
Piej:		equ $26e ;portp interrupt enable register
Pifj:		equ $26f ;portp interrupt flag register

Can4ctl0:	equ $280 ;can4 control register 0
Can4ctl1:	equ $281 ;can4 control register 1
Can4btr0:	equ $282 ;can4 bus timing register 0
Can4btr1:	equ $283 ;can4 bus timing register 1
Can4rflg:	equ $284 ;can4 receiver flags
Can4rier:	equ $285 ;can4 receiver interrupt enables
Can4tflg:	equ $286 ;can4 transmit flags
Can4tier:	equ $287 ;can4 transmit interrupt enables
Can4tarq:	equ $288 ;can4 transmit message abort control
Can4taak:	equ $289 ;can4 transmit message abort status
Can4tbel:	equ $28a ;can4 transmit buffer select
Can4idac:	equ $28b ;can4 identfier acceptance control

Can4rerr:	equ $28e ;can4 receive error counter
Can4terr:	equ $28f ;can4 transmit error counter
Can4ida0:	equ $290 ;can4 identifier acceptance register 0
Can4ida1:	equ $291 ;can4 identifier acceptance register 1
Can4ida2:	equ $292 ;can4 identifier acceptance register 2
Can4ida3:	equ $293 ;can4 identifier acceptance register 3
Can4idm0:	equ $294 ;can4 identifier mask register 0
Can4idm1:	equ $295 ;can4 identifier mask register 1
Can4idm2:	equ $296 ;can4 identifier mask register 2
Can4idm3:	equ $297 ;can4 identifier mask register 3
Can4ida4:	equ $298 ;can4 identifier acceptance register 4
Can4ida5:	equ $299 ;can4 identifier acceptance register 5
Can4ida6:	equ $29a ;can4 identifier acceptance register 6
Can4ida7:	equ $29b ;can4 identifier acceptance register 7
Can4idm4:	equ $29c ;can4 identifier mask register 4
Can4idm5:	equ $29d ;can4 identifier mask register 5
Can4idm6:	equ $29e ;can4 identifier mask register 6
Can4idm7:	equ $29f ;can4 identifier mask register 7
Can4rxfg:	equ $2a0 ;can4 rx foreground buffer thru +$2af
Can4txfg:	equ $2b0 ;can4 tx foreground buffer thru +$2bf

* end registers

	endif   ; end of conditional assembly