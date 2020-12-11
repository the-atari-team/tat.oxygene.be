; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Display List Interrupts
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;

; CRITIC=66
critical=203

@DLI_ROEDEL=204 ; 3 Bytes

VDSLST=512

HPOSP0=53248
HPOSM0=53252
SIZEM=53260

HSCROL=54276

COLPM0=53266 ; Farben Player 0
COLPF0=53270 ; Farben Playfield => 708
COLBK=53274

PRIOR=53275  ; Schatten von 623

DMACTL=54272
WSYNC=54282
NMIEN=54286
GRACTL=53277 ; 2: Player an 1: Missiles an


SETVBV=$E45C
SYSVBV=$E45F
XITVBV=$E462

CHACTL=$D401 ; 54273
CHBASE=$D409
CHBAS=756
SDLSTL=560

; PCOLR0=704
COLOR0=708

VCOUNT=54283

; Den Displaylist Interrupt lassen wir im VBI setzen, so
; laufen wir nicht Gefahr damit etwas kaputt zu machen

;     PLA
@INIT_OXYGENE_VBI
     LDA #6         ; Nutze Immediate(6) VBI
     LDY #<?VBI
     LDX #>?VBI
     JMP SETVBV


; ----------------------------------------------------------------------
;
;        OO    OO OOOOOOO   OOOOOO
;        OO    OO OO    OO    OO
;        OO    OO OO    OO    OO
;        OO    OO OOOOOOO     OO
;        OO    OO OO    OO    OO
;         OO  OO  OO    OO    OO
;          OOOO   OOOOOOO   OOOOOO
;
; Color switch TAT Sign
; Init DLI
; ----------------------------------------------------------------------

?OXYGENE_VERLAUF = @DLI_ROEDEL+2
?VBI

; VBI startet bei $7d (125 oder Zeile 150)
;     LDA VCOUNT
;     STA @RS_VCOUNT_VBI

     LDA @RS_INIT_DONE
     BEQ ?DLI_NOT_SET

     LDA #$0
     STA NMIEN ; Displaylist Interrupt ermoeglichen
     STA ?OXYGENE_VERLAUF       ; Start fuer Oxygene-Letter-Verlauf

     LDA #<?REAL_FIRST_DLI
     STA VDSLST                 ; 512
     LDA #>?REAL_FIRST_DLI
     STA VDSLST+1

     JSR @INNER_SET_SHIP_XPOS
     JSR @SET_DISPLAYLIST

     LDA #$C0
     STA NMIEN ; Displaylist Interrupt ermoeglichen

;     LDA #$20+2    ; Player Missile aus, 40 bytes
;     STA DMACTL
;     STA 559

;     LDA #0
;     STA GRACTL

; Abspielen der gesetzten Audios
     LDA @RS_AUDIO_PLAYER+2
     BEQ ?NO_AUDIO

     JSR @RS_AUDIO_PLAYER

?NO_AUDIO
?DLI_NOT_SET
;    JSR ?VBI_OWN
     JMP SYSVBV


RANDOM=53770

 .MACRO @SETCOLOR_TAT_SIGN
 LDA RANDOM        ; random Color TAT Zeichen
 ORA #$0F          ; immer die ganz helle Farbe

 STA COLPM0
 STA COLPM0+1
 STA COLPM0+2

 LDA @RS_TAT_COLOR1   ; innere Color TAT Zeichen
 STA COLPM0+3
 STA COLPF0+3         ; zusammengeschaltete Missiles color

 LDA #~00010001       ; Missiles zu einem zusammenschalten
 STA PRIOR

 LDA #~01010101       ; Missiles mittlere Breite
 STA SIZEM
 .ENDM

 .MACRO @SETPOSITION_TAT_SIGN
  CLC
  LDA @RS_TAT_XPOS ; #48+80-12
  STA HPOSP0    ; T
  ADC #1
  STA HPOSM0+1     ; left inner T 1
  ADC #4
  STA HPOSM0
  ADC #3
  STA HPOSP0+2  ; A
  STA HPOSP0+3  ; inner A
  ADC #8
  STA HPOSP0+1  ; T
  ADC #1
  STA HPOSM0+3   ; right inner T 2
  ADC #4
  STA HPOSM0+2   ; right inner T 1

 ; LDA #48+10
 ; STA HPOSM0     ; left inner T 1

 ; LDA #48+10
 ; STA HPOSM0+1   ; left inner T 2

 ; LDA #48+20+8
 ; STA HPOSM0+2   ; right inner T 1

 ; LDA #48+20+12
 ; STA HPOSM0+3   ; right inner T 2
 .ENDM

