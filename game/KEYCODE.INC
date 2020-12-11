; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Keycode translator
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;

; give a keycode, get a key value only for some keys
@getKeyFromKeyCode
 LDY #1
 LDA (@HEAP_PTR),Y

 LDX #0
 CMP #28
 BNE ?not_escape

 LDY #27
 RTS

?not_escape
 CMP #142
 BNE ?not_up

 LDY #28 ; up
 RTS

?not_up
 CMP #143
 BNE ?not_down

 LDY #29 ; down
 RTS

?not_down
 CMP #135
 BNE ?not_right

 LDY #31 ; right
 RTS

?not_right
 CMP #134
 BNE ?not_left

 LDY #30 ; left
 RTS

?not_left
 CMP #33
 BNE ?not_space

 LDY #32
 RTS

?not_space
 LDY #0
 RTS
