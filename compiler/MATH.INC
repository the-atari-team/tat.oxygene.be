; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;MATH-Library

   .LOCAL

; SGN vorzeichen x * 256 + y := SGN(@REG1)
@SGN
@SGN_I
      LDY #2
      LDA (@HEAP_PTR),Y ; high wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y ; low wert holen
      STA @REG

      LDA @REG
      ORA @REG+1
      BEQ ?SGNZERO

      LDA @REG+1 ; Hole Vorzeichen
      BPL ?SGN1 ; --> nein

      LDY #255  ;negativ
      LDX #255
      RTS
;
?SGN1
      LDY #1    ;positiv
      LDX #0
      RTS
;
?SGNZERO
      LDY #0    ;Null
      LDX #0
      RTS

; Vorzeichen entfernen, immer positiv
@ABS
@ABS_I
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

       LDA @REG+1 ;Hole Vorzeichen
       BPL ?ABSPOSITIV ;  --> nein

       LDA @REG  ;Invertieren
       EOR #255
       STA @REG
       LDA @REG+1
       EOR #255
       STA @REG+1

        WINC  @REG

?ABSPOSITIV
       LDA @REG+1 ;loesche
       AND #$7F  ;Vorzeichen
       STA @REG+1

       LDY @REG
       LDX @REG+1
       RTS

; Negiert ein gegebenes Word
; ist das gleiche wie (x*256+y) := (x*256+y) * -1 nur schneller
@NEG
@NEG_I
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

; 16 bit Binary Negation
@NEG_INNER
       SEC             ;Ensure carry is set
       LDA #0          ;Load constant zero
       SBC @REG+0      ;... subtract the least significant byte
       TAY             ;... and store the result
       LDA #0          ;Load constant zero again
       SBC @REG+1      ;... subtract the most significant byte
       TAX             ;... and store the result

       RTS

; Convertiert vorzeichenrichtig ein Byte zu einem Word
; Der Compiler koennte es leisten, ist mir aber zu kompliziert
; Beim Ausfuehren weiss das Programm nichts mehr von byte oder word
@TOWORD
@TOWORD_I
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen (ein Byte)

      BMI ?NEGATIV
      TAY
      LDX #0
      RTS

?NEGATIV
      TAY
      LDX #$FF
      RTS

; liefert 1, wenn das uebergebene ungerade ist
@ODD
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen (ein Byte)
      AND #~00000001
      BNE ?TRUE
      JMP ?FALSE

; liefert 1, wenn das uebergebene gerade ist
@EVEN
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen (ein Byte)
      AND #~00000001
      BNE ?FALSE

?TRUE
      LDY #1
      LDX #0
      RTS

?FALSE
      LDY #0
      LDX #0
      RTS

