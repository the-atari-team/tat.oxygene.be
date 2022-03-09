; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;BASIC-Library

    .LOCAL

; Genau drauf achten, das immer X das hoeherwertige Byte nimmt


; makeword(low, high) macht aus 2 bytes ein Wort.
; return a new word (high * 256 + low)
;  .if .ref @makeword
@makeword
@makeword_ii
  LDY #3
  LDA (@HEAP_PTR),Y ; high byte Wert holen
  TAX
  LDY #1
  LDA (@HEAP_PTR),Y ; low byte Wert holen
  TAY
  RTS
; .endif

; run through INITAD
@start_INITAD
  JMP (738)

; run through RUNAD
@start_RUNAD
  JMP (736)

; Jump into Address, like Basic
;  .if .ref @usr
@usr
@usr_i
 LDY #2
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA ?JUMPADR+1
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?JUMPADR

 LDA #2
 JSR @ADD_TO_HEAP_PTR

 JSR ?JUMPER

 LDA #2
 JMP @SUB_FROM_HEAP_PTR

?JUMPER
 JMP (?JUMPADR)

?JUMPADR
 .word 0

; .endif


; move length Bytes von-adresse, nach-adresse, length
; dabei wird vorwaerts geschoben
; Der Seiteneffekt ist, man setzt in die von-adresse eine 0 und nach-adresse nur ein byte weiter als von-adresse
; jetzt kann unter Angabe der length Speicher geloescht werden.
; eignet sich also nicht um Daten ein Byte nach vorne zu schieben. Das Gegenstueck hierzu heisst @moveup.
; .IF .REF @move
@move
@move_iii
; von Adresse
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1

; nach Adresse
 LDY #3
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+2
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+3

; length
 LDY #6
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX             ; oberen Wert merken fuer Auswertung, ob nicht doch move255 genutzt werden kann
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen

 CPX #0
 BEQ ?MOVE_0_TO_255_LOOP

; STX @REG+5
 STA @REG+4
 LDY #0

?MOVELOOP_3
 LDA (@REG),Y
 STA (@REG+2),Y
 INY
 BNE ?MOVELOOP_3

 INC @REG+1
 INC @REG+3

; DEC @REG+5
 DEX
 BNE ?MOVELOOP_3

 LDA @REG+4  ; last Bytes

; JMP ?MOVE_0_TO_255_LOOP

?MOVE_0_TO_255_LOOP
 CMP #0            ; nicht entfernen!
 BEQ ?MOVEEND

 TAX
 LDY #0

?MOVELOOP
 LDA (@REG),Y
 STA (@REG+2),Y
 INY
 DEX
 BNE ?MOVELOOP

?MOVEEND
 RTS
; .ENDIF

; Reverse Move
; rmove length Bytes von-adresse, nach-adresse, length
; dabei wird rueckwaerts geschoben
; eignet sich um Daten ein Byte nach vorne zu schieben. Das Gegenstueck ist move.

?from=@REG
?to=@REG+2
?size=@REG+4

@moveup
@moveup_iii
; von Adresse
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?from
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA ?from+1

; nach Adresse
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?to
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA ?to+1

; length
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?size
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA ?size+1

 LDX ?SIZE+1    ; the last byte must be moved first
 CLC          ; start at the final pages of FROM and TO
 TXA
 ADC ?FROM+1
 STA ?FROM+1

 CLC
 TXA
 ADC ?TO+1
 STA ?TO+1
 INX          ; allows the use of BNE after the DEX below

 LDY ?SIZE
 BEQ ?MU3

 DEY          ; move bytes on the last page first
 BEQ ?MU2

?MU1
 LDA (?FROM),Y
 STA (?TO),Y
 DEY
 BNE ?MU1

?MU2
 LDA (?FROM),Y ; handle Y = 0 separately
 STA (?TO),Y

?MU3
 DEY
 DEC ?FROM+1   ; move the next page (if any)
 DEC ?TO+1
 DEX
 BNE ?MU1

 RTS



; wartet bis nte Zeile erreicht ist, ggf. ueber die Austastluecke hinaus.
; Ein vsync ist somit nicht noetig, wenn die naechste Abfrage nur 2 Zeilen (228 Takte) spaeter erfolgt
;
; Routine eigent sich sehr gut um Flakern zu verhindert, ein @waitline(100) wartet meist, bis fast die letzte Zeile des
; sichtbaren Bereiches erreicht ist.

;  .if .ref @waitline
@waitline
@waitline_i

; wir fragen PAL aus und setzen die letzte Zeile entsprechend
 LDA PAL
 CMP #1
 BNE ?ISNTSC

 LDA #155
 BNE ?SETLASTLINE

?ISNTSC
 LDA #130

?SETLASTLINE
 STA ?LASTLINE+1

 LDY #1

 LDA VCOUNT
 CMP (@HEAP_PTR),Y
 BEQ ?NO_WAIT_NEED
 BMI ?WAITLOOP2

; groesser als gefordert
; wir warten erstmal ab, bis der Elektronenstrahl ganz unten ist
?WAITLOOP1
 LDA VCOUNT
?LASTLINE
 CMP #155
 BMI ?WAITLOOP1

; Dann warten wir noch bis der Elektronenstrahl wieder bei 0 ist.
?FIRSTLINE
 LDA VCOUNT
 BNE ?FIRSTLINE

; Das eigentliche Warten auf die richtige Zeile
?WAITLOOP2
 LDA VCOUNT
 CMP (@HEAP_PTR),Y
 BMI ?WAITLOOP2

?NO_WAIT_NEED
 TAY
 LDX #0
 RTS
; .endif

; TODO: sleep_lines (wir wissen, wo wir sind und koennten das evtl. anbieten mit VCOUNT!)
; @sleep(low) wartet low * vsync Zeit. (max 255 1/50s) Dazu wird der interne Zeitzaehler (20) verwendet.
; @pause(low) ist das selbe
; @pause(0) wartet nicht!
@sleep
@sleep_i
@pause
@pause_i
  LDY #1
  LDA (@HEAP_PTR),Y ; high Wert holen

  BEQ ?pauseexit
  TAY

?outerpauseloop
  LDA RTCLOK+2

?innerpauseloop
  CMP RTCLOK+2
  BEQ ?innerpauseloop

  DEY
  BNE ?outerpauseloop

?pauseexit
  LDA #0
  TAY
  TAX
  RTS


; and length Bytes von-adresse
; dabei wird vorwaerts gearbeitet
; .IF .REF @move

?andbyte=@REG
?source=@REG+2
?length=@REG+4

@andbytes
@andbytes_iii
; and Byte
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?andbyte

; nach Adresse
 LDY #3
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA ?source
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?source+1

; length
 LDY #6
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX             ; oberen Wert merken fuer Auswertung, ob nicht doch move255 genutzt werden kann
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen

 CPX #0
 BEQ ?AND_0_TO_255_LOOP

 STX ?length+1
 STA ?length
 LDY #0

?ANDLOOP_3
 LDA (?source),Y
 AND ?andbyte
 STA (?source),Y
 INY
 BNE ?ANDLOOP_3

 INC ?source+1

 DEC ?length+1
 BNE ?ANDLOOP_3

 LDA ?length  ; last Bytes

?AND_0_TO_255_LOOP
 CMP #0            ; nicht entfernen!
 BEQ ?ANDEND

 TAX
 LDY #0

?ANDLOOP
 LDA (?source),Y
 AND ?andbyte
 STA (?source),Y
 INY
 DEX
 BNE ?ANDLOOP

?ANDEND
 RTS
