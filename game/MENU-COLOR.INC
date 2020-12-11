; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Game Mission
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;

 .local

; @generateColorList(adr:menucolorlist)
@generateColorList
 LDY #2
 LDA (@HEAP_PTR),Y ; wert holen
 STA @REG+1
 DEY
 LDA (@HEAP_PTR),Y ; wert holen
 STA @REG

 LDX #3
 LDY #0
?NEXT_COLOR_LOOP
 LDA (@REG),Y
 AND #$F0
 STA ?COLOR

 LDA @MENUCOLOR,X
?LOOP
 AND #$0F          ; weg mit der Farbe
 ORA ?COLOR
 STA @MENUCOLOR,X

 INX
 LDA @MENUCOLOR,X
 BNE ?LOOP

 INY
 INX
 INX
 CPX #130
 BMI ?NEXT_COLOR_LOOP

 RTS

?COLOR
 .byte 0
