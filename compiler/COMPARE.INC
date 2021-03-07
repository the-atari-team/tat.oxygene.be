; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

 .local

;@greaterThan(endaddress, $c000)
@greaterThan
@greaterThan_ii
      LDY #2
      LDA (@HEAP_PTR),Y
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

      LDY #4
      LDA (@HEAP_PTR),Y
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

; @REG OP (x*256+y)
      CPY @REG
      TXA
      SBC @REG+1
      BCS ?false

      LDY #1
      LDX #0
      RTS

?false
      LDY #0
      LDX #0
      RTS
