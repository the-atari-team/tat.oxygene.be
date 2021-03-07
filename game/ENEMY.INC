; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;ENEMY-Library
;
; Dies sind die Gegner aus dem alten Oxygene2 Game

 .local

; GRAFP0=$D00D
; GRAFM=$D012

; ---------------------------------------------------------------------------
; TODO: so umbauen, das nur ein Byte (PMField) genutzt wird, da das PM-Field sowieso nur an 2k Adressen ($800) liegen kann
;       und das hier schon berücksichtigt wird.
; Das hier arbeitet nur mit der feinen Auflösung richtig, die 2spaltigen Player sind kleiner
@CLEARPMFIELD
@CLEARPMFIELD_I
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
;      AND #~11111000
      TAX
;      DEY
;      LDA (@HEAP_PTR),Y
;      TAY
      LDY #0

; (x*256+y) ist der Wert im Heap
; sollten mit 0 gefüllt werden
      STY @REG
      STY @REG+2
      STY @REG+4
      STY @REG+6
      STY @REG+8

      STY GRAFP0     ; GTIA PM Register ebenfalls löschen
      STY GRAFP0+1
      STY GRAFP0+2
      STY GRAFP0+3
      STY GRAFM

      TXA
      CLC
      ADC #3     ; + 768
      STA @REG+1 ; missiles
      ADC #1
      STA @REG+3 ; p0
      ADC #1
      STA @REG+5 ; p1
      ADC #1
      STA @REG+7 ; p2
      ADC #1
      STA @REG+9 ; p3

; GANZ WICHTIG: Da unser PlayField an $F800 liegt, duerfen wir ab $FFFA nichts mehr loeschen!
      LDY #$F9
      LDA #0     ; Wert, der dort rein geschrieben wird 0!
?PMLOOP
      STA (@REG),Y ; Alle Missiles und Player in einem
      STA (@REG+2),Y
      STA (@REG+4),Y
      STA (@REG+6),Y
      STA (@REG+8),Y
      DEY
      BNE ?PMLOOP
      RTS

; ---------------------------------------------------------------------------
; @copyEnemy(@adrGegner(), Xpos, Ypos, anzahl Bytes)
; kopieren der Raumerdaten in den Player/Missile Bereich
; es muss mindestens einmal setraumernumber(x) aufgerufen worden sein

; (2) Startadresse player missiles
; (3) y pos
; (6) enemynummer 0-21 + 4 exp. + 1 empty

?ENEMY_XPOS
     .byte 0
?ENEMY_YPOS
     .byte 0

@CLEARENEMY
@CLEARENEMY_I
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
; (x*256+y) ist der Wert im Heap
; Start Adresse missiles
      STY @REG
      STX @REG+1 ; Player 0

; TODO: die Zahlen nochmal etwas genauer herausarbeiten, mal 255 einsetzen!

; Small speed up
;    9 zyklen extra fuer den ADC
; Statt 2496 Zyklen für 192 Zeilen
;       2112 ~384 gespart
; moeglich bei Dopplung: 1824 oder 288 gespart
; weiteres abstrippen 779 zyklen

      CLC        ; 32 Bytes weiter (Obere Kante)
      TYA
      ADC #32+32
      STA @REG

      LDY #160-12
      LDA #0
?PMLOOP2
      STA (@REG),Y   ; 6
      DEY            ; 2
      STA (@REG),Y   ; 6
      DEY            ; 2
      BNE ?PMLOOP2   ; 3

      RTS

; ---------------------------------------------------------------------------
@COPYENEMY
@COPYENEMY_III
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
; (x*256+y) ist der Wert im Heap
; Start Adresse missiles
      STY @REG
      INX
      STX @REG+1 ; Player 0

; x-position
;      LDY #3
;      LDA (@HEAP_PTR),Y
;      CLC
;      ADC #48     ; x-position, wo player beginnt (48)
;      STA ?EMEMY_XPOS
;
;      STA 53248  ; x-pos player 0

