; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; Collisionchecks fuer Oxygene

      .local

; Laser des Raumers kollisionschecks
; - mit anderen Jets (diese explodieren)
; - mit Haus
;
; Raumer kollisionschecks
; - Kollision mit Haus
; - Funkmast
; - Strommast

@initCursorBeforeRaumerShot ; (raumerXPosition, raumerShot_x, raumerY, raumerShotCount, raumerYDirection)
@initCursorBeforeRaumerShot_IIIII
      jsr ?calcCursorBeforeRaumerShot

      LDY #5
      LDA (@HEAP_PTR),Y ; wert holen

; ((raumerY - 39) / 8 ) * $200
; umrechnen erst / 8 dann * $200

      SEC
      SBC #42
      LSR A
      LSR A
      LSR A

      ASL A
      STA ?RAUMERY_FOR_SHOT+1
      LDA #0
      STA ?RAUMERY_FOR_SHOT

      LDY #7
      LDA (@HEAP_PTR),Y ; raumerShotCount
      STA ?RAUMERSHOT_COUNT

      LDY #9
      LDA (@HEAP_PTR),Y ; raumerYDirection
      STA ?RAUMER_Y_DIRECTION


?rememberCursorForRaumerShot
      CLC
      LDA ?RAUMERY_FOR_SHOT
      ADC @REG
      STA @REG
      TAY

      LDA ?RAUMERY_FOR_SHOT+1
      ADC @REG+1
      STA @REG+1
      TAX

      STY @RAUMERSHOT_CURSOR1
      STX @RAUMERSHOT_CURSOR1+1

; safe values under cursor
      LDY #0
      LDA (@REG),Y
;      STA @RAUMERSHOT_UNDER_CURSOR1
      JSR @CHECK_FOR_JET
      CPY #1
      BCS ?FOUND_SOMETHING

      LDY #0

;      EOR #128
;      STA (@REG),Y

      INC @REG+1
      INC @REG+1
      INC @REG+1
      INC @REG+1
      LDA (@REG),Y
;      STA @RAUMERSHOT_UNDER_CURSOR2
      JSR @CHECK_FOR_JET
      CPY #1
      BCS ?FOUND_SOMETHING

;      EOR #128
;      STA (@REG),Y

; Pruefen, was

      LDY #0
      LDX #0
      RTS

?FOUND_SOMETHING
      LDX #0
      RTS



; Werte zu Begin Zeitpunkt des Schusses
; Wir brauchen diese Infos zum Ermitteln, ob 1 oder 2 Schuesse abgefeuert wurden.
?RAUMERSHOT_COUNT
     .byte 0

?RAUMER_Y_DIRECTION
     .byte 0

; (raumerXPosition, raumerShot_x)
@cursorBeforeRaumerShot
@cursorBeforeRaumerShot_II
      jsr ?calcCursorBeforeRaumerShot
      jmp ?rememberCursorForRaumerShot

; (raumerXPosition, raumerShot_x)
?calcCursorBeforeRaumerShot
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

; (x*256+y) ist der Wert im Heap
; (raumerXPosition / 32) + 22 bytes wenn raumerXDirection==1 +3
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG

      CLC
      LDA @REG
      ADC #5
      STA @REG
      BCC ?NOINC1
      INC @REG+1
?NOINC1

      LDY #3
      LDA (@HEAP_PTR),Y ; raumerShot_x holen

      LSR  ; / 4
      LSR

      CLC
      ADC @REG
      STA @REG
      TAY

      LDA @REG+1
      ADC #>MEMORY_SHIP
      STA @REG+1
      TAX

      RTS

; add together

@restoreCursorUnderRaumerShot
       RTS
; take collision_red
;      LDA @RAUMERSHOT_CURSOR1
;      STA @REG
;      LDA @RAUMERSHOT_CURSOR1+1
;      STA @REG+1
;
;      LDY #0
;      LDA @RAUMERSHOT_UNDER_CURSOR1
;      STA (@REG),Y
;
;      INC @REG+1
;      INC @REG+1
;      INC @REG+1
;      INC @REG+1
;      LDA @RAUMERSHOT_UNDER_CURSOR2
;      STA (@REG),Y
;
;      RTS

?RAUMERY_FOR_SHOT
      .word 0

@RAUMERSHOT_CURSOR1
   .word MEMORY_SHIP

;@RAUMERSHOT_UNDER_CURSOR1
;   .byte 0

;@RAUMERSHOT_UNDER_CURSOR2
;   .byte 0

