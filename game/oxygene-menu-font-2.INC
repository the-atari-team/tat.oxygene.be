; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

; Der Oxygene Menu Font
; nur 512 Bytes, da für Graphics 1

  *=$CA00 ; MEMORY_OXYGENE_MENU_FONT

; der Oxygene font ist eine Mischung aus Comp2, Computer10, data, digi und eigenen Ideen/Vorlieben
; Oxygene Menu Font 2
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000

.byte ~00111000 ; ! eigen
.byte ~00111000
.byte ~00111000
.byte ~00011000
.byte ~00000000
.byte ~00011000
.byte ~00011000
.byte ~00000000

.byte ~00000000 ; tuettel idee data
.byte ~11101110
.byte ~10101010
.byte ~11101110
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000

.byte ~11111010 ; # Jet
.byte ~01100000
.byte ~11111100
.byte ~11000110
.byte ~11111100
.byte ~01100000
.byte ~11111010
.byte ~00000000

.byte ~00111100 ; $ Enemy
.byte ~01010010
.byte ~00111000
.byte ~11111100
.byte ~00111000
.byte ~01010010
.byte ~00111100
.byte ~00000000

.byte ~01111100 ; % Timer
.byte ~11000110
.byte ~10010010
.byte ~10011010
.byte ~10000010
.byte ~11000110
.byte ~01111100
.byte ~00000000

.byte ~00000000 ; & Timer full
.byte ~10101010
.byte ~10101010
.byte ~10101010
.byte ~10101010
.byte ~10101010
.byte ~10101010
.byte ~00000000

.byte ~00000000 ; ' data
.byte ~00111000
.byte ~00101000
.byte ~00111000
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00000000

.byte ~00111100 ; ( comp2
.byte ~00110000
.byte ~00110000
.byte ~00110000
.byte ~01110000
.byte ~01110000
.byte ~01111100
.byte ~00000000

.byte ~01111000 ; ) comp2
.byte ~00011000
.byte ~00011000
.byte ~00011000
.byte ~00011100
.byte ~00011100
.byte ~01111100
.byte ~00000000

.byte ~00000000 ; * eigen
.byte ~00000000
.byte ~01111000
.byte ~11001100
.byte ~11101100
.byte ~01111000
.byte ~00000000
.byte ~00000000

.byte ~11111000 ; plus 10 Teil von 'no0' eigen
.byte ~10001000
.byte ~10001001
.byte ~10001010
.byte ~11001010
.byte ~11001010
.byte ~11001001
.byte ~00000000

.byte ~00000000 ; komma data
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00111000
.byte ~00101000
.byte ~00111000
.byte ~01100000

.byte ~00000000 ; minus data
.byte ~00000000
.byte ~00000000
.byte ~01111110
.byte ~01111000
.byte ~00000000
.byte ~00000000
.byte ~00000000

.byte ~00000000 ; Punkt data
.byte ~00000000
.byte ~00000000
.byte ~00000000
.byte ~00111000
.byte ~00101000
.byte ~00111000
.byte ~00000000

.byte ~00000110 ; slash digi
.byte ~00001110
.byte ~00011100
.byte ~00111000
.byte ~01110000
.byte ~11100000
.byte ~11000000
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000110
.byte ~11000110
.byte ~11001110
.byte ~11001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~00011000 ; data
.byte ~00011000
.byte ~00011000
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000110
.byte ~00000110
.byte ~11111110
.byte ~11100000
.byte ~11100000
.byte ~11111110
.byte ~00000000

.byte ~11111100 ; data
.byte ~11001100
.byte ~00001100
.byte ~00111110
.byte ~00001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11111100 ; digi
.byte ~11001100
.byte ~11001100
.byte ~11001100
.byte ~11111110
.byte ~00011100
.byte ~00011100
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000000
.byte ~11000000
.byte ~11111110
.byte ~00001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11111000 ; comp2
.byte ~11011000
.byte ~11000000
.byte ~11111110
.byte ~11001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; data
.byte ~00000110
.byte ~00000110
.byte ~00001110
.byte ~00001110
.byte ~00001110
.byte ~00001110
.byte ~00000000

.byte ~01111110 ; eigen
.byte ~01100110
.byte ~01100110
.byte ~11111110
.byte ~11001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; digi
.byte ~11000110
.byte ~11000110
.byte ~11111110
.byte ~00001110
.byte ~00001110
.byte ~00001110
.byte ~00000000

.byte ~00111000 ; : data
.byte ~00101000
.byte ~00111000
.byte ~00000000
.byte ~00111000
.byte ~00101000
.byte ~00111000
.byte ~00000000

.byte ~00111000 ; ; data
.byte ~00101000
.byte ~00111000
.byte ~00000000
.byte ~00111000
.byte ~00101000
.byte ~00111000
.byte ~01100000

.byte ~00000000 ; < timer 3/4
.byte ~00101010
.byte ~00101010
.byte ~00101010
.byte ~00101010
.byte ~00101010
.byte ~00101010
.byte ~00000000

.byte ~00000000 ; = timer 2/4
.byte ~00001010
.byte ~00001010
.byte ~00001010
.byte ~00001010
.byte ~00001010
.byte ~00001010
.byte ~00000000