; y-position
      LDY #3
      LDA (@HEAP_PTR),Y
      CMP #255
      BEQ ?DO_NOTHING ; Emergency exit

      CLC
      ADC #32    ; y-position, wo player beginnt (32 leere Zeilen)
      STA ?ENEMY_YPOS

; Enemy Number
      LDY #6
      LDA (@HEAP_PTR),Y
      STA ?ENEMY_NUMMER+1
      DEY
      LDA (@HEAP_PTR),Y
      STA ?ENEMY_NUMMER

      ASL ?ENEMY_NUMMER
      ROL ?ENEMY_NUMMER+1
      ASL ?ENEMY_NUMMER
      ROL ?ENEMY_NUMMER+1
      ASL ?ENEMY_NUMMER
      ROL ?ENEMY_NUMMER+1
      ASL ?ENEMY_NUMMER
      ROL ?ENEMY_NUMMER+1

      CLC
      LDA #<@ENEMY0
      ADC ?ENEMY_NUMMER
      TAY
      LDA #>@ENEMY0
      ADC ?ENEMY_NUMMER+1
      TAX

; Selbstmodifizierender Code, igitt!
      STY ?ENEMY_NUMBER1+1
      STX ?ENEMY_NUMBER1+2

      LDY ?ENEMY_YPOS
      LDA #0
      STA (@REG),Y ; eine leere Zeile oben
      INY

      LDX #0
?COPYLOOP2
?ENEMY_NUMBER1
      LDA @ENEMY0,X
      STA (@REG),Y
      INY
      INX
      CPX #16
      BNE ?COPYLOOP2

      LDA #0       ; eine leere Zeile unten
      STA (@REG),Y
?DO_NOTHING
      RTS

?ENEMY_NUMMER
.word 0

@ENEMY0
; index 0
 .byte 0
 .byte ~00001000
 .byte ~00010100
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~00001000
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 1
 .byte 0
 .byte ~00010000
 .byte ~00011000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~00000100
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 2
 .byte 0
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~00000010
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 3
 .byte 0
 .byte ~00010000
 .byte ~00110000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~00000001
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 4
 .byte 0
 .byte ~00100000
 .byte ~01010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~10000000
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 5
 .byte 0
 .byte ~00010000
 .byte ~00110000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~01000000
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 6
 .byte 0
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~00100000
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0

; index 7
 .byte 0
 .byte ~00010000
 .byte ~00011000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00010000
 .byte ~00000000
 .byte ~00111100
 .byte ~11111111
 .byte ~00010000
 .byte ~11111111
 .byte ~01111110
 .byte ~00100100
 .byte ~11000011
 .byte 0


; index 8
; 8 Explosionen 0-7
@enemy_ship_explosion_0
 .byte ~00000000
 .byte ~00000000
 .byte ~00001000
 .byte ~01000010
 .byte ~01011010
 .byte ~00111101
 .byte ~01101100
 .byte ~01111110
 .byte ~01011010
 .byte ~10101100
 .byte ~00100100
 .byte ~01011010
 .byte ~01000010
 .byte ~00000100
 .byte ~00000000
 .byte ~00000000

; index 9
 .byte ~00000000
 .byte ~10000001
 .byte ~10100001
 .byte ~01010010
 .byte ~01001110
 .byte ~01110100
 .byte ~10100110
 .byte ~10011010
 .byte ~10011010
 .byte ~01100101
 .byte ~10100101
 .byte ~01001010
 .byte ~01011110
 .byte ~10101001
 .byte ~10010001
 .byte ~00000000

; index 10
 .byte ~00000000
 .byte ~10011101
 .byte ~10100111
 .byte ~01010010
 .byte ~11101111
 .byte ~01110101
 .byte ~10100111
 .byte ~10001011
 .byte ~11000010
 .byte ~01110101
 .byte ~10100101
 .byte ~01001010
 .byte ~01011110
 .byte ~10101011
 .byte ~10110101
 .byte ~00000000

; index 11
 .byte ~00000000
 .byte ~00011100
 .byte ~00100110
 .byte ~01010010
 .byte ~11101011
 .byte ~01010001
 .byte ~10000111
 .byte ~10111011
 .byte ~11001010
 .byte ~01010101
 .byte ~10000001
 .byte ~01011010
 .byte ~01011110
 .byte ~00101010
 .byte ~00110100
 .byte ~00000000

