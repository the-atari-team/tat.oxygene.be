; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;IO-Library
;
     .LOCAL

; Die hier angegebenen IO Routinen nutzen das Atari OS um Daten zu lesen/schreiben.
; erste Handlung ist immer einen CHANNEL zu öffnen (@open...)
; Daten zu schreiben oder zu lesen
; CHANNEL zu schließen mit (@close )


; öffnet einen CHANNEL zum lesen(4), schreiben(8), anhängen(12), ...
; Usage: @open(CHANNEL, 4|6|8|12,0,adr:filename)
; @return mit Fehler 129, sollte der CHANNEL schon offen sein
@OPEN
      JSR ?GET_CHANNEL

      LDY #3
      LDA (@HEAP_PTR),Y ; der 2. Parameter von open (4,8) Read/Write/Append

      STA ICAUX1,X

      LDY #5
      LDA (@HEAP_PTR),Y ; die fragwuerdige 0

      STA ICAUX2,X

      LDY #8
      LDA (@HEAP_PTR),Y ; Adresse des Dateinamens
      STA ICBADR+1,X
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y ; Adresse des Dateinamens
      STA ICBADR,X
      STA @REG

; Laenge des Dateinamens zaehlen
      LDY #0
?OPENSTRLEN
      LDA (@REG),Y
      INY
      CMP #$FF
      BNE ?OPENSTRLEN
      DEY      ; einen zu weit gezaehlt
      TYA
; TODO: don't do that again
;      STA 1536

      STA ICBLEN,X ; Dateinamen laenge
      LDA #0
      STA ICBLEN+1,X

      LDA #3       ; open
      STA ICCOM,X

      JSR CIOV

      LDX #0
      RTS

; Schliesst den angegebenen Kanal 0-6 moeglich 1-5 eher zu nutzen
; Usage: @close(CHANNEL)
@CLOSE
      JSR ?GET_CHANNEL

     LDA #12 ; close
     STA ICCOM,X

     JSR CIOV

     LDX #0
     RTS

; Holt exact ein Byte (Zeichen) über einen offenen CHANNEL und gibt dieses zurueck,
; Zeichen >256, Fehler aufgetreten
; Usage: value := @get(CHANNEL)
@GET
      JSR ?GET_CHANNEL

      LDA #7 ; Get Characters
      STA ICCOM,X

      LDA #0
      STA ICBLEN+1,X
      STA ICBLEN,X
      JSR CIOV

      CPY #127
      BCS ?GET_ERROR

      TAY
      LDX #0
      RTS

; TODO: Fehler setzen
?GET_ERROR
      TYA
      TAX
      LDY #0
      RTS

; Liest vom offenen CHANNEL eine angegebene Länge von Bytes
; und schreibt diese direkt in den Speicher ab der angegebene Adresse
; Usage: @bget(kanal, adresse, laenge)
@BGET
      JSR ?GET_CHANNEL

      LDA #7 ; Get Characters
      STA ICCOM,X

      JMP ?BGETBPUT

; Schreibt Daten in einen offenen CHANNEL
; schreibt eine angegebene Länge von Bytes ab der angegebenen Adresse
; Usage: @bput(kanal, adresse, laenge)
@BPUT
      JSR ?GET_CHANNEL

      LDA #11 ; Put Characters
      STA ICCOM,X

      LDA #0
      STA ?BGETPUT_STATUS

?BGETBPUT
      LDY #4
      LDA (@HEAP_PTR),Y ; Kanal
      STA ICBADR+1,X
      DEY
      LDA (@HEAP_PTR),Y ; Kanal
      STA ICBADR,X

      LDY #6
      LDA (@HEAP_PTR),Y ; Kanal
      STA ICBLEN+1,X
      DEY
      LDA (@HEAP_PTR),Y ; Kanal
      STA ICBLEN,X

     JSR CIOV

     CPY #0
     BPL ?NO_GETPUT_ERROR

     STY ?BGETPUT_STATUS

?NO_GETPUT_ERROR
     LDA ICBLEN,X
     TAY
     LDA ICBLEN+1,X
     TAX
     RTS

?BGETPUT_STATUS
 .byte 0

@GETBGETPUTSTATUS
  LDY ?BGETPUT_STATUS
  LDX #0
  RTS

; TODO: @PUT
; schreibt exact ein Byte in den offenen CHANNEL
 @PUT
      JSR ?GET_CHANNEL

      LDA #11       ;Befehl 'Put Characters'
      STA ICCOM,X   ;in IOCB eintragen
      LDA #0        ;nur einen Wert schreiben
      STA ICBLEN,X  ;daher Bufferlange:=0
      STA ICBLEN+1,X

; Byte holen, das geschrieben werden soll
      LDY #3
      LDA (@HEAP_PTR),Y

      JSR CIOV      ;und ablegen...

      CPY#0         ;Fehler? (s. Text!)
      BMI ?PUT_ERROR ;ja, zur Fehlerroutine

; liefert 1, wenn erfolgreich geschrieben
     LDY #1
?PUT_ERROR
     LDX #0
     RTS

; interne Hilfsroutine um an den ersten Parameter zu kommen
?GET_CHANNEL
      LDY #1
      LDA (@HEAP_PTR),Y ; Kanal
      ASL
      ASL
      ASL
      ASL
      TAX  ; IOCB Nummer * 16
      RTS