; ----------------------------------------------------------------------
;
;      OOOOOOO  OO        OOOOOO            OOO  OO                        OO
;      OO    OO OO          OO             OO                              OO
;      OO    OO OO          OO           OOOOOO OOO  OOOOOOOO   OOOOOOO  OOOOOO
;      OO    OO OO          OO             OO    OO  OO     OO OO          OO
;      OO    OO OO          OO             OO    OO  OO         OOOOOOO    OO
;      OO    OO OO          OO             OO    OO  OO               OO   OO
;      OOOOOOO  OOOOOOOO  OOOOOO           OO   OOOO OO         OOOOOOO     OOO
;
; DLI - Animiertes TAT
; ----------------------------------------------------------------------
?REAL_FIRST_DLI
 PHA

; LDA #$32
; STA COLBK

; LDA VCOUNT
; STA @RS_VCOUNT_VBI

; LDA @RS_TEXT_COLOR
; STA COLPF0
; LDA @RS_TEXT_COLOR+1
; STA COLPF0+1
; LDA @RS_TEXT_COLOR+2
; STA COLPF0+2
; LDA @RS_TEXT_COLOR+3
; STA COLPF0+3

 LDA @RS_TEXT_HSCROL_XPOS
 STA WSYNC
 STA HSCROL

; colorswitch TAT Zeichen
; da wir aktuell CRITIC nicht verwenden, auch das Schattenregister setzen

 LDA #$20+$10+$08+$04+2 ; DMA Player Missile an ($10+$08+$04) , NORMAL ($02) (40bytes) verwenden!
 STA DMACTL
 LDA #3
 STA GRACTL

 @SETCOLOR_TAT_SIGN

 CLD

 @SETPOSITION_TAT_SIGN

 LDA #<?STATLINE_DLI
 STA VDSLST
 LDA #>?STATLINE_DLI
 STA VDSLST+1

 LDA #>MEMORY_OXYGENE_MENU_FONT          ; Menu Text Font (Graphics 1, 512 Bytes)
 STA CHBASE

 PLA
 RTI


?STATLINE_DLI
 PHA
 STY @DLI_ROEDEL

 LDA @RS_SHOW_DISPLAY_LIST
 BEQ ?STATLINE_NOMENU_ON_DLI

 STA WSYNC
 STA WSYNC
 LDY #7
?STATLINE_LOOP
 STA WSYNC
 LDA @RS_STATLINE_COLOR,Y
 STA COLPF0
 DEY
 BNE ?STATLINE_LOOP
 JMP ?STATLINE_EXIT_DLI

?STATLINE_NOMENU_ON_DLI
; LDA #$32
; STA COLBK

; LDA VCOUNT
; STA @RS_VCOUNT_VBI

 LDA @RS_TEXT_COLOR
 STA COLPF0
 LDA @RS_TEXT_COLOR+1
 STA COLPF0+1
 LDA @RS_TEXT_COLOR+2
 STA COLPF0+2
 LDA @RS_TEXT_COLOR+3
 STA COLPF0+3

 LDA #0
 STA HPOSM0

?STATLINE_EXIT_DLI
 LDA #<?PREPARE_OXYGENE_DLI
 STA VDSLST
 LDA #>?PREPARE_OXYGENE_DLI
 STA VDSLST+1

 LDY @DLI_ROEDEL
 PLA
 RTI


?PREPARE_OXYGENE_DLI
 PHA
 STY @DLI_ROEDEL
; TYA
; PHA

 ; LDA VCOUNT
 ; STA @RS_VCOUNT_VBI+1

; LDA #$82
; STA COLBK

; LDA #$32+2 ; DMA Player Missile an, UNDERSCAN (32bytes) verwenden!
; STA DMACTL
; LDA #0
; STA GRACTL

 LDA @RS_OXYGENE_LOGO_TEXT_COLOR
 STA COLPF0+2      ; Oxygene Schriftfarbe

 LDY ?OXYGENE_VERLAUF
 LDA @RS_OXYGENE_LOGO_COLOR,Y
 STA COLPF0+1
 INY
 LDA @RS_OXYGENE_LOGO_COLOR,Y
 STA COLPF0
 INY
 STY ?OXYGENE_VERLAUF

 LDA #$20+$10+8+4+1 ; DMA Player Missile an, UNDERSCAN (32bytes) verwenden!
 STA WSYNC
 STA DMACTL

