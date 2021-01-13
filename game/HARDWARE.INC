
;GTIA ==============================
GTIA	= $D000
HPOSP=$D000 ; 53248 ; horizontal position player
HPOSP0	= $D000
HPOSP1	= $D001
HPOSP2	= $D002
HPOSP3	= $D003

HPOSM=53252 ; horizontal position missiles
HPOSM0	= $D004
HPOSM1	= $D005
HPOSM2	= $D006
HPOSM3	= $D007

SIZEP = $D008
SIZEP0	= $D008
SIZEP1	= $D009
SIZEP2	= $D00A
SIZEP3	= $D00B

SIZEM	= $D00C

GRAFP0	= $D00D
GRAFP1	= $D00E
GRAFP2	= $D00F
GRAFP3	= $D010

GRAFM	= $D011

COLPM=$D012
COLPM0	= $D012
COLPM1	= $D013
COLPM2	= $D014
COLPM3	= $D015

COLPF=$D016
COLPF0	= $D016
COLPF1	= $D017
COLPF2	= $D018
COLPF3	= $D019

COLBAK	= $D01A

COLBK	= $D01A 	;alias of COLBAK

PRIOR	= $D01B

VDELAY	= $D01C
GRACTL	= $D01D
HITCLR	= $D01E
CONSOL	= $D01F

; collisions
M0PF	= $D000
M1PF	= $D001
M2PF	= $D002
M3PF	= $D003

P0PF	= $D004
P1PF	= $D005
P2PF	= $D006
P3PF	= $D007

M0PL	= $D008
M1PL	= $D009
M2PL	= $D00A
M3PL	= $D00B

P0PL	= $D00C
P1PL	= $D00D
P2PL	= $D00E
P3PL	= $D00F

TRIG0	= $D010
TRIG1	= $D011
TRIG2	= $D012
TRIG3	= $D013

PAL	= $D014 ; 53268 ; 1=PAL, $E=NTSC

;Pokey ==============================
POKEY	= $D200

AUDF1	= $D200
AUDF2	= $D202
AUDF3	= $D204
AUDF4	= $D206

AUDC1	= $D201
AUDC2	= $D203
AUDC3	= $D205
AUDC4	= $D207

POT0	= $D200
POT1	= $D201
POT2	= $D202
POT3	= $D203
POT4	= $D204
POT5	= $D205
POT6	= $D206
POT7	= $D207

AUDCTL	= $D208
ALLPOT	= $D208
POTST	= $D208

STIMER	= $D209

KBCODE	= $D209

SKRES	= $D20A
RANDOM	= $D20A
POTGO	= $D20B
SEROUT	= $D20D
SERIN	= $D20D
IRQEN	= $D20E
IRQST	= $D20E
SKCTL	= $D20F
SKSTAT	= $D20F

;PIA ==============================
PIA	= $D300
PORTA	= $D300
PORTB	= $D301
PACTL	= $D302
PBCTL	= $D303

;ANTIC ==============================
ANTIC	= $D400

DMACTL	= $D400
CHACTL	= $D401 ; page to character list

DLISTL	= $D402
DLISTH	= $D403

HSCROL	= $D404

VSCROL	= $D405

PMBASE	= $D407

CHBASE	= $D409

WSYNC	= $D40A ;54282  ; insert value, hold on the 6502-CPU until next line

VCOUNT	= $D40B ; 54283 ; vertical screen line / 2 at PAL 0-155, NTSC 0-131

PENH	= $D40C
PENV	= $D40D

NMIEN	= $D40E
NMIRES	= $D40F
NMIST	= $D40F

;ANTIC display list commands
DL_E1	= $00
DL_E2	= $10
DL_E3	= $20
DL_E4	= $30
DL_E5	= $40
DL_E6	= $50
DL_E7	= $60
DL_E8	= $70

DL_JUMP	= $01 	;jump to adress and create one empty line
DL_LOOP	= $41 	;jump to adress and wait for vsync
DL_ADDRES	= $40 	;load memory counter
DL_DLI	= $80 	;dli interrupt
DL_HS	= $10 	;horizontal scroll
DL_VS	= $20 	;vertical scroll

;BASIC XL GR-codes:
DL_GR0	= $02 	;text hi-res mode 40 bytes/line
DL_A3	  = $03 	;hi-res text mode 8x10 pixel char, 40 bytes/line
DL_GR12 = $04 	;text - 4+1 color, 1 line V
DL_GR13 = $05 	;text - 4+1 color, 2 line V
DL_GR1	= $06 	;4 color text mode 20 bytes/line, 1 line V
DL_GR2	= $07 	;4 color text mode 20 bytes/line, 2 line V

DL_GR3	= $08 	;4 color graphics mode 10 bytes/line, 8 line V
DL_GR4	= $09 	;1 color graphics mode 10 bytes/line, 4 line V
DL_GR5	= $0A 	;4 color graphics mode, 20 bytes/line, 4 line V
DL_GR6	= $0B 	;1 color graphics mode, 20 bytes/line, 2 line V
DL_GR14	= $0C 	;1 color graphics mode, 20 bytes/line, 1 line V
DL_GR7	= $0D 	;4 color graphics mode, 40 bytes/line, 2 line V
DL_GR15	= $0E 	;4 color graphics mode, 40 bytes/line, 1 line V
DL_GR8	= $0F 	;graphics hi-res mode 40 bytes/line

DL_GR9	= $0F 	;graphics hi-res mode 40 bytes/line PRIOR=$40
DL_GR10	= $0F 	;graphics hi-res mode 40 bytes/line PRIOR=$80
DL_GR11	= $0F 	;graphics hi-res mode 40 bytes/line PRIOR=$C0



