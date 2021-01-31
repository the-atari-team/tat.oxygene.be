; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;RUNTIME-Library

  .LOCAL

; Here the most important addresses only

POKMSK=16
; bit dec hex
;   7 128 $80 - Breakkey is possible (BRKKY: 566,567)
;   6  64 $40 - key interrupt possible
;   2   4 $04 - Interrupt 4. pokey timer is possible
;   1   2 $02 - Interrupt 2. pokey timer is possible
;   0   1 $01 - Interrupt 1. pokey timer is possible

BRKKEY=17
RTCLOK=18 ; 18,19,20 Timer will increase every 1/50s (PAL)

STATUS=48

CHKSUM=49

SOUNDR=65 ; 0 means no sound at disk IO

CRITIC=66 ; !0 means no second VBI (faster ~50000 cycles less)

ERRNO=73

ATRACT=77 ; will increment every 5s, >128 color switch begin

; Addresses from 80 - 122 will used by screen editor
TMPCHR=80
HOLD1=81
LMARGN=82 ; left start position
RMARGN=83 ; right margin

ROWCRS=84 ; row position of the cursor
COLCRS=85 ; 85,86 colum position of the cursor

DINDEX=87 ; type of graphics
SAVMSC=88 ; address of the left upper corner of the screen
; The text window is TXTMSC (660,661)

; Address 90-98 are used by drawto/fill
OLDROW=90
OLDCOL=91 ; 91,92

OLDCHR=93
OLDADR=94 ; 94,95
; NEWROW=96
; NEWCOL=97 ; 97,98

FKDEV=96 ; 96,97 Pointer to definition table of function keys (since 1200XL)

PALNTS=98 ; 1 means PAL else NTSC

LOGCOL=99 ; logical line position (max 3 lines)

ADRESS=100 ; 100,101
MLTTMP=102 ; 102,103
SAVADR=104 ; 104,105

RAMTOP=106 ; upper RAM memory page real adress is RAMTOP * 256

BUFCNT=107 ; count of values in logical screen row

BUFSTR=108
BITMSK=110
SHFAMT=111 ; for pixel shift in pixel graphics
ROWAC=112 ; 112,113 calc register for plot/drawto
COLAC=114 ; 114,115
ENDPT=116 ; 116,117
DELTAR=118
DELTAC=119 ; 119,120
KEYDEF=121 ; key definition table
SWPFLG=123
HOLDCH=124
INSDAT=125
COUNTR=126 ; 126,127 line draw counter

; -----------------------------
; Address from 128 to 202 are used by Atari Basic

FREE=203 ; 203-211 in Atari Basic

; -----------------------------
; internal variables in zero page
; used by wnf-compiler
;
; we would like to use only the 42 bytes of floating-point-register
BININT = 212                   ; return value for Basic
@AUX  =   212

@PUTARRAY = 212                 ; 2 212 duerfen innerhalb von Expressions nicht ueberschrieben werden
@GETARRAY = @PUTARRAY+2         ; 2 214 dito

; Math values (mult, div, modulo)
@OP   =   @AUX + 4              ; 4 216
; Ergebnis, Produkt, REST
@PRODUKT = @AUX+8               ; 2 220
@REST =   @AUX+8                ; 2 222
@ERG  =   @AUX+8                ; 2 224
@ISMODULO = @AUX+10             ; 1 226

; working registers will always overwrite! Do not expect they will not changed after function call
@REG  =   @AUX+12               ; 26 bytes (13 Register) 224

@COLOR_REGISTER = 251

@FKT_PTR = 252
@HEAP_PTR = 254

;
; -----------------------------
SDMCTL = 559 ; Shadow register of ANTIC DMA Controller

SDLSTL=560 ; Shadow register of current Displaylist
; -----------------------------
; Hardware-Handler Adressen
EDITRV = $E400  ; Editor
SCRENV = $E410  ; Screen
KEYBDV = $E420  ; Keyboard

; Input ueber Keyboard only

ICHID =   832+0 ; Handleridentifizierung
ICDNO =   832+1 ; Devicenummer e.g. D1:
ICCOM =   832+2 ; Befehlsbyte
ICSTA =   832+3 ; Status
ICBADR =  832+4 ; :2 Adresse Filebuffer oder Filename
ICPUT =   832+6 ; :2
ICBLEN =  832+8 ; :2 Laenge des Buffers
ICAUX1 =  832+10 ; nach Open nicht verwenden
ICAUX2 =  832+11 ; nach Open nicht verwenden
ICAUX3 =  832+12
ICAUX4 =  832+13
ICAUX5 =  832+14
ICAUX6 =  832+15

CIOV  =   $E456

CIO_OPEN	= 3
CIO_GETTEXT	= 5
CIO_GETDATA	= 7
CIO_PUTTEXT	= 9
CIO_PUTDATA	= 11
CIO_CLOSE	= 12
CIO_GETSTATUS	= 13
CIO_READ	= 4
CIO_WRITE	= 8
CIO_DIR	= 6
