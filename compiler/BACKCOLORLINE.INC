; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;BASIC-Library
;

  .LOCAL

; @backcolorline(color) setzt die Hintergrundfarbe auf color in exakt der Bildschirmzeile
; in der sich der Elektronenstrahl gerade befindet.
; .IF .REF @backcolorline
@backcolorline
 LDY #1
 LDA (@HEAP_PTR),Y

 STA WSYNC

 LDX 712 ; COLOR0+4
 STA COLBK
 STA WSYNC

 STX COLBK
 RTS
; .ENDIF