; TODO: ???
 LDA @RS_OXYGENE_LOGO_TAT_SIGN
 STA COLPF0+2

 LDA #<?OXYGENE_DLI
 STA VDSLST
 LDA #>?OXYGENE_DLI
 STA VDSLST+1

; LDA #0
; STA COLBK

; PLA
; TAY
 LDY @DLI_ROEDEL
 PLA
 RTI


; ----------------------------------------------------------------------
;
;    OOOOOOO  OO        OOOOOO          OOOOOO
;    OO    OO OO          OO           OO    OO
;    OO    OO OO          OO           OO    OO OO   OO OO     OO  OOOOOOOO  OOOOOOO  OOOOOOOO   OOOOOOO
;    OO    OO OO          OO           OO    OO  OO OO  OO     OO OO     OO OO     OO OO     OO OO     OO
;    OO    OO OO          OO           OO    OO   OOO   OO     OO OO     OO OOOOOOOOO OO     OO OOOOOOOOO
;    OO    OO OO          OO           OO    OO  OO OO   OOOOOOOO  OOOOOOOO OO        OO     OO OO
;    OOOOOOO  OOOOOOOO  OOOOOO          OOOOOO  OO   OO        OO        OO  OOOOOOO  OO     OO  OOOOOOO
;                                                       OOOOOOOO  OOOOOOOO
; DLI - Farbuebergang Oxygene Schriftzug
; ----------------------------------------------------------------------
?OXYGENE_DLI
 PHA

 STY @DLI_ROEDEL

 LDY ?OXYGENE_VERLAUF
 LDA @RS_OXYGENE_LOGO_COLOR,Y
 STA COLPF0+1
 INY
 LDA @RS_OXYGENE_LOGO_COLOR,Y
 STA COLPF0
 INY
 STY ?OXYGENE_VERLAUF

 CPY #14
 BEQ ?NEW_DLI

 LDY @DLI_ROEDEL
 PLA
 RTI

?NEW_DLI

 LDA #<?RAUMER_DLI
 STA VDSLST
 LDA #>?RAUMER_DLI
 STA VDSLST+1

 LDY @DLI_ROEDEL
 PLA
 RTI

; ----------------------------------------------------------------------
;
;    OOOOOOO  OO        OOOOOO         OOOOOOO
;    OO    OO OO          OO           OO    OO
;    OO    OO OO          OO           OO    OO  OOOOOOOO OO     OO OOOO OOO   OOOOOOO  OOOOOOOO
;    OO    OO OO          OO           OO    OO OO     OO OO     OO OO OOO OO OO     OO OO     OO
;    OO    OO OO          OO           OOOOOO   OO     OO OO     OO OO  O  OO OOOOOOOOO OO
;    OO    OO OO          OO           OO   OO  OO     OO OO     OO OO  O  OO OO        OO
;    OOOOOOO  OOOOOOOO  OOOOOO         OO    OO  OOOOOOOO  OOOOOOOO OO  O  OO  OOOOOOO  OO
;
; DLI - Raumer
; ----------------------------------------------------------------------

?RAUMER_DLI
 PHA ; STA @DLI_ROEDEL

 ; LDA VCOUNT
 ; STA @RS_VCOUNT_VBI+2

; LDA #$32
; STA COLBK

 LDA #$20+$10+8+4+2 ; DMA Player Missile an KEIN OVERSCAN verwenden!
 STA DMACTL
; LDA #3
; STA GRACTL

 LDA #~00110000    ; volle Breite Player 2
 STA SIZEM

 LDA #~00000001    ; Missiles zu einem zusammenschalten
 STA PRIOR

; LDA CRITICAL
; BEQ ?YES_RAUMER_DLI

; LDA #32+2       ; DMA Player Missile aus
; STA DMACTL
; LDA #0
; STA GRACTL

; JMP ?NO_RAUMER_DLI

;?YES_RAUMER_DLI

 STA WSYNC

; LDA @RS_SHIP_COLBK
; STA COLBK

 LDA @RS_SHIP_COLOR0 ; #2             ; Farben Ship
 STA COLPF0
 LDA @RS_SHIP_COLOR0+1 ; #12
 STA COLPF0+1
 LDA @RS_SHIP_COLOR0+2 ; #6
 STA COLPF0+2

 LDA @RS_SHIP_COLOR3STAR ; #$34 ; steuerboard farbe (gruen)
 STA COLPF0+3

 LDA @RS_SHOW_DISPLAY_LIST
 BNE ?MENU_ON_DLI

 LDA #>MEMORY_OXYGENE_FONT         ; Raumer Font
 JMP ?SET_CHBASE

