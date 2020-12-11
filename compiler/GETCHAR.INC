; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
;INPUT-Library

   .LOCAL

;
;Ein Zeichen einlesen
; - solange warten bis Zeichen eingegeben!
; <A> :enthaelt Zeichen
; @return x*256+y ist das eingelesene Zeichen
@GETCHAR
      JSR ?GK
      TAY
      LDX #0
      RTS
;
?GK   LDA KEYBDV+5 ;simuliere
      PHA
      LDA KEYBDV+4
      PHA
      RTS

?CONSOL=53279

@isStartKey
   LDA ?CONSOL
   AND #~00000001
   BEQ ?KEY_PRESSED

 ?KEY_NOT_PRESSED
   LDY #0
   LDX #0
   RTS

 ?KEY_PRESSED
   LDY #1
   LDX #0
   RTS

@isOptionKey
   LDA ?CONSOL
   AND #~00000100
   BEQ ?KEY_PRESSED
   BNE ?KEY_NOT_PRESSED

@isSelectKey
   LDA ?CONSOL
   AND #~00000010
   BEQ ?KEY_PRESSED
   BNE ?KEY_NOT_PRESSED

