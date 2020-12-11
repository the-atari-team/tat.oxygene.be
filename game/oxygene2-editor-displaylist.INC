;; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Editor Display List
;

 *=$9200

 .local

; Displaylist
; Horizontales Scrolling


HSCROL=54276

; --------------------------------------------------------------------
; setzen der XPOS innerhalb des Ships
; es wird das HSCROL beruecksichtigt
; Aktuell nur von Basic aus verwendbar
; TODO: Umbau auf Parameter f?r Compiler
;
 JMP @BASIC_SET_SHIP_XPOS

@BASIC_INIT_OXYGENE_DLI
     PLA
     LDA #3
     STA HSCROL
     LDA #<@OXYGENE_DISPLAYLIST
     STA 560
     LDA #>@OXYGENE_DISPLAYLIST
     STA 560+1
     JMP @INIT_OXYGENE_DLI

@BASIC_SET_SHIP_XPOS
 PLA
 PLA
 STA @SHIP_X_POSITION+1
 PLA
 STA @SHIP_X_POSITION
 JMP ?INNER_SET_SHIP_XPOS

@SHIP_XPOS_A
 .word 0

; TODO Vertikales Wackeln implementieren

?EXIT
 RTS

?STERN
 .byte ~00000010
 .byte ~00001000
 .byte ~00100000
 .byte ~10000000

?INNER_SET_SHIP_XPOS

 LDA @SHIP_X_POSITION+1
 STA @SHIP_XPOS_A+1
 LDA @SHIP_X_POSITION
 STA @SHIP_XPOS_A

; HSCROL setzen
; LDA @SHIP_X_POSITION
 AND #3
 EOR #3
 STA HSCROL

 TAX
 LDA ?STERN,X
 STA $97e3
 STA $97e4

; 3 bit nach rechts
 NOP
 NOP
 NOP
 NOP

 LSR @SHIP_XPOS_A+1
 ROR @SHIP_XPOS_A

 LSR @SHIP_XPOS_A+1
 ROR @SHIP_XPOS_A

 LDY #1
 CLC
 LDA @SHIP_XPOS_A
 ADC #<$9800
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
 ADC #>$9800
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


@OXYGENE_DISPLAYLIST
 .byte $70 ; 8 leerzeilen
 .byte $30 ; 4
; .byte $70 ; 8

?DISPLAYLIST_SHIP
 .byte $80 ; 1 Leerzeile, Displaylist Interrupt
 .byte $10 ; 1 leerzeilen

@DLIST_SHIP_XPOS
 .byte $54     ; Bereich fuer Ship
 .word $9800
 .byte $54
 .word $9a00
 .byte $54
 .word $9c00
 .byte $54
 .word $9e00
 .byte $54
 .word $a000
 .byte $54
 .word $a200
 .byte $54
 .word $a400
 .byte $54
 .word $a600
 .byte $54
 .word $a800
 .byte $54
 .word $aa00
 .byte $54
 .word $ac00
 .byte $54
 .word $ae00
 .byte $54
 .word $b000
 .byte $54
 .word $b200
 .byte $54
 .word $b400
 .byte $54
 .word $b600
 .byte $54
 .word $b800

; Zeile 136+2

 .byte $80 ; 1 Leerzeile, Displaylist Interrupt
 .byte $20 ; 3 leerzeilen

; Zeile 136 + 2 + 4
 .byte $4f ; Graphics 8 Bereich fuer Ship in sehr klein
 .word $ba00
 .byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f

 .byte $0 ; 1 leerzeile
; Zeile 136 + 2 + 4 + 13 + 1 = 156

  .byte $42
  .word $bc40
  .byte 2,2,2,2,2,2

 .byte $41 ; jump & vbi ausloesen
 .word @OXYGENE_DISPLAYLIST

 .include "RAUMER-STRUCT.INC"
 .include "EDITOR-DLI.INC"