; Pruefen, was sich kurz vor dem Raumer befindet Kollisionstest
; @cursorBeforeRaumer(raumerXPosition, raumerY) ; , raumerXDirection, raumerLastAnimation
@cursorBeforeRaumer
@cursorBeforeRaumer_ii
      jsr ?calcCursorBeforeRaumer

      STY @REG
      STY @RAUMER_CURSOR1
      STX @REG+1
      STX @RAUMER_CURSOR1+1

; safe values under cursor
      LDY #0
      LDA (@REG),Y

;      STA @RAUMER_UNDER_CURSOR1




      JSR @CHECK_FOR_HAUS_OR_MAST
      CPY #0
      BNE ?FOUND_HAUS_OR_MAST

      LDY #2
      LDA (@REG),Y






      JSR @CHECK_FOR_HAUS_OR_MAST
      CPY #0
      BNE ?FOUND_HAUS_OR_MAST

      INC @REG+1
      INC @REG+1

      LDY #1
      LDA (@REG),Y

;      STA @RAUMER_UNDER_CURSOR3




      JSR @CHECK_FOR_HAUS_OR_MAST
      CPY #0
      BNE ?FOUND_HAUS_OR_MAST

      INC @REG+1
      INC @REG+1

      LDY #0
      LDA (@REG),Y

;      STA @RAUMER_UNDER_CURSOR4




      JSR @CHECK_FOR_HAUS_OR_MAST
      CPY #0
      BNE ?FOUND_HAUS_OR_MAST

      LDY #2
      LDA (@REG),Y






      JSR @CHECK_FOR_HAUS_OR_MAST
      CPY #0
      BNE ?FOUND_HAUS_OR_MAST

      LDY #0
      LDX #0
      RTS

?FOUND_HAUS_OR_MAST
;      LDY #1  ; in Y steht drin, was wir gefunden haben!
      LDX #0
      RTS


?CHECK_HOUSE_OR_MAST
 .byte 0 ; fuellbyte
 .byte 15, 16 ; hochhaus
 .byte 19, 20
 .byte 22, 23
 .byte 48, 49, 50 ; Strommast
 .byte 103, 104 ; Funkantenne
 .byte 106, 107
 .byte 121 ; Landebahn

; Pruefe ob im Akku ein Wert drin ist, der ein Haus,
; Funkmast oder Strommast entspricht.
@CHECK_FOR_HAUS_OR_MAST
 LDX #14
?CHECK_HOUSE_OR_MAST_LOOP
 CMP ?CHECK_HOUSE_OR_MAST,X
 BEQ ?FOUND_HOUSE_OR_MAST ; House or Mast Character gefunden
 DEX
 BNE ?CHECK_HOUSE_OR_MAST_LOOP

 LDY #0 ; nichts gefunden
 RTS

?FOUND_HOUSE_OR_MAST
 TAY ; etwas gefunden, Y-Reg enthaelt was genau
 RTS



?calcCursorBeforeRaumer
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

; (x*256+y) ist der Wert im Heap
; (raumerXPosition / 32) + 22 bytes
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG
      LSR @REG+1 ; / 2
      ROR @REG

      CLC
      LDA @REG
      ADC #22
      STA @REG
      BCC ?NOINC2
      INC @REG+1
?NOINC2

; ((raumerY - 42) / 8 ) * $200
; umrechnen erst / 8 dann * $200
      LDY #3
      LDA (@HEAP_PTR),Y ; wert holen

      SEC
      SBC #42

      LSR A
      LSR A
      LSR A

      ASL A
      STA @REG+3
      LDA #0
      STA @REG+2

; raumerXDirection
;      LDY #5
;      LDA (@HEAP_PTR),Y ; wert holen

; wir brauchen die raumerXDirection nicht
; wir muessen unter dem Raumer
; x x
;  x
; x x
; immer diese Positionen pruefen, sonst koennen wir bei Highspeed
; evtl. 2 Felder breite Haeuser �berfliegen
;      CMP #255
;      BEQ ?NO_ADD_TO_XPOSITION

;      CLC
;      LDA @REG
;      ADC #2
;      STA @REG
;;      LDA @REG+1
;;      ADC #0
;;      STA @REG+1
;      BCC ?NOINC2
;      INC @REG+1
;?NOINC2
;
;?NO_ADD_TO_XPOSITION
; add together
      CLC
      LDA @REG
      ADC @REG+2
      TAY

      LDA @REG+1
      ADC @REG+3
      ADC #>MEMORY_SHIP
      TAX
      RTS

@restoreCursor
       RTS
; collision_red
;      LDA @RAUMER_CURSOR1
;      STA @REG
;      LDA @RAUMER_CURSOR1+1
;      STA @REG+1
;
;      LDY #0
;      LDA @RAUMER_UNDER_CURSOR1
;      STA (@REG),Y
;
;      INC @REG+1
;      INC @REG+1
;      LDA @RAUMER_UNDER_CURSOR2
;      STA (@REG),Y
;
;      INC @REG+1
;      INC @REG+1
;      LDA @RAUMER_UNDER_CURSOR3
;      STA (@REG),Y
;
;      RTS

