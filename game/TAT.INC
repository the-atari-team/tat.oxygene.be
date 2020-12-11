 .local
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

; TAT sign in player-missile grafik.
; Es werden ALLE Player und Missiles verwendet.

; Adresse Hardcode fuer Oxygene2
?PLAYER0 = $F800+$400
?MISSILES = $F800+$300

@set_tat_in_player
 LDX #22              ; Y-Position des TAT Zeichens
 LDY #0               ; Position in der Liste

?LOOP
 LDA ?T,Y             ; Player T 2x
 STA ?PLAYER0,X
 STA ?PLAYER0+$100,X
 LDA ?A,Y             ; Player A
 STA ?PLAYER0+$200,X

 LDA ?INNER_A,Y       ; Player A innen
 STA ?PLAYER0+$300,X

 LDA ?INNER_T,Y       ; Missiles innen (brauchen doppelte Breite!)
 STA ?MISSILES,X
 INX
 INY
 CPY #8
 BNE ?LOOP
 RTS

?T
 .byte ~01111110
 .byte ~10000001
 .byte ~01100110
 .byte ~00100100
 .byte ~00100100
 .byte ~00100100
 .byte ~00100100
 .byte ~00011000

?A
 .byte ~00011000
 .byte ~00100100
 .byte ~00100100
 .byte ~01000010
 .byte ~01011010
 .byte ~10000001
 .byte ~10011001
 .byte ~01100110

;
; Missiles, Player 3
; die Missiles brauchen die doppelte Breite

?INNER_T
 .byte 0
 .byte ~11101110
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100

?INNER_A
 .byte 0
 .byte ~00011000
 .byte ~00011000
 .byte ~00111100
 .byte ~00100100
 .byte ~01111110
 .byte ~01100110
 .byte 0
