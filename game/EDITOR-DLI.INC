; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Editor Display List Interrupts
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;
 .local

VDSLST=512

COLPM0=53266 ; Farben Player 0
COLPF0=53270 ; Farben Playfield => 708
PRIOR=53275  ; Schatten von 623

DMACTL=54272
WSYNC=54282
NMIEN=54286
GRACTL=53277 ; 2: Player an 1: Missiles an


SETVBV=$E45C
SYSVBV=$E45F
XITVBV=$E462

CHBASE=$D409

PCOLR0=704

; Den Displaylist Interrupt lassen wir im VBI setzen, so
; laufen wir nicht Gefahr damit etwas kaputt zu machen

@INIT_OXYGENE_DLI
     LDA #6         ; Nutze Immediate(6) VBI
     LDY #<?RESETDLI
     LDX #>?RESETDLI
     JSR SETVBV

     RTS


?RESETDLI
     PHA
     LDA #0
     STA 77 ; no colorswitch

     LDA #$0
     STA NMIEN ; Displaylist Interrupt sperren

     LDA #<?RAUMER_DLI
     STA VDSLST
     LDA #>?RAUMER_DLI
     STA VDSLST+1

     LDA #$C0
     STA NMIEN ; Displaylist Interrupt ermoeglichen

     PLA
     JMP SYSVBV

; ----------------------------------------------------------------------
?RAUMER_DLI
 PHA

; TODO: DMA Player Missile ein

 LDA @RS_SHIP_COLOR0 ; #2             ; Farben Ship
 STA COLPF0
 LDA @RS_SHIP_COLOR0+1 ; #12
 STA COLPF0+1
 LDA @RS_SHIP_COLOR0+2 ; #6
 STA COLPF0+2
 LDA @RS_SHIP_COLOR3STAR ; #$34 ; steuerboard farbe (gruen)
 STA COLPF0+3

; Raumer Font
 LDA #$94
 STA CHBASE

; Player Missile
 LDA PCOLR0
 STA COLPM0
 LDA PCOLR0+1
 STA COLPM0+1
 LDA PCOLR0+2
 STA COLPM0+2
 LDA PCOLR0+3
 STA COLPM0+3

 LDA #$3e     ; Player Missile an
 STA DMACTL
 LDA #3
 STA GRACTL


 LDA #<?SHIELD_ON_DLI
 STA VDSLST
 LDA #>?SHIELD_ON_DLI
 STA VDSLST+1
 PLA
 RTI

;;  -------------------------------------------
?SHIELD_ON_DLI
 PHA

 LDA #34     ; Player Missile aus
 STA DMACTL
 LDA #0
 STA GRACTL

 LDA 756     ; Standard Font
 STA CHBASE

 LDA 708     ; Standard Farben
 STA COLPF0
 LDA 709
 STA COLPF0+1
 LDA 710
 STA COLPF0+2
 LDA 711
 STA COLPF0+3
 LDA 712
 STA COLPF0+4

 LDA #<?RAUMER_DLI
 STA VDSLST
 LDA #>?RAUMER_DLI
 STA VDSLST+1
 PLA
 RTI