?MENU_ON_DLI
; LDA #$20+$10+8+4+2 ; DMA Player Missile an normaler Screen
; STA DMACTL

 LDA #>MEMORY_OXYGENE_MENU_FONT          ; Menu Text Font, Graphics 1, 512 Bytes

?SET_CHBASE
 STA CHBASE

 LDA @RS_ENEMY_COLOR  ; Player Missile
 STA COLPM0
 LDA @RS_RAUMER_COLOR_LIGHT
 STA COLPM0+1
 LDA @RS_RAUMER_COLOR_INNER
 STA COLPM0+2
 LDA @RS_RAUMER_COLOR_SHADOW
 STA COLPM0+3

 LDA @ENEMY_SHOT_XPOS
 STA HPOSM0   ; x-pos missile 0 (Gegner)

 LDA @ENEMY_XPOS
 STA HPOSP0    ; x-pos player 0 (Enemy)

 LDA @RAUMER_SHOT_XPOS
 STA HPOSM0+2

 LDA @SHIP_HSCROL
 STA HSCROL

; Position Raumer
 LDA @RS_XPOS_PLAYER1 ; 53249   ; x-pos player 1
 STA HPOSP0+1
 LDA @RS_XPOS_PLAYER2 ; 53250   ; x-pos player 2
 STA HPOSP0+2
 LDA @RS_XPOS_MISSILE1 ; 53253   ; x-pos missile 1
 STA HPOSM0+1

 LDA @RS_XPOS_PLAYER3 ; 53251   ; x-pos player 3
 STA HPOSP0+3
 LDA @RS_XPOS_MISSILE3 ; 53255   ; x-pos missile 3
 STA HPOSM0+3

 LDA @RS_SHOW_DISPLAY_LIST
 BEQ ?NO_MENU_ON_DLI_2

 STA WSYNC

 STY @DLI_ROEDEL+1
 LDY #0

; ----------------------------------------------
; Schleife f?r Menufarben, ist sehr empfindlich
; ----------------------------------------------
?MENU_DLI_LOOP
 LDA @MENUCOLOR,y
 AND @RS_MENU_COLOR_AND
 STA COLPF0

 STA WSYNC

 INY
 CPY #131
 BNE ?MENU_DLI_LOOP

 LDA #6             ; alle Zeichen auf dem Kopf darstellen
 STA CHACTL

?MENU_DLI_LOOP2
 LDA @MENUCOLOR,y
 AND @RS_MENU_COLOR_AND
 STA COLPF0

 STA WSYNC

 INY
 CPY #140
 BNE ?MENU_DLI_LOOP2

 LDY @DLI_ROEDEL+1

?NO_RAUMER_DLI
?NO_MENU_ON_DLI_2

 LDA #<?MID_SHIP_DLI
 STA VDSLST
 LDA #>?MID_SHIP_DLI
 STA VDSLST+1

 PLA
 RTI

; ----------------------------------------------------------------------
; mid ship
; ----------------------------------------------------------------------

?MID_SHIP_DLI
 PHA
 LDA #<?PORT_SHIP_DLI
 STA VDSLST
 LDA #>?PORT_SHIP_DLI
 STA VDSLST+1

 LDA @RS_SHIP_COLOR3MID ; #$34 ; mid ship farbe
 STA COLPF0+3

 PLA
 RTI


; ----------------------------------------------------------------------
; port ship
; ----------------------------------------------------------------------

?PORT_SHIP_DLI
 PHA
 LDA #<?SHIELD_ON_DLI
 STA VDSLST
 LDA #>?SHIELD_ON_DLI
 STA VDSLST+1

 LDA @RS_SHIP_COLOR3PORT ; #$34 ; backboard farbe (rot)
 STA COLPF0+3

 PLA
 RTI


; ----------------------------------------------------------------------
;
;    OOOOOOO  OO        OOOOOO          OOOOOO  OO         OO            OOO         OO
;    OO    OO OO          OO           OO       OO                        OO         OO
;    OO    OO OO          OO           OO       OOOOOOOO  OOO   OOOOOOO   OO   OOOOOOOO
;    OO    OO OO          OO            OOOOOO  OO     OO  OO  OO     OO  OO  OO     OO
;    OO    OO OO          OO                 OO OO     OO  OO  OOOOOOOOO  OO  OO     OO
;    OO    OO OO          OO                 OO OO     OO  OO  OO         OO  OO     OO
;    OOOOOOO  OOOOOOOO  OOOOOO          OOOOOO  OO     OO OOOO  OOOOOOO  OOOO  OOOOOOOO
;
; DLI - Shield
; anderer Zeichensatz
; Farben umstellen
; GTIA setzen (9 Farben)
; ----------------------------------------------------------------------

