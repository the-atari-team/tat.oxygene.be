; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;MATH-Library

   .LOCAL

; @shiftright(value, bits)
; shifted value um bits nach rechts (1 bit entspricht geteilt durch 2, 2 bits entspricht geteilt durch 4)
@shiftright
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
; (x*256+y) ist der Wert im Heap
      STY @REG
      STX @REG+1

      LDY #3
      LDA (@HEAP_PTR),Y ; wert holen
      AND #$0F       ; maxvalue ist 15
      TAX
      BEQ ?NO_SHIFTRIGHT

?SHIFTRIGHT_LOOP
      LSR @REG+1 ;verschiebe
      ROR @REG
      DEX
      BNE ?SHIFTRIGHT_LOOP

?NO_SHIFTRIGHT
      LDY @REG
      LDX @REG+1
      RTS

; @shiftleft(value, bits)
; shifted value um bits nach links (1 bit entspricht mult mit 2, 2 bits entspricht mult mit 4)
@shiftleft
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG
; (x*256+y) ist der Wert im Heap

      LDY #3
      LDA (@HEAP_PTR),Y ; wert holen
      AND #$0F       ; maxvalue ist 15
      TAX
      BEQ ?NO_SHIFTRIGHT

?SHIFTLEFT_LOOP
      ASL @REG
      ROL @REG+1
      DEX
      BNE ?SHIFTLEFT_LOOP

      LDY @REG
      LDX @REG+1
      RTS
