;-*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;FAST_SCREEN_OUTPUT-Library

@CURRENT_CURSOR_ROW
 .word 0

   .LOCAL

?PRINTFF_COLOR = @REG+8

; ----------------------------------------------------
; Schnellere Routine um Zeichen in den Bildschirm zu "stoßen"
; Character kommt im Akku!
@FASTSCREEN_OUT
; character ASCII -> Screenbyte umwandeln
; alles <32 with +64
; alles >96 bleibt wie es ist
; alles zw. 32 und 96 with -32

 CMP #32
 BMI ?CHAR_SMALLER_33

 CMP #96
 BPL ?SETFASTCHAR

 SEC
 SBC #32

 JMP ?SETFASTCHAR

?CHAR_SMALLER_33
 CLC
 ADC #64

?SETFASTCHAR
; Ab hier ist das Char ein Screenbyte

 CMP #$9b     ; Sonderzeichen, carrige return
 BEQ ?CURSOR_NEXTLINE

 ORA ?PRINTFF_COLOR
 TAX

 LDY COLCRS
 TXA
 STA (@REG+6),Y

; Ab hier cursor Movement
 INY
 CPY ?BYTES_PER_LINE
 BPL ?CURSOR_NEXTLINE

 STY COLCRS

 LDY #0               ; error code!
 LDX #0
 RTS


?CURSOR_NEXTLINE
 LDA #0
 STA COLCRS

 INC ROWCRS

 CLC
 LDA @REG+6
 ADC ?BYTES_PER_LINE
 STA @REG+6
 STA @CURRENT_CURSOR_ROW
 BCC ?NO_INC_HIGH2

 INC @REG+7
 INC @CURRENT_CURSOR_ROW+1

?NO_INC_HIGH2
 LDY #0              ; error code!
 RTS

; zeigt exact auf die Adresse des Cursors

?BYTES_PER_LINE
 .byte 20

; Zeigt auf die linke obere Ecke, INIT_FASTSCREEN setzt das!
?SCREEN_UPPER_LEFT
 .word 0

; setzt die linke obere Ecke
@INIT_FASTSCREEN
     LDY #2
     LDA (@HEAP_PTR),Y
     STA ?SCREEN_UPPER_LEFT+1
     STA @CURRENT_CURSOR_ROW+1

     DEY
     LDA (@HEAP_PTR),Y
     STA ?SCREEN_UPPER_LEFT
     STA @CURRENT_CURSOR_ROW

     DEY            ; save a byte
     STY COLCRS
     STY ROWCRS

; Der default ist 20 bytes
     LDA #20
     STA ?BYTES_PER_LINE

     RTS

; setzt die Anzahl an Bytes pro Zeile. Nach INIT_FASTSCREEN setzen!
; folgende Breiten gibt es
; 16 Gfx 1&2 und 559<=Schmalles Anzeigefeld
; 20 Gfx 1&2
; 24 Gfx 1&2 und 559<=breites Anzeigefeld oder horiz. Scrolling
; 28 Gfx 1&2 und 559<=breites Anzeigefeld und horiz. Scrolling
; 32 Gfx 0 und schmalles Anzeigefeld
; 40 Gfx 0
; 48 Gfx 0 und 559<=breites Anzeigefeld oder horiz. Scrolling

@INIT_SET_BYTES_PER_LINE
     LDY #1
     LDA (@HEAP_PTR),Y
     STA ?BYTES_PER_LINE
     RTS

; bewegt den Cursor an eine andere Position (x, y)
; und berechnet dabei die NEXT_CURSOR_POSITION neu
; WICHTIG, INIT_FASTSCREEN sollte gerufen worden sein
@FAST_GOTOXY
 LDY #1
 LDA (@HEAP_PTR),Y
 STA COLCRS
; X-position wird spaeter addiert

 LDY #3
 LDA (@HEAP_PTR),Y
 STA ROWCRS
 TAY

 LDA ?SCREEN_UPPER_LEFT
 STA @CURRENT_CURSOR_ROW
 LDA ?SCREEN_UPPER_LEFT+1
 STA @CURRENT_CURSOR_ROW+1

 CPY #0
 BEQ ?NO_INC_OF_LINES

; Y-Cursor * n * Bytes_per_line
?LOOP
 CLC
 LDA @CURRENT_CURSOR_ROW
 ADC ?BYTES_PER_LINE
 STA @CURRENT_CURSOR_ROW
 BCC ?NO_INC_HIGH
 INC @CURRENT_CURSOR_ROW+1
?NO_INC_HIGH
 DEY
 BNE ?LOOP

?NO_INC_OF_LINES
 RTS