?SHIELD_ON_DLI
 PHA

 ; LDA VCOUNT
 ; STA @RS_VCOUNT_VBI+3

 LDA #$3e       ; DMA Player Missile an normaler Screen
 STA DMACTL

 LDA #>MEMORY_OXYGENE_SHIELD_FONT    ; Shield Font
 STA CHBASE

 LDA @RS_SHIELD_SHIP_XPOS ; #48+6    ; blauer Player
 STA HPOSP0+1

 LDA #0         ; Den Raumerschatten weg schalten
 STA HPOSP0+3
 STA HPOSM0     ; Missile Enemy shot weg

 STA COLPM0     ; 704 - Hintergrund-Farbe (GTIA)
 LDA @RS_SHIELD_SHIP_COLOR
 STA COLPM0+1   ; 705
 LDA @RS_SHIELD_BACKGROUND2
 STA COLPM0+2   ; 706
 LDA @RS_SHIELD_VERLAUF  ; #$28
 STA COLPM0+3   ; 707

 LDA @RS_SHIELD_VERLAUF+1 ; #$18
 STA COLPF0     ; 708
 LDA @RS_SHIELD_VERLAUF+2 ; #$e8
 STA COLPF0+1   ; 709
 LDA @RS_SHIELD_VERLAUF+3 ; #$d8
 STA COLPF0+2   ; 710
 LDA @RS_SHIELD_VERLAUF+4 ; #$c8
 STA COLPF0+3   ; 711

 LDA #$80       ; Umschalten auf Graphics 10 (GTIA) 9 Farben
 STA PRIOR

 LDA @RS_SHIELD_VERLAUF+5 ; #$b8
 STA WSYNC
 STA COLBK      ; 712

?NO_SHIELD_ON_DLI

 LDA #<?SHIELD_OFF_DLI
 STA VDSLST
 LDA #>?SHIELD_OFF_DLI
 STA VDSLST+1
 PLA
 RTI

; ----------------------------------------------------------------------
;
;    OOOOOOO  OO        OOOOOO         OOO                        OO
;    OO    OO OO          OO            OO                        OO
;    OO    OO OO          OO            OO   OOOOOOOO  OOOOOOO  OOOOOO
;    OO    OO OO          OO            OO  OO     OO OO          OO
;    OO    OO OO          OO            OO  OO     OO  OOOOOOO    OO
;    OO    OO OO          OO            OO  OO     OO        OO   OO
;    OOOOOOO  OOOOOOOO  OOOOOO         OOOO  OOOOOOOO  OOOOOOO     OOO
;
; DLI Shield wieder abschalten
; ----------------------------------------------------------------------

?SHIELD_OFF_DLI
 PHA

 ; LDA VCOUNT
 ; STA @RS_VCOUNT_VBI+4

; STY @DLI_ROEDEL+1
; STX @DLI_ROEDEL+2
 LDA #0
 STA COLPM0       ; 704
 STA COLPM0+1
 STA COLPM0+2
 STA COLPM0+3

 STA WSYNC
 STA COLPF0+4

 LDA #1           ; GTIA wieder aus
 STA PRIOR

 LDA #0 ;15
 STA COLPF0+2

; LDA #0 ;$34
 STA COLPF0+1

 LDA #32+1       ; DMA Player Missile aus
 STA DMACTL
 LDA #0
 STA GRACTL

 LDA #<?REAL_FIRST_DLI
 STA VDSLST
 LDA #>?REAL_FIRST_DLI
 STA VDSLST+1

; LDY @DLI_ROEDEL+1
; LDX @DLI_ROEDEL+2
 PLA
 RTI

