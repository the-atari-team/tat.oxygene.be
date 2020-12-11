; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;Macros

; -----------------------------

;Interne Variablen muessen in der Zero-Page liegen
; wir wollen nur die 42 Bytes der Floating-Point-Register verwenden
@BININT = 212                   ; Rueckgabewert Basic
@AUX  =   212

@PUTARRAY = 212                 ; 2 duerfen innerhalb von Expressions nicht ueberschrieben werden
@GETARRAY = @PUTARRAY+2         ; 2 dito

@OP   =   @AUX+4                ; 4
; Ergebnis, Produkt, REST
@PRODUKT = @AUX+8               ; 2
@REST =   @AUX+8                ; 2
@ERG  =   @AUX+8                ; 2

; Das sind Roedelregister, die grundsaetzlich ueberschrieben werden!
@REG  =   @AUX+10                ; 16 bytes (8 Register)

@RETURN = @REG+12
@ISMODULO = @REG+14             ; 1

; NOCH FREI     = @AUX+10+16 - @AUX+10+16+11 ; 11
@DLI_ROEDEL     = @AUX+10+16+9      ; 2 ; 247
@DISPLAYLIST    = @AUX+10+16+10+1   ; 2 ; 249
@COLOR_REGISTER = @AUX+10+16+10+3   ; 1 ; 251
@HEAP_PTR       = @AUX+10+16+10+4   ; 2 ; 252

    .MACRO WINC
    INC %1   ; 5
    BNE W    ; 2+1
    INC %1+1 ; 5
W
    .ENDM

    .MACRO WDEC
        LDA %1+0       ;Test if the LSB is zero
        BNE SKIP       ;If it isn't we can skip the next instruction
        DEC %1+1       ;Decrement the MSB when the LSB will underflow
SKIP    DEC %1+0       ;Decrement the LSB
    .ENDM

; Folgendes Macro wird verwendet um den Heap_Ptr zu erhoehen,
; wenn Proceduren mit Parametern aufgerufen werden.
; 11 Bytes (statt 6 Bytes (2+3+1) (lda #, jsr x, rts))
; aber 13 Takte statt 24 mit jsr
    .MACRO ADD_TO_HEAP_PTR
      CLC              ;2 (Takte)
      LDA @HEAP_PTR    ;3
      ADC #%1          ;2
      STA @HEAP_PTR    ;3
      BCC NO_INC_HIGH_HEAP_PTR ;3 ; => 13 Takte statt 24 mit jsr

      INC @HEAP_PTR+1  ;5

NO_INC_HIGH_HEAP_PTR
    .ENDM

; Folgendes Macro wird verwendet um den Heap_Ptr zu erniedrigen,
; wenn Proceduren mit Parametern aufgerufen wurden.
; 11 Bytes (statt 6 Bytes (2+3+1) (lda #1, jsr x, rts))
; aber 13 Takte statt 32 mit jsr
    .MACRO SUB_FROM_HEAP_PTR
      SEC              ;2
      LDA @HEAP_PTR    ;3
      SBC #%1          ;2
      STA @HEAP_PTR    ;3
      BCS NO_DEC_HIGH_HEAP_PTR ;3 ; => 13 Takte statt 30 mit jsr

      DEC @HEAP_PTR+1  ;5

NO_DEC_HIGH_HEAP_PTR
    .ENDM

;Putarrayb Var
      .MACRO PUTARRAYB
      CLC             ; 2 putarrayb MACRO
      TYA             ; 2
      ADC # <%1       ; 2
      STA @PUTARRAY   ; 3
      TXA             ; 2
      ADC # >%1       ; 2
      STA @PUTARRAY+1 ; 3
      .ENDM
;             in Summe 16 Zyklen 11 Bytes

;Getarrayb Var
      .MACRO GETARRAYB
      CLC             ; 2 Getarrayb MACRO
;      TYA             ; 2
      ADC # <%1       ; 2
      STA @GETARRAY   ; 3
      TXA             ; 2
      ADC # >%1       ; 2
      STA @GETARRAY+1 ; 3
      LDX #0          ; 2
      LDA (@GETARRAY,X) ; 6
      TAY             ; 2
      .ENDM
;             in Summe 26 Zyklen 16 Bytes
;
; Putarrayw Var
      .MACRO PUTARRAYW
      TYA         ; 2 putarrayw MACRO
      ASL A       ; 2 Mult (x,y)*2
      TAY         ; 2
      TXA         ; 2
      ROL A       ; 2
      TAX         ; 2
      CLC         ; 2 add %1 to the nth value
      TYA         ; 2
      ADC # <%1   ; 2
      STA @PUTARRAY ; 3
      TXA         ; 2
      ADC # >%1   ; 2
      STA @PUTARRAY+1 ; 3
      .ENDM
;         in Summe 28 Zyklen 17 Bytes

; Getarrayw Var
      .MACRO GETARRAYW
      TYA           ; 2 Getarrayw MACRO
      ASL A         ; 2 Mult (x,y)*2
      TAY           ; 2
      TXA           ; 2
      ROL A         ; 2
      TAX           ; 2
      CLC           ; 2 add %1 to the nth value
      TYA           ; 2
      ADC # <%1     ; 2
      STA @GETARRAY ; 3
      TXA           ; 2
      ADC # >%1     ; 2
      STA @GETARRAY+1 ; 3
      LDY #1        ; 2 load x and y from @ARRAY
      LDA (@GETARRAY),Y ; 5
      TAX           ; 2
      DEY           ; 2
      LDA (@GETARRAY),Y ; 5
      TAY           ; 2
      .ENDM
;          in Summe 46 Zyklen 25 Bytes
