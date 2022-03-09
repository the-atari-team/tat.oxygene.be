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
; Deshalb sind @peek(addr) & @poke(addr, value) hier eigentlich
; voellig unnoetige Routinen und nur der Vollstaendigkeit halber da
; wir brauchen diese, da wir sonst nicht mit einenem Namen an den Wert kommen
; ein &NAME gibt es halt noch nicht im Compiler

; Hole ein Byte aus dem Speicher, wie in Basic
; .IF .REF @PEEK
@PEEK
@PEEK_I
@GETBYTE
@GETBYTE_I
 LDY #2
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG

; get Value out of memory
; LDY #0
 DEY
 LDA (@REG),Y
 TAY
 LDX #0
 RTS
; .ENDIF

; set a byte into memory
; @poke(address, byte)
; @setbyte(address, byte) is like @setbytearray(address,0,byte)
@POKE
@POKE_II
@SETBYTE
@SETBYTE_II
 LDY #1
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+1

; get Value out of memory
; LDY #3
 INY
 LDA (@HEAP_PTR),Y

 LDY #0
 STA (@REG),Y
 RTS


; Hole ein Word aus dem Speicher, wie in Basic
; value := @dpeek(addr) // ist in C value = *addr

;  .IF .REF @DPEEK
@ADDRESS               ; little bit more clear in word
@ADDRESS_I
@GETWORD
@GETWORD_I
@DPEEK
@DPEEK_I
 LDY #1
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+1

;(x*256+y)

; get Value out of memory
; LDY #1
 DEY
 LDA (@REG),Y
 TAX
 DEY
 LDA (@REG),Y
 TAY
 RTS
; .ENDIF
