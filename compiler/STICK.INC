; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;STICK-Library
;
;  enthaelt die Funktionen fuer Stick, Strig
;

; liefert aktuellen Wert zum Feuerknopf
; 0=gedrueckt
; 1=nicht gedrueckt
@STRIG
@STRIG_I
  LDY #1
  LDA (@HEAP_PTR),Y ; der 1. Parameter
  AND #~00000001 ; max 2 Strig
  TAY

  LDA 644,Y ; Schatten zu 53264..
  TAY
  LDX #0
  RTS

; liefert den originalen Stick Wert, kann nur mit 2 Sticks arbeiten (Atari XL)
; 15=nicht bewegt und jedes Bit fuer entsprechende Richtung
@STICK
@STICK_I
  LDY #1
  LDA (@HEAP_PTR),Y ; der 1. Parameter
  AND #~00000001 ; max 2 Sticks
  TAY

  LDA 632,Y ; Schatten von 54016..
  TAY
  LDX #0
  RTS

; liefert 1, wenn Stick(n) nach oben gedrueckt wird
@STICKUP
@STICKUP_I
  JSR @STICK
  TYA
  AND #~0001
  BEQ ?STICK_MOVED

?STICK_NOT_MOVED
  LDY #0
  LDX #0
  RTS

?STICK_MOVED
  LDY #1
  LDX #0
  RTS

; liefert 1, wenn Stick(n) nach unten gedrueckt wird
@STICKDOWN
@STICKDOWN_I
  JSR @STICK
  TYA
  AND #~0010
  BEQ ?STICK_MOVED
  BNE ?STICK_NOT_MOVED

; liefert 1, wenn Stick(n) nach links gedrueckt wird
@STICKLEFT
@STICKLEFT_I
  JSR @STICK
  TYA
  AND #~0100
  BEQ ?STICK_MOVED
  BNE ?STICK_NOT_MOVED

; liefert 1, wenn Stick(n) nach rechts gedrueckt wird
@STICKRIGHT
@STICKRIGHT_I
  JSR @STICK
  TYA
  AND #~1000
  BEQ ?STICK_MOVED
  BNE ?STICK_NOT_MOVED

