; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

 .local

; This functions compare 16bit values in unsigned manner on 6502
; They return 1 if a compare is true
; These functions are not the fastest, they are very short and can
; used in @assertThat(...) function

; @inrange(value, low, high)
; returns 1, when value is in interval [low, high], low and high included.
; not perfect fast, but works as expected
?value=@reg
?low=@reg+2
?high=@reg+4

@inRange
@inRange_iii
  jsr ?twoParameters

  jsr ?regLTxy      ; value < low
  cpy #1
  beq ?false        ; --> not in Range

  LDY #5
  LDA (@HEAP_PTR),Y
  STA @REG
  INY
  LDA (@HEAP_PTR),Y
  STA @REG+1

  LDY #2
  LDA (@HEAP_PTR),Y
  TAX
  DEY
  LDA (@HEAP_PTR),Y
  TAY

  jsr ?regLTxy      ; high < value
  cpy #1
  bne ?true
  beq ?false

;@greaterEqual(first, second)
; returns 1, when first >= second
@GE
@GE_ii
@greaterEqual
@greaterEqual_ii
      jsr ?twoParameters

; @REG >= (x*256+y)
; reg - xy (reg <= xy => C=0)
      cpy @reg
      bne ?false_ge
      cpx @reg+1
      beq ?true

?false_ge
      CPY @REG
      TXA
      SBC @REG+1
      BCS ?false

;      jmp ?false

?true
      LDY #1
      LDX #0
      RTS

?false
      LDY #0
      LDX #0
      RTS


;@greaterThan(first, second)
; returns 1, when first > second
@GT
@GT_ii
@greaterThan
@greaterThan_ii
      jsr ?twoParameters

; @REG >= (x*256+y)
      CPY @REG
      TXA
      SBC @REG+1
      BCS ?false
      jmp ?true


;@lessThan(first, second)
; returns 1, when first < second ist
@LT
@LT_ii
@lessThan
@lessThan_ii
      jsr ?twoParameters

?regLTxy
      cpy @REG
      bne ?false_lt
      cpx @reg+1
      beq ?false    ; wenn reg == xy --> false

?false_lt

; @REG < (x*256+y)
      CPY @REG
      TXA
      SBC @REG+1
      BCC ?false    ; reg >= xy --> false (equal we check before)

      bcs ?true

;@lessEqual(first, second)
; returns 1, when first <= second ist
@LE
@LE_ii
@lessEqual
@lessEqual_ii
      jsr ?twoParameters

; @REG <= (x*256+y)
      CPY @REG
      TXA
      SBC @REG+1
      BCC ?false    ; reg >= xy --> false
      jmp ?true


; @equal(first, second)
; returns 1, when first == second
@eq
@eq_ii
@equal
@equal_ii
  jsr ?twoParameters

; @REG == (x*256+y)
  cpy @REG
  bne ?false
  cpx @REG+1
  bne ?false
  beq ?true

; @notequal(first, second)
; returns 1, when first != second
@ne
@ne_ii
@notequal
@notequal_ii
  jsr ?twoParameters

; @REG != (x*256+y)
  cpy @REG
  bne ?true
  cpx @REG+1
  bne ?true
  beq ?false

; Get 2 parameter from our Heap
; 1. parameter is put in memory @REG
; 2. parameter is put in register (x*256+y)
?twoParameters
      LDY #1            ; read parameter forward
      LDA (@HEAP_PTR),Y
      STA @REG
      INY
      LDA (@HEAP_PTR),Y
      STA @REG+1

      LDY #4            ; read parameter backwards
      LDA (@HEAP_PTR),Y ; to store in x,y registers
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
      RTS

; found: https://www.codebase64.org/doku.php?id=base:16-bit_comparison
; /*! «»«»«»«»{CMP16}«»«»«»«»
;     Does exactly the same as CMP of two values (effectively its a val1-val2) and sets the flags as follows:
;
;                        (BCC/BCS)      (BEQ/BNE)      (BMI/BPL)
;     If val1 = val2 : Carry =  SET   Zero =  SET   Negative = CLEAR
;     If val1 > val2 : Carry =  SET   Zero = CLEAR  Negative = CLEAR
;     If val1 < val2 : Carry = CLEAR  Zero = CLEAR  Negative =  SET
; */
;
;     lda val1
;     sec
;     sbc val2
;     php
;     lda val1+1
;     sbc val2+1
;     php
;     pla
;     sta temp
;     pla
;     and #%00000010
;     ora #%11111101
;     and temp
;     pha
;     plp
;
; >42 cycles, expensive!
;
; Somewhere on ZP:
; temp:
;     .byte $00


; Different approach: instead of setting flags, goes to different destinations:
; ; Val1 ≥ Val2 ?
;   LDA Val1 +1    ; high bytes
;   CMP Val2+1
;   BCC LsThan     ; hiVal1 < hiVal2 --> Val1 < Val2
;   BNE GrtEqu     ; hiVal1 ≠ hiVal2 --> Val1 > Val2
;   LDA Val1       ; low bytes
;   CMP Val2
;   ;BEQ Equal     ; Val1 = Val2
;   BCS GrtEqu     ; loVal1 ≥ loVal2 --> Val1 ≥ Val2
; LsThan
; ...
; GrtEqu
; ...
; 21 cycles

