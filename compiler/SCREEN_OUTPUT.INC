;-*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;SCREEN_OUTPUT-Library

   .LOCAL

; Hardware-Treibertabellen
; EDITRV = $E400  ; Editor
; SCRENV = $E410  ; Screen
; KEYBDV = $E420  ; Keyboard

; Jeder Treiber sieht wie folgt aus
; 0 Vektor zu OPEN -1
; 2 Vektor zu CLOSE -1
; 4 Vektor zu GETBYTE -1
; 6 Vektor zu PUTBYTE -1
; 8 Vektor zu STATUS -1
; 10 Vektor zu SPECIAL -1
; 12 JMP ($4c)
; 13 Adresse zur INIT Routine
; 15 unbenutzt

; ----------------------------------------------------
; Wichtige Routinen hier:
; @PRINTSTRING  gibt übergebenen String aus (adr:bytearray)
; @PRINTCHAR    gibt ein Zeichen aus
; @PRINTVALUE   gibt eine Zahl vorzeichenbehaftet aus
; @PRINTDIGITS  gibt eine Zahl nicht vorzeichenbehaftet aus
; @CLRSCR       löscht den Schirm, alles was in der Displaylist erreichbar ist, leider auch den Header :-(
; @PRINTHEX2    gibt eine Zahl hexadezimal aus, 2 Zeichen only
; @PRINTHEX4    gibt eine Zahl hexadezimal aus, 4 Zeichen, Reihenfolge ist für die Ausgabe richtig, groß zuerst
;
; write ln() ist ausgebaut, @printf() verwenden!
; @PRINT_STRING gibt String aus, dieser beginnt sofort hinter dem JSR @PRINT_STRING und endet mit $FF
; @EOLOUT       gibt ein Atari-Return aus
; @DECOUT       gibt eine Zahl nicht vorzeichenbehaftet aus



; ----------------------------------------------------
; Hier nur Routinen, die Dinge auf dem Screen ausgeben
; ----------------------------------------------------

; Loesche den Bildschirm
@CLRSCR
      LDA EDITRV+1
      PHA
      LDA EDITRV
      PHA
      RTS

; ----------------------------------------------------
; Zeichenfolge auf Screen ausgeben
; endet mit $FF

@PRINT_STRING
      PLA
      STA @AUX
      PLA
      STA @AUX+1
      WINC  @AUX

      JSR ?PRINT_AUXCONTENT

      LDA @AUX+1
      PHA
      LDA @AUX
      PHA
      RTS

; ----------------------------------------------------
; Cursor in neue Zeile (enter)
@EOLOUT
      LDA #$9B  ;EOL ausgeben
      BNE @SCROUT

; @PRINTCHAR für Ausgabe eines Zeichens, nutzt die Funktion @SCROUT
@PRINTCHAR
     LDY #1
     LDA (@HEAP_PTR),Y

;       EIN Zeichen ausgeben
; <A> : auszugebendes Zeichen
@SCROUT
      TAY

      LDA @PRINTF_TYPE
      BEQ ?EDITOR_OUT
      CMP #6
      BEQ ?SCREEN_OUT

 .IF .DEF @FASTSCREEN_OUT
      CMP #'F
      BNE ?NO_FASTSCREEN_OUT

      TYA
      JMP @FASTSCREEN_OUT
 .ENDIF
?NO_FASTSCREEN_OUT

?EDITOR_OUT
      LDA EDITRV+7
      PHA
      LDA EDITRV+6
      PHA
      TYA
      RTS

?SCREEN_OUT
      LDA SCRENV+7
      PHA
      LDA SCRENV+6
      PHA
      TYA
      RTS

@PRINTF_TYPE
 .byte 0

; ----------------------------------------------------

@PRINTF_PRINTCHAR
     TYA
     JMP @SCROUT

; TODO: Cursor-Steuerung?
; up() down() left() right()

; ----------------------------------------------------
; Ausgabe eines Strings per Parameter
@PRINTSTRING
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

@PRINTF_PRINTSTRING
      STY @AUX
      STX @AUX+1

?PRINT_AUXCONTENT
      LDX #0
?PRINT2
      LDA (@AUX,X)
      CMP #$FF
      BEQ ?PREXIT2
      JSR @SCROUT
      WINC  @AUX
      LDX #0
      BEQ ?PRINT2

?PREXIT2
      RTS

; ----------------------------------------------------
; @PRINTHEX2 um 2 HEX-Zahlen auszugeben
; '$' muss per @PRINTCHAR(36) ausgegeben werden
@PRINTHEX2
      LDY #1
      LDA (@HEAP_PTR),Y ; Wert holen
      JMP @PRINTHEX

@PRINTF_PRINTHEX2
      TYA
      JMP @PRINTHEX
; ----------------------------------------------------
; @PRINTHEX4 um 4 HEX-Zahlen auszugeben (word oder byte)
; '$' muss per @PRINTCHAR(36) ausgegeben werden
@PRINTHEX4
      LDY #2
      LDA (@HEAP_PTR),Y ; Wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

@PRINTF_PRINTHEX4
;      STY @REG
      TYA
      PHA
;      STX @REG+1 ; unnötig
      TXA
      JSR @PRINTHEX
;      LDA @REG
      PLA
;      JMP @PRINTHEX ; unnötig

; Ein Byte in hex ausgeben
; <A> enthaelt das Zeichen
@PRINTHEX
      PHA
      LSR A
      LSR A
      LSR A
      LSR A
      TAX
      LDA ?ASCIIHEX,X
      JSR @SCROUT
      PLA
      AND #$0F
      TAX
      LDA ?ASCIIHEX,X
      JMP @SCROUT

?ASCIIHEX
      .BYTE '0,'1,'2,'3,'4,'5,'6,'7,'8,'9,'A,'B,'C,'D,'E,'F

; ----------------------------------------------------
; Decimalzahl nicht vorzeichenbehaftet ausgeben (-1 => 65535)
@PRINTDIGITS
    LDY #2
    LDA (@HEAP_PTR),Y ; wert holen
    TAX
    DEY
    LDA (@HEAP_PTR),Y
    TAY
@PRINTF_PRINTDIGITS
    JMP @DECOUT

; ----------------------------------------------------
; Vorzeichenbehaftete Decimalzahl ausgeben (-32768 bis 32767)
@PRINTVALUE
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

@PRINTF_PRINTVALUE
      STY @REG
      STX @REG+1

      LDA #32
      STA ?VORZEICHEN
;
; Wenn Zahl negativ:
      LDA @REG+1
      AND #128
      BEQ ?POSITIV
;
      LDA #'-   ; Negativ!!!
      STA ?VORZEICHEN
;
      LDA @REG  ;Invertieren
      EOR #255
      STA @REG
      LDA @REG+1
      EOR #255
      STA @REG+1
;
       WINC  @REG
;
; Binaer in Dezimal Umrechnung
?POSITIV
      LDY @REG
      LDX @REG+1

; ----------------------------------------------------
; Zahl als positive Dezimalzahl ausgeben
; Zahl (x * 256 + y)
@DECOUT
      STY @AUX  ;Parameter
      STX @AUX+1 ;speichern
      LDX #4
?VORBES
      LDA #'0   ;Ausgabebuffer
      STA ?ZIFFER,X ;mit B.-Code
      DEX       ;fuer Null
      BPL ?VORBES ;vorbesetzen

      LDX #0    ;Stellenzaehler
?STELLE
      LDA @AUX+1 ;Zehner-Potenz
      CMP ?DECHI,X ;groesser als
      BNE ?TSTHI ;restlich.Zahl?
      LDA @AUX
      CMP ?DECLO,X
?TSTHI
      BCC ?KLEINER ;Potenz zu gross
; Zehner-Potenz abziehen, Ziffer erhoehen
      SEC
      LDA @AUX  ;die aktuelle
      SBC ?DECLO,X ;Zehnerpotenz
      STA @AUX  ;abziehen
      LDA @AUX+1
      SBC ?DECHI,X
      STA @AUX+1
      INC ?ZIFFER,X ;Ziffer erhoehen
      JMP ?STELLE ;gleiche Stelle nochmal
; kleinere Zehnerpotenz anwaehlen
?KLEINER
      INX       ;schon vier Stellen
      CPX #4    ;bearbeitet?
      BNE ?STELLE ;nein ->
; nur noch Einerstelle da
      CLC       ;Einerstelle
      LDA @AUX  ;in Ausgabebuffer
      ADC ?ZIFFER+4 ;addieren
      STA ?ZIFFER+4

      LDA ?VORZEICHEN ;Vorzeichen?
      CMP #32
      BEQ ?NO_VORZEICHEN ;--> Nein

      JSR @SCROUT

; fuehrende '0 ueberspringen
?NO_VORZEICHEN
      LDX #0
?ZIFCHECK
      LDA ?ZIFFER,X
      CMP #'0
      BNE ?ZIFPRINT ;--> wenn nicht 0 ausgabe beginnen

      INX       ;am Ende?
      CPX #4
      BNE ?ZIFCHECK
;
?ZIFPRINT
      TXA
      PHA
      LDA ?ZIFFER,X
      JSR @SCROUT ;Print Ziffer
      PLA
      TAX
      INX
      CPX #5    ;am Ende?
      BNE ?ZIFPRINT

      LDA #32
      STA ?VORZEICHEN

      RTS

; zu Debugzwecken wieder ausmarkieren
; PRINT_ZIFFERN
;       JSR @PRINT_STRING

?VORZEICHEN
    .BYTE " "
?ZIFFER
    .BYTE ".....",$FF

; Tabellen der Zehnerpotenzen
; getrennte Tabellen f. LSB und MSB
?DECLO
    .BYTE  <10000, <1000,100,10
?DECHI
    .BYTE  >10000, >1000,0,0

; @POSITION(x,y) oder @gotoxy(x,y) um Cursor zu positionieren
@gotoxy
@Position
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA 86
      DEY
      LDA (@HEAP_PTR),Y
      STA 85

      LDY #3
      LDA (@HEAP_PTR),Y ; wert holen
      STA 84
      RTS
