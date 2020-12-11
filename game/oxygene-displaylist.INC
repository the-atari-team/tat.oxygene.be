;; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Display List
;

 .include "MEMORY-MAP.INC"

 *= MEMORY_DISPLAYLISTS

 .local

; Displaylist
; Horizontales Scrolling

; --------------------------------------------------------------------
; setzen der XPOS innerhalb des Ships
; es wird das HSCROL beruecksichtigt
; TODO: Umbau auf Parameter fuer Compiler
;
 JMP @INIT_OXYGENE2_VBI       ; $1000

; ------------------------------------------------------------------------------
;
;    OOOOOOO   OO                      OOO                      OO        OO              OO
;    OO    OO                           OO                      OO                        OO
;    OO    OO OOO   OOOOOOO  OOOOOOOO   OO   OOOOOOOO OO     OO OO       OOO   OOOOOOO  OOOOOO
;    OO    OO  OO  OO        OO     OO  OO  OO     OO OO     OO OO        OO  OO          OO
;    OO    OO  OO   OOOOOOO  OO     OO  OO  OO     OO OO     OO OO        OO   OOOOOOO    OO
;    OO    OO  OO         OO OOOOOOOO   OO  OO     OO  OOOOOOOO OO        OO         OO   OO
;    OOOOOOO  OOOO  OOOOOOO  OO        OOOO  OOOOOOOO        OO OOOOOOOO OOOO  OOOOOOO     OOO
;                            OO                       OOOOOOOO
;
; OXYGENE #2 Displaylist
; ------------------------------------------------------------------------------
?MISSION_COMPLETED
; .sbyte "  ^ #$%&         00000  "
; .sbyte "  ^ #$%&       <=>&& ^  "
  .sbyte "                        "

@OXYGENE_DISPLAYLIST_SHIP
 .byte $70 ; 8 leerzeilen
 .byte $30 ; 5
 .byte $80 ; 1  Displaylist interrupt FIRST_DLI
 .byte $70 ; 8

; Zeile 22
 .byte $80 ; 1 Displaylist Statusline
 .byte $10 ; 2 leerzeilen

@DLIST_MISSION_TEXT_XPOS
 .byte $56 ; lade Adresse $1003 text 24,5,8 ; Mission
 .word ?MISSION_COMPLETED

 .byte $80 ; Displaylist interrupt PREPARE_OXYGENE_DLI
 .byte $10

 .byte ~01001110 ; $4e ; lade Adresse $15e0 (Oxygene Schriftzug)
 .word MEMORY_OXYGENE_LETTERING
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
; 38 Zeilen fuer Oxygene Schriftzug

 .byte $10 ; 2 Leerzeilen
; Zeile 40

 .byte $80 ; 1 Leerzeile, Displaylist Interrupt RAUMER_DLI
 .byte $00 ; 1 leerzeile

@SHIP_SHAKER1
 .byte $30 ; 4 leerzeilen

; Zeile 46
@DLIST_SHIP_XPOS
 .byte $54 ; displaylist interrupt
 .word MEMORY_SHIP
 .byte $54
 .word MEMORY_SHIP+$0200
 .byte $54
 .word MEMORY_SHIP+$0400
 .byte $54
 .word MEMORY_SHIP+$0600
 .byte $54
 .word MEMORY_SHIP+$0800
 .byte $54+$80              ; mid ship dli
 .word MEMORY_SHIP+$0a00
 .byte $54
 .word MEMORY_SHIP+$0c00
 .byte $54
 .word MEMORY_SHIP+$0e00
 .byte $54
 .word MEMORY_SHIP+$1000
 .byte $54
 .word MEMORY_SHIP+$1200
 .byte $54+$80              ; port ship dli
 .word MEMORY_SHIP+$1400
 .byte $54
 .word MEMORY_SHIP+$1600
 .byte $54
 .word MEMORY_SHIP+$1800
 .byte $54
 .word MEMORY_SHIP+$1a00
 .byte $54
 .word MEMORY_SHIP+$1c00
 .byte $54
 .word MEMORY_SHIP+$1e00
 .byte $54
 .word MEMORY_SHIP+$2000

; Zeile 46 + 17*8 = 182

; Shield
; Shieldfont beginnt bei $F800, da wir nur 192 Bytes brauchen,
; kann es und egal sein, das wir die 1. 512 bytes noch fuer das Ship
; verwenden
; Player Missiles Base ab $F800, da die ersten 768 Bytes nicht gebraucht werden

@SHIP_SHAKER2
 .byte $30 ; 4 leerzeilen

 .byte $20 ; 4 leerzeilen
 .byte $80 ; 1 Leerzeile, Displaylist Interrupt SHIELD_DLI
 .byte $10 ; 1 Leerzeile
 .byte $42
 .word MEMORY_SHIELD

; Zeile 200

 .byte $80 ; 1 Leerzeile, Displaylist Interrupt SHIELD_DLI_OFF
 .byte $30 ; 4 leerzeile

; Zeile 205

 .byte $41 ; jump & vbi ausloesen
 .word @OXYGENE_DISPLAYLIST_SHIP





