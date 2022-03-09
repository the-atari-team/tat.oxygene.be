; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;IO-Library
;
     .LOCAL

; Die hier angegebenen IO Routinen nutzen das Atari OS um Daten zu lesen/schreiben.
; erste Handlung ist immer einen CANAL zu öffnen (@open...)
; Daten zu schreiben oder zu lesen
; CANAL zu schließen mit (@close )


; öffnet einen CANAL zum lesen(4), schreiben(8), anhängen(12), ...
; Usage: @open(CANAL, 4|6|8|12,0,adr:filename)
; @return mit Fehler 129, sollte der CANAL schon offen sein
@OPEN
@OPEN_IIII
      JSR ?GET_CANAL

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
; Kanal 0 ist fuer den Editor immer offen
; Kanal 6 ist fuer Graphics, immer geschlossen, trotzdem nutzbar
; Usage: @close(CANAL)
@CLOSE
@CLOSE_I
      JSR ?GET_CANAL

     LDA #12 ; close
     STA ICCOM,X

     JSR CIOV

     LDX #0
     RTS

; Holt exakt ein Byte (Zeichen) über einen offenen CANAL und gibt dieses zurueck,
; Zeichen >256, Fehler aufgetreten
; Usage: value := @get(CANAL)
@GET
@GET_I
      JSR ?GET_CANAL
      jsr ?get_single_byte

      TAY
      LDX #0
      RTS

; TODO: Fehler setzen
?GET_ERROR
      TYA
      TAX
      LDY #0
      RTS

; Holt exakt zwei Byte (Zeichen) über einen offenen CANAL und gibt diese zurueck,
; Usage: value := @getw(CANAL)
@GETW
@GETW_I
      JSR ?GET_CANAL
      jsr ?get_single_byte ; low byte
      STA @REG

      jsr ?get_single_byte ; high byte
      TAX
      LDY @REG
      RTS

?get_single_byte
      LDA #7 ; Get Characters
      STA ICCOM,X

      LDA #0
      STA ICBLEN+1,X
      STA ICBLEN,X
      JSR CIOV

      CPY #127
      BCS ?GET_ERROR

      RTS

; Liest vom offenen CANAL eine angegebene Länge von Bytes
; und schreibt diese direkt in den Speicher ab der angegebene Adresse
; Usage: @bget(kanal, adresse, laenge)
@BGET
@BGET_III
      JSR ?GET_CANAL

      LDA #7 ; Get Characters
      STA ICCOM,X

      JMP ?BGETBPUT

; Schreibt Daten in einen offenen CANAL
; schreibt eine angegebene Länge von Bytes ab der angegebenen Adresse
; Usage: @bput(kanal, adresse, laenge)
@BPUT
@BPUT_III
      JSR ?GET_CANAL

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

@PUTW
@PUTW_II
  jsr ?get_canal

  ldy #3
  lda (@HEAP_PTR),y

  jsr ?put

  ldy #4
  lda (@HEAP_PTR),y

  jsr ?put
  jmp ?put_exit

; TODO: @PUT
; schreibt exact ein Byte in den offenen CANAL
 @PUT
 @PUT_II
      JSR ?GET_CANAL

; Byte holen, das geschrieben werden soll
      ldy #3
      lda (@HEAP_PTR),y

      jsr ?put
?put_exit
      CPY#0         ;Fehler? (s. Text!)
      BMI ?PUT_ERROR ;ja, zur Fehlerroutine

; liefert 1, wenn erfolgreich geschrieben
     LDY #1
?PUT_ERROR
     LDX #0
     RTS

?put
      pha
      LDA #11       ;Befehl 'Put Characters'
      STA ICCOM,X   ;in IOCB eintragen
      LDA #0        ;nur einen Wert schreiben
      STA ICBLEN,X  ;daher Bufferlange:=0
      STA ICBLEN+1,X
      pla

      JMP CIOV      ;und ablegen...

; liefert den aktuellen Status des uebergebenen Kanals
;
@STATUS
@STATUS_I
  jsr ?get_canal

  lda ICSTA,X
  tay
  ldx #0
  rts

; interne Hilfsroutine um an den ersten Parameter zu kommen
?GET_CANAL
      LDY #1
      LDA (@HEAP_PTR),Y ; Kanal
      ASL
      ASL
      ASL
      ASL
      TAX  ; IOCB Nummer * 16
      RTS
