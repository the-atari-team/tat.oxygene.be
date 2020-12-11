; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;optimierte ARRAY-Library

    .LOCAL
;          in Summe: 48 Zyklen (-4 optimierung moeglich) 23 Bytes

; Einfacher Zugriff auf ein Array
; @getByteArray(adr:[name_array], index) entspricht name_array[index]
; der Index muss <= 255 sein,
; weil es ueber indirekte Adressierung funktioniert
@getbytearray
 LDY #2            ; 2  erster Parameter, Adresse des Arrays
 LDA (@HEAP_PTR),Y ; 5 high Wert holen
 STA @REG+1        ; 3
 DEY               ; 2
 LDA (@HEAP_PTR),Y ; 5 low Wert holen
 STA @REG          ; 3

 LDY #3            ; 2 2. Parameter (byte only) ist Index
 LDA (@HEAP_PTR),Y ; 5
 TAY               ; 2
 LDA (@REG),Y      ; 5

 TAY               ; 2
 LDX #0            ; 2
 RTS               ; 6
;          in Summe: 44 Zyklen  22 Bytes

; Setzt einen gegebenen Wert in ein Array
; @setByteArray(address, index, value)
; .IF .REF @SETBYTEARRAY
@SETBYTEARRAY
 LDY #2            ; 2  erster Parameter, Adresse des Arrays
 LDA (@HEAP_PTR),Y ; 5 high Wert holen
 STA @REG+1

 DEY               ; 2
 LDA (@HEAP_PTR),Y ; 5 low Wert holen
 STA @REG          ; 3

 LDY #5            ; 2 3. Parameter (byte only)
 LDA (@HEAP_PTR),Y ; 5
 TAX               ; 2 Wert merken

 LDY #3            ; 2 2. Parameter (byte only) ist Index
 LDA (@HEAP_PTR),Y ; 5
 TAY               ; 2

 TXA               ; 2
 STA (@REG),Y      ; 6
 RTS               ; 6
; .ENDIF

; Einfacher Zugriff auf ein Array
; @getWordArray(adr:[name_array], index) entspricht name_array[index]
; der Index muss <= 127 sein,
; weil es ueber indirekte Adressierung funktioniert
; .IF .REF @getwordarray
@getwordarray
 LDY #2            ; 2  erster Parameter, Adresse des Arrays
 LDA (@HEAP_PTR),Y ; 5 high Wert holen
 TAX               ; 2 <--- optimierung sta @reg+1
 DEY               ; 2
 LDA (@HEAP_PTR),Y ; 5 low Wert holen
 TAY               ; 2 <--- optimierung sta @reg
 STY @REG          ; 3
 STX @REG+1        ; 3

 LDY #3            ; 2 2. Parameter (byte only) ist Index
 LDA (@HEAP_PTR),Y ; 5
 ASL A             ; 2 Mult mit 2
 TAY               ; 2

 INY               ; 2
 LDA (@REG),Y      ; 5
 TAX               ; 2
 DEY               ; 2
 LDA (@REG),Y      ; 5
 TAY               ; 2
 RTS               ; 6
; .ENDIF

;          in Summe: 59 Zyklen (-4 optimierung m?glich) 30 Bytes