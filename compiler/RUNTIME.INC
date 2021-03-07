; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;RUNTIME-Library
;fuer den WiNiFe-Compiler

  .LOCAL

; In Atari-Basic a USR(address) call, put always one byte onto the stack
; this is the value of how much parameters will follow.
; Every parameter puts 2 more bytes to the stack. This parameters
; need to pull from stack.
; To use parameter from Basic within this compiler,
; insert the following line in your wnf file
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

; We need to add Y-Register to the Heap-pointer
     JMP @MAIN_FROM_BASIC

; Callback function to the caller.
; Within Atari-Basic there is one return parameter possible.
; This value need to be in BININT
; We can call this function by JSR, because the last TXS set the stack
; to the position at INIT_RUNTIME time. The RTS takes the jump
; back to Basic
@EXIT
@EXIT_I
      LDY #1
      LDA (@HEAP_PTR),Y ; Wert holen
      STA BININT
      INY
      LDA (@HEAP_PTR),Y
      STA BININT+1

 .IF .DEF @INIT_BREAKKEY
  jsr @RESTORE_BREAKKEY
 .ENDIF

      LDX ?STACKPOINTER
      TXS
      RTS

; function pointer call
; @(fkt)(...)
; Here jump in with a address given in register X,Y (y+256*x)
@FUNCTION_POINTER

; Some old ideas, not taken
; Doesn't work as expected, need fkt := adr:ptr - 1
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


; sub akku from heap_ptr
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

;
;    OO              OO     OO                                      OO       OO
;         OOOOOO          OOOOOOO         OOOOOO  OO   OO OOOOOO  OOOOOOO         OOO OO   OOOOO
;  OOOO   OO   OO  OOOO     OO            OO   OO OO   OO OO   OO   OO     OOOO   OOOOOOO OO   OO
;    OO   OO   OO    OO     OO            OO      OO   OO OO   OO   OO       OO   OO O OO OOOOOOO
;    OO   OO   OO    OO     OO            OO      OO   OO OO   OO   OO       OO   OO O OO OO
; OOOOOOO OO   OO OOOOOOO    OOOO         OO       OOOOOO OO   OO    OOOO OOOOOOO OO O OO  OOOOO
;
; INIT-Runtime
; This is the only function, we call to initialise before program starts
; @Parameter: X-Register must contain the Stack Pointer (TSX)
;             Y-Register will be added to the heap-ptr
;                        This is very helpful for Atari-Basic parameters
@INIT_RUNTIME
     STX ?STACKPOINTER

     LDA #<@HEAP_MEMORY
     STA @HEAP_PTR
     LDA #>@HEAP_MEMORY
     STA @HEAP_PTR+1

 .IF .DEF @INIT_BREAKKEY
  jsr @INIT_BREAKKEY
 .ENDIF


; TODO: I don't know, if this is good idea hear
     LDA #0
     STA @ASSERT_FEHLER
     STA @ASSERT_FEHLER+1

; We copy Basic Parameters to our heap and move the Heap-Pointer
     TYA
;    JMP @ADD_TO_HEAP_PTR ; due to move next function, we save 3 bytes

; Add Akku zum Heap_Ptr
@ADD_TO_HEAP_PTR
    CLC                ; 2
    ADC @HEAP_PTR      ; 3
    STA @HEAP_PTR      ; 3
    BCS ?INC_HEAD_PTR2 ; 2
    RTS                ; 6

?INC_HEAD_PTR2
    INC @HEAP_PTR+1    ; 1+5
    RTS                ; 6

?STACKPOINTER
     .byte 0

@ASSERT_FEHLER
     .word 0

; Here starts the Heap-Memory.
     .BYTE "HEAP"

@PARAMETERCOUNT
@HEAP_MEMORY
    .byte 0

; @parameter starts one! byte after heap_memory, because from Atari-basic
; the first byte always contains the count of following parameters.
@PARAMETER
    .BYTE $de,$ad,$be,$ef

; Here must not stay anything.