; index 12
 .byte ~00000000
 .byte ~00011001
 .byte ~10100000
 .byte ~00010010
 .byte ~01101010
 .byte ~01010000
 .byte ~00000110
 .byte ~00111000
 .byte ~01001010
 .byte ~01010110
 .byte ~10000001
 .byte ~01001010
 .byte ~01010000
 .byte ~00101010
 .byte ~10110100
 .byte ~00000000

; index 13
 .byte ~00000000
 .byte ~00001000
 .byte ~00000001
 .byte ~10000010
 .byte ~00101010
 .byte ~01000000
 .byte ~00000000
 .byte ~00100010
 .byte ~00010000
 .byte ~00000100
 .byte ~10100001
 .byte ~00000000
 .byte ~01000000
 .byte ~00001000
 .byte ~00000010
 .byte ~00000000

; index 14
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~01000000
 .byte ~00010100
 .byte ~00000000
 .byte ~00000000
 .byte ~00000010
 .byte ~10000000
 .byte ~00001000
 .byte ~00100000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000010
 .byte ~00000000

; index 15
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000

; Ab hier die alten Enemies

; vielfaches von 16
@enemy_ships_left

 .byte ~00001100
 .byte ~00011000
 .byte ~00011000
 .byte ~00110000
 .byte ~00110000
 .byte ~00110000
 .byte ~01011110
 .byte ~01111100
 .byte ~01011110
 .byte ~00110000
 .byte ~00110000
 .byte ~00110000
 .byte ~00011000
 .byte ~00011000
 .byte ~00001100
 .byte ~00000000


 .byte ~00000000
 .byte ~00000000
 .byte ~00111110
 .byte ~01001001
 .byte ~10001000
 .byte ~00011100
 .byte ~01110110
 .byte ~00111101
 .byte ~00111101
 .byte ~01110110
 .byte ~00011100
 .byte ~10001000
 .byte ~01001001
 .byte ~00111110
 .byte ~00000000
 .byte ~00000000


 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~01110000
 .byte ~10011000
 .byte ~00001100
 .byte ~00011110
 .byte ~00111011
 .byte ~00111101
 .byte ~00111011
 .byte ~00011110
 .byte ~00001100
 .byte ~10011000
 .byte ~01110000
 .byte ~00000000
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~00111000
 .byte ~01110100
 .byte ~11010010
 .byte ~00011001
 .byte ~00111100
 .byte ~01110110
 .byte ~00110011
 .byte ~01110110
 .byte ~00111100
 .byte ~00011001
 .byte ~11010010
 .byte ~01110100
 .byte ~00111000
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~01111110
 .byte ~00110000
 .byte ~00100000
 .byte ~01111000
 .byte ~10010100
 .byte ~01111010
 .byte ~01111010
 .byte ~10010100
 .byte ~01111000
 .byte ~00100000
 .byte ~00110000
 .byte ~01111110
 .byte ~00000000
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~01111000
 .byte ~11000100
 .byte ~11001000
 .byte ~00110000
 .byte ~01111000
 .byte ~01101100
 .byte ~00100110
 .byte ~01101100
 .byte ~01111000
 .byte ~00110000
 .byte ~11001000
 .byte ~11000100
 .byte ~01111000
 .byte ~00000000


 .byte ~00000000
 .byte ~01111100
 .byte ~10010010
 .byte ~00010000
 .byte ~00011000
 .byte ~00110000
 .byte ~00111000
 .byte ~01101100
 .byte ~11100111
 .byte ~01101100
 .byte ~00111000
 .byte ~00110000
 .byte ~00011000
 .byte ~00010000
 .byte ~10010010
 .byte ~01111100


 .byte ~00000000
 .byte ~00111110
 .byte ~01000001
 .byte ~10111101
 .byte ~11101010
 .byte ~00011000
 .byte ~00111100
 .byte ~01111111
 .byte ~01111111
 .byte ~00111100
 .byte ~00011000
 .byte ~11101010
 .byte ~10111101
 .byte ~01000001
 .byte ~00111110
 .byte ~00000000



 .byte ~00000000
 .byte ~00011000
 .byte ~00101100
 .byte ~01000110
 .byte ~10000011
 .byte ~00000110
 .byte ~00001111
 .byte ~00011101
 .byte ~00011101
 .byte ~00001111
 .byte ~00000110
 .byte ~10000011
 .byte ~01000110
 .byte ~00101100
 .byte ~00011000
 .byte ~00000000



 .byte ~00000000
 .byte ~00111100
 .byte ~01000010
 .byte ~01000001
 .byte ~00111110
 .byte ~00011000
 .byte ~00110100
 .byte ~01111010
 .byte ~01111010
 .byte ~00110100
 .byte ~00011000
 .byte ~00111110
 .byte ~01000001
 .byte ~01000010
 .byte ~00111100
 .byte ~00000000

 .byte ~00001110
 .byte ~00011000
 .byte ~00110000
 .byte ~00110000
 .byte ~01111100
 .byte ~11000110
 .byte ~10001101
 .byte ~11111001
 .byte ~10001101
 .byte ~11000110
 .byte ~01111100
 .byte ~00110000
 .byte ~00110000
 .byte ~00011000
 .byte ~00001110
 .byte ~00000000


 .byte ~01111100
 .byte ~10010010
 .byte ~00010000
 .byte ~00010000
 .byte ~00111000
 .byte ~01111110
 .byte ~10001011
 .byte ~11111001
 .byte ~10001011
 .byte ~01111110
 .byte ~00111000
 .byte ~00010000
 .byte ~00010000
 .byte ~10010010
 .byte ~01111100
 .byte ~00000000



