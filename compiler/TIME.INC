; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;TIMER-Library

   .LOCAL

; braucht SCREEN_OUTPUT.INC

; Der Atari merkt sich in 3 Bytes die 1/50s seit dem System-Start
; Es gibt keine feste Uhr nur die 1/50s PAL Sync, bei NTSC sind es 1/60s
; Somit haben wir 2^24 1/50s (PAL) oder 335544s oder 5592min oder 93h oder 3,8d
; 1d hat 24*60*60*50 1/50s oder 4.320.000 1/50s
;
; Merken der aktuellen Zeit in 3 Byte
; wir setzen Interrupt flag um den NMI zu verhindern
; zusaetzlich warten wir bis ein VBI durchlaufen wurde
; Damit sollten Zeitmessungen noch genauer sein
@STARTTIME
  JSR @VSYNCTIME

  SEI
  LDA RTCLOK
  STA ?START_TIMER
  LDA RTCLOK+1
  STA ?START_TIMER+1
  LDA RTCLOK+2
  STA ?START_TIMER+2
  CLI
  RTS

; Wir subtrahieren von der aktuellen Zeit unseren Start Timer
; Das Ergebnis sollte in 2 Byte passen was ~21min in 1/50s entspricht
;
@STOPTIME
  SEI
  LDA RTCLOK
  STA ?STOP_TIMER
  LDA RTCLOK+1
  STA ?STOP_TIMER+1
  LDA RTCLOK+2
  STA ?STOP_TIMER+2
  CLI

; ACHTUNG: auch wenn es falsch aussieht ist es richtig, die Daten
; sind falsch herum im Speicher abgelegt

  SEC
  LDA ?STOP_TIMER+2
  SBC ?START_TIMER+2
  STA ?END_TIMER+2
  LDA ?STOP_TIMER+1
  SBC ?START_TIMER+1
  STA ?END_TIMER+1
  LDA ?STOP_TIMER
  SBC ?START_TIMER
  STA ?END_TIMER

  LDY ?END_TIMER+2
  LDX ?END_TIMER+1
  RTS

; Wir syncronisieren uns mal und warten so lange
; bis der Inhalt von 20 sich aendert. (VBI)
@VSYNCTIME
  LDA RTCLOK+2
?LOOP
  CMP RTCLOK+2
  BEQ ?LOOP
  RTS


; Berechnet stoptime - starttime und gibt das Ergebnis auf dem Schirm aus.
@SHOWTIME
  JSR @STOPTIME
  JMP ?INNER_SHOW_GIVEN_TIME

; output the given value as String like @printf('Benoetigte Zeit: %d in 1/50s(pal)\n', value)
; or "1/60s (ntsc)" on ntsc systems
@SHOWGIVENTIME
@SHOWGIVENTIME_I
  LDY #2
  LDA (@HEAP_PTR),Y ; Wert holen
  TAX
  DEY
  LDA (@HEAP_PTR),Y
  TAY

?INNER_SHOW_GIVEN_TIME
  STY ?OUTPUT_TIME
  STX ?OUTPUT_TIME+1

  JSR @PRINT_STRING
  .byte "Benoetigte Zeit: ",$ff

  LDY ?OUTPUT_TIME
  LDX ?OUTPUT_TIME+1
  JSR @DECOUT

; wir fragen PAL aus und setzen die letzte Zeile entsprechend
  LDA PAL
  CMP #1
  BNE ?ISNTSC2

  JSR @PRINT_STRING
  .byte " in 1/50s (pal)",$ff
  JMP ?ENDE

?ISNTSC2
  JSR @PRINT_STRING
  .byte " in 1/60s (ntsc)",$ff

?ENDE
  JSR @EOLOUT
  LDY ?END_TIMER+2
  LDX ?END_TIMER+1
  RTS


; Datenbereich...
?OUTPUT_TIME
 .WORD 0

?START_TIMER
  .BYTE 0,0,0

?STOP_TIMER
  .BYTE 0,0,0

?END_TIMER
  .BYTE 0,0,0

?microtimer
 .byte 0
?seconds
 .byte 0
?minutes
 .byte 0

@sec_min_seconds
 LDY ?seconds
 LDX #0
 RTS

@sec_min_minutes
 LDY ?minutes
 LDX #0
 RTS

@reset_min_sec_timer
 LDA #0
 STA ?MICROTIMER
 STA ?seconds
 STA ?minutes
 RTS

@increment_min_sec_Timer
 INC ?MICROTIMER

; wir fragen PAL aus und setzen die letzte Zeile entsprechend
 LDA PAL
 CMP #1
 BNE ?ISNTSC

 LDA #50
 BNE ?PALORNTSC

?ISNTSC
 LDA #60
?PALORNTSC
 CMP ?MICROTIMER
 BEQ ?INC_SECONDS
 RTS

?INC_SECONDS
 LDA #0
 STA ?MICROTIMER

 SED
 CLC
 LDA ?seconds
 ADC #1
 STA ?seconds

 CMP #$60            ; BCD 60
 BEQ ?INC_MINUTES
 CLD
 RTS

?INC_MINUTES
 LDA #0
 STA ?seconds
 CLC
 LDA ?minutes
 ADC #1
 STA ?minutes
 CLD
 RTS