; ------------------------------------------------------------------------------
;
;    OOOOOOO   OO                      OOO                      OO        OO              OO
;    OO    OO                           OO                      OO                        OO
;    OO    OO OOO   OOOOOOO  OOOOOOOO   OO   OOOOOOOO OO     OO OO       OOO   OOOOOOO  OOOOOO
;    OO    OO  OO  OO        OO     OO  OO  OO     OO OO     OO OO        OO  OO          OO
;    OO    OO  OO   OOOOOOO  OO     OO  OO  OO     OO OO     OO OO        OO   OOOOOOO    OO
;    OO    OO  OO         OO OOOOOOOO   OO  OO     OO  OOOOOOOO OO        OO         OO   OO
;    OOOOOOO  OOOO  OOOOOOO  OO        OOOO  OOOOOOOO        OO OOOOOOOO OOOO  OOOOOOO     OOO
;                            OO                       OOOOOOOO
;
; OXYGENE #2 Displaylist Menu
; ------------------------------------------------------------------------------

@OXYGENE_DISPLAYLIST_MENU
 .byte $70 ; 8 leerzeilen
 .byte $30 ; 5
 .byte $80 ; 1 Displaylist FIRST_DLI
 .byte $70 ; 8

; Zeile 22
 .byte $80 ; 1 Displaylist Statusline
 .byte $10 ; 2 leerzeilen

; Hier Greetingstext scrollen lassen!
@DLIST_MISSION_TEXT_XPOS2
 .byte $56 ; lade Adresse $1003 text 24,5,8 ; Mission
 .word ?MISSION_COMPLETED

 .byte $80 ; Displaylist interrupt
 .byte $10


 .byte ~01001110 ; $4e ; lade Adresse $15e0 (Oxygene Schriftzug)
 .word MEMORY_OXYGENE_LETTERING
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
 .byte $8e ; Displaylist interrupt
 .byte $0e
 .byte $0e
 .byte $0e
; Zeile 38

 .byte $10 ; 1 Leerzeilen
; Zeile 40

  .byte $80 ; 1 leerzeilen und Displaylistinterrupt
  .byte $00 ; 2 leerzeilen

  .byte $30 ; 4

; Zeile 46

  .byte $46 ; lade Adresse text 20,5,8 ; by the atari team
  .word MEMORY_SHIP ; @TEXTLINES
  .byte $10
  .byte $06 ; text 20,5,8 ; cdw 1988 - 2020
  .byte $10
  .byte $06 ; text 20,5,8 ; press fire to start
  .byte $10
  .byte $06 ; text 20,5,8 ; result level
  .byte $10
  .byte $06 ; text 20,5,8 ; easy-peasy
  .byte $10
  .byte $06 ; text 20,5,8
  .byte $10
  .byte $06 ; text 20,5,8 ; options
  .byte $10
  .byte $06 ; text 20,5,8 ; use cursor keys
  .byte $10
  .byte $06 ; text 20,5,8
  .byte $10
  .byte $06 ; text 20,5,8
  .byte $10
  .byte $06 ; text 20,5,8
  .byte $10
  .byte $06 ; text 20,5,8
  .byte $10
  .byte $06 ; text 20,5,8
  .byte $00
; Zeile 46 + 130 = 176

  .byte $46
  .word MEMORY_SHIP+12*20

;  .byte $50 ; 6 leerzeilen

; Shield
; Shieldfont beginnt bei $F800, da wir nur 192 Bytes brauchen,
; kann es und egal sein, das wir die 1. 512 bytes noch fuer das Ship
; verwenden
; Player Missiles Base ab $F800, da die ersten 768 Bytes nicht gebraucht werden

;@SHIP_SHAKER2
 .byte $20+$80 ; 1 leerzeilen
; .byte $10 ; 2
 .byte $10+$80 ; 1 leerzeilen
; .byte $10 ; 2
 .byte $00

 .byte $80 ; 1 Leerzeile, Displaylist Interrupt SHIELD_DLI
 .byte $10 ; 1 Leerzeile
 .byte $42
 .word MEMORY_SHIELD

; Zeile 194

 .byte $80 ; 1 Leerzeile, Displaylist Interrupt SHIELD_DLI_OFF
 .byte $30 ; 1 leerzeile

 .byte $41 ; jump & vbi ausloesen
 .word @OXYGENE_DISPLAYLIST_MENU