@enemy_ships_right
 .byte ~00110000
 .byte ~00011000
 .byte ~00011000
 .byte ~00001100
 .byte ~00001100
 .byte ~00001100
 .byte ~01111010
 .byte ~00111110
 .byte ~01111010
 .byte ~00001100
 .byte ~00001100
 .byte ~00001100
 .byte ~00011000
 .byte ~00011000
 .byte ~00110000
 .byte ~00000000


 .byte ~00000000
 .byte ~00000000
 .byte ~01111100
 .byte ~10010010
 .byte ~00010001
 .byte ~00111000
 .byte ~01101110
 .byte ~10111100
 .byte ~10111100
 .byte ~01101110
 .byte ~00111000
 .byte ~00010001
 .byte ~10010010
 .byte ~01111100
 .byte ~00000000
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00001110
 .byte ~00011001
 .byte ~00110000
 .byte ~01111000
 .byte ~11011100
 .byte ~10111100
 .byte ~11011100
 .byte ~01111000
 .byte ~00110000
 .byte ~00011001
 .byte ~00001110
 .byte ~00000000
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~00011100
 .byte ~00101110
 .byte ~01001011
 .byte ~10011000
 .byte ~00111100
 .byte ~01101110
 .byte ~11001100
 .byte ~01101110
 .byte ~00111100
 .byte ~10011000
 .byte ~01001011
 .byte ~00101110
 .byte ~00011100
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~01111110
 .byte ~00001100
 .byte ~00000100
 .byte ~00011110
 .byte ~00101001
 .byte ~01011110
 .byte ~01011110
 .byte ~00101001
 .byte ~00011110
 .byte ~00000100
 .byte ~00001100
 .byte ~01111110
 .byte ~00000000
 .byte ~00000000



 .byte ~00000000
 .byte ~00000000
 .byte ~00011110
 .byte ~00100011
 .byte ~00010011
 .byte ~00001100
 .byte ~00011110
 .byte ~00110110
 .byte ~01100100
 .byte ~00110110
 .byte ~00011110
 .byte ~00001100
 .byte ~00010011
 .byte ~00100011
 .byte ~00011110
 .byte ~00000000



 .byte ~00000000
 .byte ~00111110
 .byte ~01001001
 .byte ~00001000
 .byte ~00011000
 .byte ~00001100
 .byte ~00011100
 .byte ~00110110
 .byte ~11100111
 .byte ~00110110
 .byte ~00011100
 .byte ~00001100
 .byte ~00011000
 .byte ~00001000
 .byte ~01001001
 .byte ~00111110



 .byte ~00000000
 .byte ~01111100
 .byte ~10000010
 .byte ~10111101
 .byte ~01010111
 .byte ~00011000
 .byte ~00111100
 .byte ~11111110
 .byte ~11111110
 .byte ~00111100
 .byte ~00011000
 .byte ~01010111
 .byte ~10111101
 .byte ~10000010
 .byte ~01111100
 .byte ~00000000



 .byte ~00000000
 .byte ~00011000
 .byte ~00110100
 .byte ~01100010
 .byte ~11000001
 .byte ~01100000
 .byte ~11110000
 .byte ~10111000
 .byte ~10111000
 .byte ~11110000
 .byte ~01100000
 .byte ~11000001
 .byte ~01100010
 .byte ~00110100
 .byte ~00011000
 .byte ~00000000


 .byte ~00000000
 .byte ~00111100
 .byte ~01000010
 .byte ~10000010
 .byte ~01111100
 .byte ~00011000
 .byte ~00101100
 .byte ~01011110
 .byte ~01011110
 .byte ~00101100
 .byte ~00011000
 .byte ~01111100
 .byte ~10000010
 .byte ~01000010
 .byte ~00111100
 .byte ~00000000


 .byte ~01110000
 .byte ~00011000
 .byte ~00001100
 .byte ~00001100
 .byte ~00111110
 .byte ~01100011
 .byte ~10110001
 .byte ~10011111
 .byte ~10110001
 .byte ~01100011
 .byte ~00111110
 .byte ~00001100
 .byte ~00001100
 .byte ~00011000
 .byte ~01110000
 .byte ~00000000


 .byte ~00111110
 .byte ~01001001
 .byte ~00001000
 .byte ~00001000
 .byte ~00011100
 .byte ~01111110
 .byte ~11010001
 .byte ~10011111
 .byte ~11010001
 .byte ~01111110
 .byte ~00011100
 .byte ~00001000
 .byte ~00001000
 .byte ~01001001
 .byte ~00111110
 .byte ~00000000


