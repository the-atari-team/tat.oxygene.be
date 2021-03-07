; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

; BASIC-Library

    .LOCAL

; Genau drauf achten, das immer X das hoeherwertige Byte nimmt

; Der WiNiFe-Compiler kann Variablen deklarieren mit dem Speicherort.
; byte hintergrundfarbe=712
; hintergrundfarbe:=10          // setzt die hintergrundfarbe
; irgendwas := hintergrundfarbe // weisst den Inhalt der Hintergrundfarbe zu
;
; Deshalb sind das hier eigentlich voellig unnoetige Routinen und nur der Vollstaendigkeit halber da

; Hole ein Byte aus dem Speicher, wie in Basic
; .IF .REF @PEEK
@PEEK
@peek_i
 LDY #2
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG

; get Value out of memory
 LDY #0
 LDA (@REG),Y
 TAY
 LDX #0
 RTS
; .ENDIF

@POKE
@POKE_II
 LDY #2
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG

; get Value out of memory
 LDY #3
 LDA (@HEAP_PTR),Y

 LDY #0
 STA (@REG),Y
 RTS


; Hole ein Byte aus dem Speicher, wie in Basic
;  .IF .REF @DPEEK
@DPEEK
 LDY #2
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG

;(x*256+y)

; get Value out of memory
 LDY #1
 LDA (@REG),Y
 TAX
 DEY
 LDA (@REG),Y
 TAY
 RTS
; .ENDIF
