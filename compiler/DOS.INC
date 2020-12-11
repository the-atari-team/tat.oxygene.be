; -*- text -*-
; cdw by 'The Atari Team' 1989-2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

;DOS-Library
;
     .LOCAL

; DOS
; Backjump into Dup TURBO-DOS XL 1.7
; Entnommen dem TURBO-DOS2-1Handbuch-final.pdf
@DOS
 JMP ($000A)


; Das aktuelle Verzeichnis, aus dem wir alles lesen sollten
; Wir nutzen hier einen Trick.
; Da es scheinbar keine offizielle Moeglichkeit gibt an diesen Wert zu kommen
; nutzen wir ICDNO+16 (kanal #1) dort sollte before @main() richtig gestartet
; wird, das Geraet zu finden sein, das zuletzt verwendet wurde.
@initCurrentDisk
        LDX #16
        LDA ICDNO,X
        CLC
        ADC #$30
        STA ?currentDisk
        RTS

; liefert die aktuelle Disk Station
@getCurrentDisk
        LDY ?currentDisk
        LDX #0
        RTS

?currentDisk
 .byte $31