.byte ~00000000 ; > timer 1/4
.byte ~00000010
.byte ~00000010
.byte ~00000010
.byte ~00000010
.byte ~00000010
.byte ~00000010
.byte ~00000000

.byte ~11111110 ; ? data
.byte ~00000110
.byte ~00000110
.byte ~11111110
.byte ~11100000
.byte ~00000000
.byte ~11100000
.byte ~11100000

.byte ~11111110 ; @ eigen
.byte ~11000110
.byte ~11000110
.byte ~11101010
.byte ~11101110
.byte ~11100000
.byte ~11111110
.byte ~00000000

.byte ~01111110 ; A comp2
.byte ~01100110
.byte ~01100110
.byte ~11111110
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~00000000

.byte ~11111100 ; comp2
.byte ~11001100
.byte ~11001100
.byte ~11111110
.byte ~11001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000110
.byte ~11000000
.byte ~11100000
.byte ~11100000
.byte ~11100110
.byte ~11111110
.byte ~00000000

.byte ~11111100 ; computer10
.byte ~11001100
.byte ~11001100
.byte ~11101110
.byte ~11101110
.byte ~11101110
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000000
.byte ~11000000
.byte ~11111100
.byte ~11100000
.byte ~11100000
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; comp2
.byte ~11000000
.byte ~11000000
.byte ~11111100
.byte ~11100000
.byte ~11100000
.byte ~11100000
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000110
.byte ~11000000
.byte ~11101110
.byte ~11101110
.byte ~11100110
.byte ~11111110
.byte ~00000000

.byte ~11000110 ; data
.byte ~11000110
.byte ~11000110
.byte ~11111110
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~00000000

.byte ~00110000 ; data
.byte ~00110000
.byte ~00110000
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00000000

.byte ~00001100 ; data
.byte ~00001100
.byte ~00001100
.byte ~00001110
.byte ~00001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11001100 ; data
.byte ~11001100
.byte ~11001100
.byte ~11111110
.byte ~11111110
.byte ~11100110
.byte ~11100110
.byte ~00000000

.byte ~01100000 ; data
.byte ~01100000
.byte ~01100000
.byte ~01110000
.byte ~01110000
.byte ~01110000
.byte ~01111110
.byte ~00000000

.byte ~11111110 ; digi
.byte ~11001010
.byte ~11001010
.byte ~11100010
.byte ~11100010
.byte ~11100010
.byte ~11100010
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000110
.byte ~11000110
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~00000000

.byte ~11111110 ; data
.byte ~11001110
.byte ~11001110
.byte ~11000110
.byte ~11000110
.byte ~11000110
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; comp2
.byte ~11000110
.byte ~11000110
.byte ~11111110
.byte ~11100000
.byte ~11100000
.byte ~11100000
.byte ~00000000

.byte ~11111110 ; comp2
.byte ~11000110
.byte ~11000110
.byte ~11000110
.byte ~11001110
.byte ~11001110
.byte ~11111110
.byte ~00001110

.byte ~11111100 ; data
.byte ~11001100
.byte ~11001100
.byte ~11111110
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~00000000

.byte ~11111110 ; data
.byte ~11000110
.byte ~11000000
.byte ~11111110
.byte ~00001110
.byte ~11001110
.byte ~11111110
.byte ~00000000

.byte ~11111110 ; eigen
.byte ~00110000
.byte ~00110000
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00000000

.byte ~11000110 ; data
.byte ~11000110
.byte ~11000110
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~11111110
.byte ~00000000

.byte ~11100110 ; data
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~11101110
.byte ~01101100
.byte ~01111100
.byte ~00000000

.byte ~11000010 ; digi
.byte ~11000010
.byte ~11000010
.byte ~11101010
.byte ~11101010
.byte ~11101010
.byte ~11111110
.byte ~00000000

.byte ~11000110 ; digi
.byte ~11000110
.byte ~11000110
.byte ~01111100
.byte ~11100110
.byte ~11100110
.byte ~11100110
.byte ~00000000

.byte ~11000110 ; data
.byte ~11000110
.byte ~11000110
.byte ~11111110
.byte ~00111000
.byte ~00111000
.byte ~00111000
.byte ~00000000

.byte ~11111110 ; eigen
.byte ~11000110
.byte ~00001100
.byte ~00111000
.byte ~01100000
.byte ~11100110
.byte ~11111110
.byte ~00000000

.byte ~00011110 ; [ eigen
.byte ~00011100
.byte ~00011100
.byte ~00011000
.byte ~00011000
.byte ~00011000
.byte ~00011110
.byte ~00000000

.byte ~00011000 ; \ Joystick?
.byte ~00100100
.byte ~00011000
.byte ~00011000
.byte ~01111100
.byte ~10000010
.byte ~11111110
.byte ~00000000

.byte ~01111000 ; ] eigen
.byte ~00111000
.byte ~00111000
.byte ~00011000
.byte ~00011000
.byte ~00011000
.byte ~01111000
.byte ~00000000

.byte ~00000000 ; ^ (Ship)
.byte ~01000100
.byte ~10111010
.byte ~10000010
.byte ~10000010
.byte ~10000010
.byte ~01111100
.byte ~00000000

.byte ~00000000 ; _ 20 Teil von 'no0'
.byte ~00000000
.byte ~11000000
.byte ~01100000
.byte ~01101110
.byte ~00101010
.byte ~11001110
.byte ~00000000
