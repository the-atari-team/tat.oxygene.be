; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

; Ein paar Routinen fuer den Compiler, die nur vom Spiel Oxygene verwendet werden
;

  .LOCAL

; statt @sleep(5), dies hier nutzen
; .if .ref @sleep5
@sleep5
 LDA #5

 LDY #1
 STA (@HEAP_PTR),Y
 JMP @pause
; .ENDIF