; ------------------------------------------------------------------------------
;
;    OOOOOOO   OO                      OOO                      OO        OO              OO
;    OO    OO                           OO                      OO                        OO
;    OO    OO OOO   OOOOOOO  OOOOOOOO   OO   OOOOOOOO OO     OO OO       OOO   OOOOOOO  OOOOOO
;    OO    OO  OO  OO        OO     OO  OO  OO     OO OO     OO OO        OO  OO          OO
;    OO    OO  OO   OOOOOOO  OO     OO  OO  OO     OO OO     OO OO        OO   OOOOOOO    OO
;    OO    OO  OO         OO OOOOOOOO   OO  OO     OO  OOOOOOOO OO        OO         OO   OO
;    OOOOOOO  OOOO  OOOOOOO  OO        OOOO  OOOOOOOO        OO OOOOOOOO OOOO  OOOOOOO     OOO
;                            OO                       OOOOOOOO
;
; OXYGENE #2 Displaylist Load
; ------------------------------------------------------------------------------
?SCREEN_LINE_LOAD_SHIP
 .byte 0,0,0,0,0,~00000110,~00000111,~11110011,~11110111,~11100000,~00000111,~11110110,~00110110,~01111111,~00000000,0,0,0,0,0
 .byte 0,0,0,0,0,~00000110,~00000110,~01110011,~00110110,~01100000,~00000110,~00110110,~00110110,~01100011,~00000000,0,0,0,0,0
 .byte 0,0,0,0,0,~00000110,~00000110,~01110011,~00110110,~01100000,~00000110,~00000110,~00110110,~01100011,~00000000,0,0,0,0,0
 .byte 0,0,0,0,0,~00000111,~00000110,~00110111,~11110111,~01110011,~11100111,~11110111,~11110111,~01111111,~00000000,0,0,0,0,0
 .byte 0,0,0,0,0,~00000111,~00000110,~00110111,~00110111,~01110000,~00000000,~01110111,~00110111,~01110000,~00011100,~11100111,0,0,0,0
 .byte 0,0,0,0,0,~00000111,~00000110,~00110111,~00110111,~01110000,~00000110,~01110111,~00110111,~01110000,~00010100,~10100101,0,0,0,0
 .byte 0,0,0,0,0,~00000111,~11110111,~11110111,~00110111,~11110000,~00000111,~11110111,~00110111,~01110000,~00011100,~11100111,0,0,0,0

@OXYGENE_DISPLAYLIST_LOAD
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen

 .byte $4B ; lade Adresse $1003 text 24,5,8 ; Mission
 .word ?SCREEN_LINE_LOAD_SHIP
 .byte $00
 .byte $0B
 .byte $00
 .byte $0B
 .byte $00
 .byte $0B
 .byte $00
 .byte $0B
 .byte $00
 .byte $0B
 .byte $00
 .byte $0B

 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $70 ; 8 leerzeilen
 .byte $41 ; jump & vbi ausloesen
 .word @OXYGENE_DISPLAYLIST_LOAD

; -----------------------------------------------------------------
@INIT_OXYGENE2_VBI
     LDA #3
     STA @SHIP_HSCROL
;     JSR @INIT_AUDIO
     JSR @SET_DISPLAYLIST_MENU
     JMP @INIT_OXYGENE_VBI



;?audctl = $d208
;?skctl = $d20f

; initialisiert das Audio System
;@INIT_AUDIO
;   LDA #3
;   STA ?skctl
;   LDA #0
;   STA ?audctl
;   RTS

@SHIP_XPOS_A
 .word 0

; TODO Vertikales Wackeln implementieren


@INNER_SET_SHIP_XPOS

 LDA @SHIP_X_POSITION
 STA @SHIP_XPOS_A
 LDA @SHIP_X_POSITION+1
 STA @SHIP_XPOS_A+1

; horizontales fine-scrolling (HSCROL) setzen
 LDA @SHIP_X_POSITION
 AND #3
 EOR #3
 STA @SHIP_HSCROL

; 2 bit nach rechts
 LSR @SHIP_XPOS_A+1
 ROR @SHIP_XPOS_A

 LSR @SHIP_XPOS_A+1
 ROR @SHIP_XPOS_A

; LSR @SHIP_XPOS_A+1
; ROR @SHIP_XPOS_A


; Manipuliere die Displaylist
 LDY #1
 CLC
 LDA @SHIP_XPOS_A
 ADC #<MEMORY_SHIP
 STA @DLIST_SHIP_XPOS+1
 STA @DLIST_SHIP_XPOS+1+3
 STA @DLIST_SHIP_XPOS+1+6
 STA @DLIST_SHIP_XPOS+1+9
 STA @DLIST_SHIP_XPOS+1+12
 STA @DLIST_SHIP_XPOS+1+15
 STA @DLIST_SHIP_XPOS+1+18
 STA @DLIST_SHIP_XPOS+1+21
 STA @DLIST_SHIP_XPOS+1+24
 STA @DLIST_SHIP_XPOS+1+27
 STA @DLIST_SHIP_XPOS+1+30
 STA @DLIST_SHIP_XPOS+1+33
 STA @DLIST_SHIP_XPOS+1+36
 STA @DLIST_SHIP_XPOS+1+39
 STA @DLIST_SHIP_XPOS+1+42
 STA @DLIST_SHIP_XPOS+1+45
 STA @DLIST_SHIP_XPOS+1+48

 LDA @SHIP_XPOS_A+1
 ADC #>MEMORY_SHIP
 STA @DLIST_SHIP_XPOS+2
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+3
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+6
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+9
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+12
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+15
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+18
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+21
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+24
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+27
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+30
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+33
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+36
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+39
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+42
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+45
 ADC #>$200
 STA @DLIST_SHIP_XPOS+2+48

 RTS

 .include "RAUMER-STRUCT.INC"
 .include "DLI.INC"
