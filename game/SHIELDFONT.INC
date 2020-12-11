; -*- text-mode -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

; Fuer den Shield-Font brauchen wir nur ein paar Zeichen,
; Ein Font belegt aber immer 1024 bytes
; Wir stellen den also auf $F800, nutzen die ersten 512 Bytes aber noch
; fuer das Ship und erst danach kommen die Shield-Zeichen
;
; Clou: Die Player Missile Grafik hat am Anfang 768 leerbytes, hier passt exact
; der Shield-Font nebst der Zeile zum Anzeigen des Shields hinein
;  .byte $42
;   .word $fad8

; Die Daten der Playermissile Grafik beginnt dann ab
; $FB00 (Missiles)
; $FC00 (Player 0)
; $FD00 (Player 1)
; $FE00 (Player 2)
; $FF00 (Player 3)

 *=$F800

 *=* + 8*64

; Zeichen 64
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000

; *=* + 16 *8 Zahlen

; *=* + 8*32

; Zeichen 65

; color 2 stellt ganz dunkles grau dar, hintergrund fuer player 0
 .byte ~00000000
 .byte ~00100010
 .byte ~00100010
 .byte ~00100010
 .byte ~00100010
 .byte ~00100010
 .byte ~00100010
 .byte ~00000000

; color 2-3 macht keinen Sinn

; color 3 Farbe rot
 .byte ~00000000
 .byte ~00110011
 .byte ~00110011
 .byte ~00110011
 .byte ~00110011
 .byte ~00110011
 .byte ~00110011
 .byte ~00000000

; color 3-4
 .byte ~00000000
 .byte ~00110100
 .byte ~01000011
 .byte ~00110100
 .byte ~01000011
 .byte ~00110100
 .byte ~01000011
 .byte ~00000000

; color 4
 .byte ~00000000
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100
 .byte ~01000100
 .byte ~00000000

; color 4-5
 .byte ~00000000
 .byte ~01000101
 .byte ~01010100
 .byte ~01000101
 .byte ~01010100
 .byte ~01000101
 .byte ~01010100
 .byte ~00000000

; color 5
 .byte ~00000000
 .byte ~01010101
 .byte ~01010101
 .byte ~01010101
 .byte ~01010101
 .byte ~01010101
 .byte ~01010101
 .byte ~00000000

; color 5-6
 .byte ~00000000
 .byte ~01010110
 .byte ~01100101
 .byte ~01010110
 .byte ~01100101
 .byte ~01010110
 .byte ~01100101
 .byte ~00000000

; color 6
 .byte ~00000000
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~00000000

; color 6-7
 .byte ~00000000
 .byte ~01100111
 .byte ~01110110
 .byte ~01100111
 .byte ~01110110
 .byte ~01100111
 .byte ~01110110
 .byte ~00000000

; color 7
 .byte ~00000000
 .byte ~01110111
 .byte ~01110111
 .byte ~01110111
 .byte ~01110111
 .byte ~01110111
 .byte ~01110111
 .byte ~00000000

; color 7-8
 .byte ~00000000
 .byte ~01111000
 .byte ~10000111
 .byte ~01111000
 .byte ~10000111
 .byte ~01111000
 .byte ~10000111
 .byte ~00000000

; color 8 farbe gruen
 .byte ~00000000
 .byte ~10001000
 .byte ~10001000
 .byte ~10001000
 .byte ~10001000
 .byte ~10001000
 .byte ~10001000
 .byte ~00000000

; rechts jetzt immer 2

; color 3-2
 .byte ~00000000
 .byte ~00110010
 .byte ~00110010
 .byte ~00110010
 .byte ~00110010
 .byte ~00110010
 .byte ~00110010
 .byte ~00000000

; color 3-4-2
 .byte ~00000000
 .byte ~00110010
 .byte ~01000010
 .byte ~00110010
 .byte ~01000010
 .byte ~00110010
 .byte ~01000010
 .byte ~00000000

; color 4-2
 .byte ~00000000
 .byte ~01000010
 .byte ~01000010
 .byte ~01000010
 .byte ~01000010
 .byte ~01000010
 .byte ~01000010
 .byte ~00000000

; color 4-5-2
 .byte ~00000000
 .byte ~01000010
 .byte ~01010010
 .byte ~01000010
 .byte ~01010010
 .byte ~01000010
 .byte ~01010010
 .byte ~00000000

; color 5-2
 .byte ~00000000
 .byte ~01010010
 .byte ~01010010
 .byte ~01010010
 .byte ~01010010
 .byte ~01010010
 .byte ~01010010
 .byte ~00000000

; color 5-6-2
 .byte ~00000000
 .byte ~01010010
 .byte ~01100010
 .byte ~01010010
 .byte ~01100010
 .byte ~01010010
 .byte ~01100010
 .byte ~00000000

; color 6-2
 .byte ~00000000
 .byte ~01100010
 .byte ~01100010
 .byte ~01100010
 .byte ~01100010
 .byte ~01100010
 .byte ~01100010
 .byte ~00000000

; color 6-7-2
 .byte ~00000000
 .byte ~01100010
 .byte ~01110010
 .byte ~01100010
 .byte ~01110010
 .byte ~01100010
 .byte ~01110010
 .byte ~00000000

; color 7-2
 .byte ~00000000
 .byte ~01110010
 .byte ~01110010
 .byte ~01110010
 .byte ~01110010
 .byte ~01110010
 .byte ~01110010
 .byte ~00000000

; color 7-8-2
 .byte ~00000000
 .byte ~01110010
 .byte ~10000010
 .byte ~01110010
 .byte ~10000010
 .byte ~01110010
 .byte ~10000010
 .byte ~00000000

; color 8-2
 .byte ~00000000
 .byte ~10000010
 .byte ~10000010
 .byte ~10000010
 .byte ~10000010
 .byte ~10000010
 .byte ~10000010
 .byte ~00000000

