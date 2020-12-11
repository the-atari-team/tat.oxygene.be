; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;RUNTIME-Library

  .LOCAL

; Hardware-Handler Adressen
KEYBDV = $E420  ;Keyboard

; Input ueber Keyboard only

ICHID =   832+0 ; Handleridentifizierung
ICDNO =   832+1 ; Devicenummer e.g. D1:
ICCOM =   832+2 ; Befehlsbyte
ICSTA =   832+3 ; Status
ICBADR =  832+4 ; :2 Adresse Filebuffer oder Filename
ICPUT =   832+6 ; :2
ICBLEN =  832+8 ; :2 Laenge des Buffers
ICAUX1 =  832+10 ; nach Open nicht verwenden
ICAUX2 =  832+11 ; nach Open nicht verwenden
ICAUX3 =  832+12
ICAUX4 =  832+13
ICAUX5 =  832+14
ICAUX6 =  832+15

CIOV  =   $E456