; wird im VBI gesetzt
@SET_DISPLAYLIST
 LDA @RS_DMA
 BEQ @SET_DISPLAYLIST_LOAD

 LDA @RS_SHOW_DISPLAY_LIST
 BEQ @SET_DISPLAYLIST_SHIP ; z=1 (LDA #0) Wir zeigen das SHIP bei 0, sonst Menu!

; CMP #2
; BEQ @SET_DISPLAYLIST_DONE

@SET_DISPLAYLIST_MENU
 LDY #<@OXYGENE_DISPLAYLIST_MENU
 LDX #>@OXYGENE_DISPLAYLIST_MENU

?SET560
 STY SDLSTL
 STX SDLSTL+1
 RTS

@SET_DISPLAYLIST_SHIP
 LDY #<@OXYGENE_DISPLAYLIST_SHIP
 LDX #>@OXYGENE_DISPLAYLIST_SHIP
 BNE ?SET560


@SET_DISPLAYLIST_LOAD
; bloede Idee, weil Font unter OS!
; LDA #>MEMORY_OXYGENE_MENU_FONT          ; Menu Text Font (Graphics 1, 512 Bytes)
; STA CHBAS

 LDA 20
 LSR
 LSR
 AND #$0F
 STA COLOR0

 LDY #<@OXYGENE_DISPLAYLIST_LOAD
 LDX #>@OXYGENE_DISPLAYLIST_LOAD
 BNE ?SET560


DLISTL=54274
SDMCTL=559
GPRIOR=623
CONSOL=53279
PCOLR0=704
CHACT=755
CH=764
KBCODE=53769
KEYDEL=753
KEYDIS=621
KEYREP=730
PORTA=54016
SKSTAT=53775
SRTIMR=555
STICK0=632
STICK1=633
STRIG0=644
STRIG1=645
TRIG0=53264
TRIG1=53265

;; ?VBI_OWN
;;    LDA SDLSTL+1 ; 561
;;    STA DLISTL+1
;;    LDA SDLSTL  ; 560
;;    STA DLISTL
;;    LDA SDMCTL  ; 559
;;    STA DMACTL
;;    LDA GPRIOR  ; 623
;;    STA PRIOR
;;
;;    LDX #$08
;;    STX CONSOL
;;
;; ?COLORLOOP
;;     CLI
;;     LDA PCOLR0,X
;;     STA COLPM0,X
;;     DEX
;;     BPL ?COLORLOOP
;;     LDA CHBAS
;;     STA CHBASE
;;     LDA CHACT
;;     STA CHACTL
;;
;;     LDA SKSTAT ; shift key
;;     AND #$04
;;     BEQ ?KEY_IS_PRESSED
;;     LDA KEYDEL
;;     BEQ ?KEY_IS_PRESSED
;;     DEC KEYDEL
;;
;; ?KEY_IS_PRESSED
;;     LDA SRTIMR
;;     BEQ ?KEY_BUT_DO_NOTHING
;;     LDA SKSTAT
;;     AND #$04
;;     BNE ?KEY_NOT_PRESSED
;;     DEC SRTIMR
;;     BNE ?KEY_BUT_DO_NOTHING
;;     LDA KEYDIS
;;     BNE ?KEY_BUT_DO_NOTHING
;;     LDA KEYREP
;;     STA SRTIMR
;;
;;     LDA KBCODE
;;     CMP #$9F      ; ctrl-1
;;     BEQ ?KEY_BUT_DO_NOTHING
;;     CMP #$83      ; ctrl-f1
;;     BEQ ?KEY_BUT_DO_NOTHING
;;     CMP #$84      ; ctrl-f2
;;     BEQ ?KEY_BUT_DO_NOTHING
;;     CMP #$94      ; ctrl-f4
;;     BEQ ?KEY_BUT_DO_NOTHING
;;     AND #$3F
;;     CMP #$11      ; Help / Ctrl-Q
;;     BEQ ?KEY_BUT_DO_NOTHING
;;
;;     LDA KBCODE
;;     STA CH
;;     JMP ?KEY_BUT_DO_NOTHING              ;[expand]
;;
;; ?KEY_NOT_PRESSED
;;     LDA #$00
;;     STA SRTIMR
;;
;; ?KEY_BUT_DO_NOTHING
;;     LDA PORTA    ; Stick 0&1
;;     LSR
;;     LSR
;;     LSR
;;     LSR
;;     STA STICK1
;;
;;     LDA PORTA
;;     AND #$0F
;;     STA STICK0
;;
;;     LDA TRIG0
;;     STA STRIG0
;;
;;     LDA TRIG1
;;     STA STRIG1
;;
;;     RTS

?AFTER_VBI = *
  .OPT LIST
  .IF ?AFTER_VBI >= [$15e0 - 1]
  .ERROR "We overwrite Code!"
  .ENDIF