; --- SHOTS -----------------------------------------------------

@SHOT_YPOS
    .byte 0
@SHOT_XPOS
    .byte 0

@SHOT_NUMMER
    .word 0

@SETENEMYSHOTNUMBER
@SETENEMYSHOTNUMBER_I
; gewuenschte Shotnumber
      LDY #2
      LDA (@HEAP_PTR),Y
      STA @SHOT_NUMMER+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @SHOT_NUMMER
; * 8 (bytes)
      ASL @SHOT_NUMMER
      ROL @SHOT_NUMMER+1
      ASL @SHOT_NUMMER
      ROL @SHOT_NUMMER+1
      ASL @SHOT_NUMMER
      ROL @SHOT_NUMMER+1

      CLC
      LDA #<@SHOT0
      ADC @SHOT_NUMMER
      TAY
      LDA #>@SHOT0
      ADC @SHOT_NUMMER+1
      TAX

; Selbstmodifizierender Code, igitt!
      STY ?SHOT_NUMBER1+1
      STX ?SHOT_NUMBER1+2
      RTS

; ---------------------------------------------------------------------------
@COPYENEMYSHOT
@COPYENEMYSHOT_III
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

; (x*256+y) ist der Wert im Heap
; Start Adresse
      STY @REG   ; Missiles Adresse
      STX @REG+1

; x-position
      LDY #3
      LDA (@HEAP_PTR),Y
      CLC
      ADC #48     ; x-position
      STA @SHOT_XPOS
      STA @ENEMY_SHOT_XPOS ; x-pos missile 0 (Gegner)

;      STA 53252   ; x-pos missile 0 (Gegner)

; y-position
      LDY #5
      LDA (@HEAP_PTR),Y
      CLC
      ADC #32-3    ; y-position, wo player beginnt (32 - 3 leere Zeilen)
      ADC #10      ; Playerheight
      STA @SHOT_YPOS

      LDX #0
      LDY @SHOT_YPOS
