; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

; Current score and High score fuer Oxygene

      .local

; Wir arbeiten hier mit BCD Zahlen, dann haben wir es bei der Ausgabe einfacher
; einfach als Hex-Zahlen (3x1 Byte) rueckwaerts ausgeben
; Das heisst aber:
; in Interrupts ist unbedingt CLD zu verwenden, sollte ADC/SBC zum Einsatz kommen

; erhoehe Highscore um Wert aus Parameter
@ADD_CURRENT_SCORE
@ADD_CURRENT_SCORE_I
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen

      SED
      CLC
      ADC @BCD_CURRENT_SCORE1
      JMP ?STORE_AND_ADD_HIGH_VALUES


; erhoehe CURRENT_score um 1
@INC_CURRENT_SCORE

 SED
 CLC
 LDA @BCD_CURRENT_SCORE1
 ADC #$01

?STORE_AND_ADD_HIGH_VALUES
 STA @BCD_CURRENT_SCORE1
 LDA @BCD_CURRENT_SCORE2
 ADC #$00
 STA @BCD_CURRENT_SCORE2
 LDA @BCD_CURRENT_SCORE3
 ADC #$00
 STA @BCD_CURRENT_SCORE3

 CLD
 RTS

; ueberprueft current score mit Highscore und kopiert wenn current > high
@CHECK_SCORE
 LDA @BCD_CURRENT_SCORE3
 CMP @BCD_HIGHSCORE3
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 BEQ ?CHECK_NO_2

 LDA @BCD_CURRENT_SCORE3
 STA @BCD_HIGHSCORE3
?COPY_2
 LDA @BCD_CURRENT_SCORE2
 STA @BCD_HIGHSCORE2
?COPY_1
 LDA @BCD_CURRENT_SCORE1
 STA @BCD_HIGHSCORE1
 RTS

?CHECK_NO_2
 LDA @BCD_CURRENT_SCORE2
 CMP @BCD_HIGHSCORE2
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 BEQ ?CHECK_NO_1
 JMP ?COPY_2

?CHECK_NO_1
 LDA @BCD_CURRENT_SCORE1
 CMP @BCD_HIGHSCORE1
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 JMP ?COPY_1

?DO_NOT_COPY_CURRENT_TO_HIGH
 RTS

; setzt den aktuellen Score auf 0 zurueck
@CLEAR_CURRENT_SCORE
 LDA #0
 STA @BCD_CURRENT_SCORE1
 STA @BCD_CURRENT_SCORE2
 STA @BCD_CURRENT_SCORE3
 RTS


@BCD_CURRENT_SCORE1
 .byte 0

@BCD_CURRENT_SCORE2
 .byte 0

@BCD_CURRENT_SCORE3
 .byte 0

@BCD_HIGHSCORE1
 .byte 0

@BCD_HIGHSCORE2
 .byte 0

@BCD_HIGHSCORE3
 .byte 0


; Resttime gibt die Zeit in sec an, die noch verblieben
; da wir diese addieren m�chten, als bcd halten
?RESTTIME
 .byte 0

@INIT_BCD_REST_TIME
 LDA #0
 STA ?RESTTIME
 RTS

@GET_BCD_REST_TIME
 LDY ?RESTTIME
 LDX #0
 RTS

; erhoehe RestTime_score um 1
@INC_BCD_REST_TIME
 SED
 CLC
 LDA ?RESTTIME
 ADC #$01
 STA ?RESTTIME
 CLD
 RTS