@RAUMER_CURSOR1
   .word MEMORY_SHIP

;@RAUMER_UNDER_CURSOR1
;   .byte 0
;
;@RAUMER_UNDER_CURSOR2
;   .byte 0
;
;@RAUMER_UNDER_CURSOR3
;   .byte 0

?CHECKJET1
 .byte 0 ; fuellbyte
 .byte 30, 31, 32 ; Enemy 1
 .byte 33, 34, 35 ; Wenn die fehlen, kleiner Enemy 1 !
 .byte 36, 37, 38

?CHECKJET2
 .byte 0 ; fuellbyte
 .byte 112, 113, 114 ; Enemy 2
 .byte 115, 116, 117
 .byte 118, 119, 120

?REPLACE_WITH_EXPLOSION
 .byte 39, 40, 41 ; Explosion
 .byte 42, 43, 44
 .byte 45, 46, 47

; Pruefe ob im Akku ein Wert drin ist, der einem JET entspricht.
@CHECK_FOR_JET
 LDX #9
?CHECKJET1_LOOP
 CMP ?CHECKJET1,X
 BEQ ?FOUND_CHECK1   ; JET Character gefunden
 DEX
 BNE ?CHECKJET1_LOOP

; naechsten Jet pruefen
 LDX #9
?CHECKJET2_LOOP
 CMP ?CHECKJET2,X
 BEQ ?FOUND_CHECK1   ; JET Character gefunden
 DEX
 BNE ?CHECKJET2_LOOP

; haus pruefen, durch Masten koennen wir durchschiessen
 LDX #6
?CHECKHOUSE2_LOOP
 CMP ?CHECK_HOUSE_OR_MAST,X
 BEQ ?FOUND_HOUSE2   ; Haus Character gefunden
 DEX
 BNE ?CHECKHOUSE2_LOOP

 LDY #0 ; nichts gefunden
 RTS

?FOUND_HOUSE2
 LDY #2
 RTS


; Position relativ zur linken oberen Ecke
?JET_POSITIONS
 .word 0 ; fuellword
 .word 0,1,2
 .word $200,$201,$202
 .word $400,$401,$402

?FOUND_CHECK1
 TXA               ; im X Register steht welche Position wir gefunden haben
 ASL A             ; *2, fuer Word
 TAX

 SEC
 LDA @REG
 SBC ?JET_POSITIONS,X
 STA @REG+2
 STA @REG+4
 LDA @REG+1
 SBC ?JET_POSITIONS+1,X
 STA @REG+3         ; Jetzt sollte in (@REG+2) die linke obere Position sein
 STA @REG+5

 INC @REG+5
 INC @REG+5  ; (@REG+4) zeigt in die Mitte

; Das sind die Moeglichkeiten, wir kontrollieren die Mitte
; Second      first
; x  x  x     30 31 32
; 30 31 32    36 37 38
; 36 37 38    x  x  x

 LDY #0
 LDA (@REG+4),Y
 CMP #30
 BEQ ?SMALL_JET_EXPLOSION_SECOND_CASE

 CMP #36
 BEQ ?SMALL_JET_EXPLOSION_FIRST_CASE

?NORMAL_JET_EXPLOSION
 LDX #0
 JSR ?REPLACE_ONE_LINE
 INC @REG+3
 INC @REG+3
 JSR ?REPLACE_ONE_LINE
 INC @REG+3
 INC @REG+3
 JSR ?REPLACE_ONE_LINE

 LDY #1
 RTS

?SMALL_JET_EXPLOSION_SECOND_CASE
 INC @REG+3
 INC @REG+3
?SMALL_JET_EXPLOSION_FIRST_CASE
 LDX #0
 JSR ?REPLACE_ONE_LINE
 INC @REG+3
 INC @REG+3
 INX
 INX
 INX
 JSR ?REPLACE_ONE_LINE

 LDY #1
 RTS

?REPLACE_ONE_LINE
 LDY #0
 LDA ?REPLACE_WITH_EXPLOSION,X
 STA (@REG+2),Y
 INY
 INX
 LDA ?REPLACE_WITH_EXPLOSION,X
 STA (@REG+2),Y
 INY
 INX
 LDA ?REPLACE_WITH_EXPLOSION,X
 STA (@REG+2),Y
 INX
 RTS

; 15 16 hochhaus
; 19 20
; 22 23
; 48 49 50 Strommast
; 103 104 Funkantenne
; 106 107

; 121 Landebahn

; 124 Stern