?SHOTCOPYLOOP
      LDA (@REG),Y    ; Missile
      AND @SHOT_MASK
?SHOT_NUMBER1
      ORA @SHOT0,X
      STA (@REG),Y
      INY
      INX
      TXA
      CMP #6
      BNE ?SHOTCOPYLOOP

      RTS

; ---------------------------------------------------------------------------
; Loeschen des Enemy Shot Missiles
@CLEARENEMYSHOT
@CLEARENEMYSHOT_I
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen missile address
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
; (x*256+y) ist der Wert im Heap
; y-position
      CLC
      ADC #70     ; y-position, wo player beginnt (32 - 3 leere Zeilen)
      STA @REG

      LDY #152    ; 76
;      LDA @SHOT_MASK
;      STA @REG+2
?SHOTCLEARLOOP
      LDA (@REG),Y    ; Missile
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      LDA (@REG),Y    ; unroll loops (2x)
      AND #~11111100 ; @REG+2
;      ORA #~00000011
      STA (@REG),Y
      DEY

      BNE ?SHOTCLEARLOOP

      RTS

; Killer shot wenn es mal richtig boese zugehen soll...
@ENEMYSHOT_KILLER
@ENEMYSHOT_KILLER_IIII
      LDY #2
      LDA (@HEAP_PTR),Y
      STA @REG+1        ; Missiles Adresse
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG          ; Missiles Adresse

; x-position
      LDY #3
      LDA (@HEAP_PTR),Y
      CLC
      ADC #48     ; x-position
;      STA @SHOT_XPOS

;      STA 53252   ; x-pos missile 0 (Gegner)
      STA @ENEMY_SHOT_XPOS ; x-pos missile 0 (Gegner)

; y-position oben
      LDY #5
      LDA (@HEAP_PTR),Y ; wert holen
      CLC
      ADC #32      ; y-position, wo player beginnt (32)
      STA @REG+4 ; @ES_OBEN

; y-position unten
      LDY #7
      LDA (@HEAP_PTR),Y ; wert holen
      CLC
      ADC #32      ; y-position, wo player beginnt (32)

      CMP #210
      BCC ?SMALLER_THEN_210
      LDA #210

?SMALLER_THEN_210
      STA @REG+5 ; @ES_UNTEN

      LDY @REG+4 ; @ES_OBEN

      CPY #72
      BCS ?GREATER_THEN_72

      LDY #72

?GREATER_THEN_72
      LDA @SHOT_MASK
      STA @REG+6

?ES_KILLER_LOOP
      LDA RANDOM
      AND #~00000011
      STA @REG+2

      LDA (@REG),Y    ; Missile
      AND @REG+6    ; @SHOT_MASK
      ORA @REG+2
      STA (@REG),Y
      INY

      LDA (@REG),Y    ; Missile
      AND @REG+6    ; @SHOT_MASK
      STA (@REG),Y

      INY
      CPY @REG+5 ; @ES_UNTEN
      BCC ?ES_KILLER_LOOP

      RTS

;@ES_OBEN
;      .byte 0
;@ES_UNTEN
;      .byte 0

@SHOT_MASK
      .byte ~11111100

@SHOT0
      .byte ~00000000
      .byte ~00000001
      .byte ~00000001
      .byte ~00000001
      .byte ~00000001
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000001
      .byte ~00000001
      .byte ~00000010
      .byte ~00000010
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000011
      .byte ~00000011
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000010
      .byte ~00000010
      .byte ~00000001
      .byte ~00000001
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000010
      .byte ~00000010
      .byte ~00000010
      .byte ~00000010
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000001
      .byte ~00000001
      .byte ~00000010
      .byte ~00000010
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000011
      .byte ~00000011
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

      .byte ~00000000
      .byte ~00000010
      .byte ~00000010
      .byte ~00000001
      .byte ~00000001
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

@DOUBLE_SHOT0
      .byte ~00000000
      .byte ~00000011
      .byte ~00000000
      .byte ~00000000
      .byte ~00000011
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000

; index 9
@SHOT_EMPTY0
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
      .byte ~00000000
