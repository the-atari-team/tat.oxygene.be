; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;RUNTIME-Library

  .LOCAL

; Das (Atari)Basic legt grundsätzlich ein Byte im Stack ab, der abgeholt werden muss
; das ist der Parametercount
; jeder Parameter legt 2 weitere Bytes im Stack ab, die geholt werden müssen.
; to use parameter from basic within compiler, insert the following line in your wnf file
; word array args[1] = @PARAMETER

@BASIC_MAIN
     PLA
     STA @PARAMETERCOUNT
     LDY #0
     TAX
?LOOP
     CPX #0
     BEQ ?REALMAIN
     PLA
     STA @PARAMETER+1,Y
     PLA
     STA @PARAMETER,Y
     INY
     INY
     DEX
     JMP ?LOOP
?REALMAIN
     INY

; Wir müssen Y auf den Heap-pointer addieren
     JMP @MAIN_FROM_BASIC

; Ruecksprung zum Aufrufer, Parameter legen wir in BININT ab
; Wir können hier auch mir JSR hineinspringen, weil TXS den Stack verbiegt ist das RTS ein Rücksprung ins Basic
@EXIT
      LDY #2
      LDA (@HEAP_PTR),Y ; Wert holen
      STA BININT+1
      DEY
      LDA (@HEAP_PTR),Y
      STA BININT

     LDX ?STACKPOINTER
     TXS

     RTS

; Here jump in with a address given in register X,Y (y+256*x)
@FUNCTION_POINTER
; doesn't work as expected, need fkt:=adr:ptr-1
;  TXA
;  PHA
;  TYA
;  PHA
;  RTS

; SMC-Code!
;  STY ?ADDRESS+1
;  STX ?ADDRESS+2
;?ADDRESS
;  JMP $4000

 STY @FKT_PTR
 STX @FKT_PTR+1
 JMP (@FKT_PTR)

; Hilfsroutine um an die Asserts zu kommen, die jeder fehlerhafte @Assert(condition) erzeugt.
@GETASSERTS
    LDY @ASSERT_FEHLER
    LDX @ASSERT_FEHLER+1
    RTS

; Add Akku zum Heap_Ptr, wird in Proceduren gebraucht, da add kommuntativ ist, einfach Heap_ptr addieren
@ADD_TO_HEAP_PTR
    CLC                ; 2
    ADC @HEAP_PTR      ; 3
    STA @HEAP_PTR      ; 3
    BCS ?INC_HEAD_PTR2 ; 2
    RTS                ; 6

?INC_HEAD_PTR2
    INC @HEAP_PTR+1    ; 1+5
    RTS                ; 6

; 2+3+3+2+(1+5)+6 => 16 Takte  + 2+6 => 8 (lda, jsr) (!) STA @REG kann raus, spart nochmal 3 Takte! (24 Takte)


; must be called with Akku set
@SUB_FROM_HEAP_PTR
    STA @REG

    SEC
    LDA @HEAP_PTR
    SBC @REG
    STA @HEAP_PTR
    BCC ?DEC_HEAD_PTR
    RTS

?DEC_HEAD_PTR
    DEC @HEAP_PTR+1
    RTS
; 3+2+3+3+3+2+(6)+6 => 22 Takte + 2+6 => 8 (lda, jsr) (30 Takte)

; Hilfsfunktion die den Compiler initialisiert
@HEAP_INIT
     STX ?STACKPOINTER

     LDA #<@HEAP_MEMORY
     STA @HEAP_PTR
     LDA #>@HEAP_MEMORY
     STA @HEAP_PTR+1

; TODO: Das löschen des ASSERT_FEHLERS sollte hier nicht gemacht werden
     LDA #0
     STA @ASSERT_FEHLER
     STA @ASSERT_FEHLER+1

; Wir kopieren in Basic die Parameter auf den Heap und verbiegen hier den Heap-Pointer
     TYA
     JMP @ADD_TO_HEAP_PTR

?STACKPOINTER
     .byte 0

@ASSERT_FEHLER
     .word 0

; macht aktuell ein paar Probleme
; .INCLUDE WINIFE_HEADER.INC

; Hier beginnt der Heap-Speicher, hier wollen wir Parameter fuer
; alle Funktionen ablegen
     .BYTE "HEAP"

@PARAMETERCOUNT
@HEAP_MEMORY
    .byte 0
@PARAMETER
    .BYTE $de,$ad,$be,$ef

; Hier hinter sollte niemals etwas stehen!
