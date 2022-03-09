; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Display List Interrupts
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;

 .local

@AUDIO_PTR=207 ; 2 Bytes

?audf1 = $d200 ; audio frequence (audio freq = takt / AUDF)
?audc1 = $d201

?skctl=$d20f
?audctl=$d208

; Spielt einen Sound ab, jede 1/50s wird der naechste Wert geholt, bis 255,255 erreicht ist.
; wir nutzen den AUDIO_BUFFER zusaetzlich um zu markieren, ob der Kanal belegt ist
; dabei pruefen wir nur das hoeherwertige Byte
; Die Daten liegen irgendwo im Speicher der Form:
; audf, audc, ..., 255,255

; @start_play(adr:sound)

@INIT_AUDIO_HARDWARE
 LDA #0
 STA ?audctl
 LDA #3
 STA ?skctl
 RTS

@INIT_AUDIO_PLAYER
 LDX #0
 TXA
?CLEAR_LOOP
 STA @AUDIO_BUFFER_PTR,X
 INX
 CPX #8
 BNE ?CLEAR_LOOP

 LDA #<@AUDIO_PLAYER
 STA @RS_AUDIO_PLAYER+1
 LDA #>@AUDIO_PLAYER
 STA @RS_AUDIO_PLAYER+2

 RTS

@AUDIO_START_PLAY2
@AUDIO_START_PLAY2_I
 LDX #0
 BEQ ?FREE_CHANAL_FOUND

@AUDIO_START_PLAY
@AUDIO_START_PLAY_I
 LDX #2
?SEARCH_FREE_LOOP            ; wir suchen einen freien Kanal
 LDA @AUDIO_BUFFER_PTR+1,X
 BEQ ?FREE_CHANAL_FOUND

 INX
 INX
 CPX #8
 BNE ?SEARCH_FREE_LOOP

 INC @AUDIO_NOT_PLAYED
 RTS                          ; es gibt keinen Freien Kanal, also nichts machen

?FREE_CHANAL_FOUND            ; Freude! Es gibt einen freien Kanal
 LDY #1                       ; Abzuspielenden Audio holen
 LDA (@HEAP_PTR),Y
 STA @AUDIO_BUFFER_PTR,X      ; zuerst das niederwertige Byte setzen!
 INY                          ; Weil wir das hoeherwertige Byte auch als Marke verwenden
 LDA (@HEAP_PTR),Y
 STA @AUDIO_BUFFER_PTR+1,X

; Ein freier Soundkanal sollte jetzt belegt sein und
; der Buffer ist gesetzt mit der Adresse des abzuspielenden Sounds
 RTS


; Diese Funktion sollte alle 1/50s angetriggert werden, um die gewuenschten Sounds abzuspielen
@AUDIO_PLAYER
 LDX #0
?SEARCH_FOR_CHANAL_IN_USE     ; wir suchen belegte Kaenale
 LDA @AUDIO_BUFFER_PTR+1,X
 BEQ ?CHANAL_NOT_IN_USE

 JSR ?SET_AUDIO

?CHANAL_NOT_IN_USE
 INX
 INX
 CPX #8
 BNE ?SEARCH_FOR_CHANAL_IN_USE
 RTS

?SET_AUDIO
 LDA @AUDIO_BUFFER_PTR,X
 STA @AUDIO_PTR
 LDA @AUDIO_BUFFER_PTR+1,X
 STA @AUDIO_PTR+1

 LDY #1                      ; Wir setzen das AudioCtrl Register, da ein Wert von 255 nicht vorkommt, als Marke pruefen
 LDA (@AUDIO_PTR),Y
 CMP #255
 BEQ ?END_MARK_FOUND
 STA ?audc1,X

 DEY
 LDA (@AUDIO_PTR),Y          ; Frequenz (freq = 64khz / this value)
 STA ?audf1,X

 CLC                          ; Setze den Buffer auf die naechsten Werte
 LDA @AUDIO_BUFFER_PTR,X
 ADC #2
 STA @AUDIO_BUFFER_PTR,X
 BCC ?NO_HIGH_ADD
 INC @AUDIO_BUFFER_PTR+1,X
?NO_HIGH_ADD
 RTS

?END_MARK_FOUND
 LDA #0
 STA ?audf1,X
 STA ?audc1,X
; STA @AUDIO_BUFFER_PTR,X     ; nicht noetig zu loeschen
 STA @AUDIO_BUFFER_PTR+1,X

 RTS

;; TODO:
;; Umbau der Audio Listen zu diesem Source

;; ;*************************************************
;; ;*           SOUND IM VBI                        *
;; ;*                                               *
;; ;* Soundgenerator im VBI - zum Editor SNDEDIT    *
;; ;*************************************************
;; ;
;; ; MUSTERTABELLE:
;; ;
;; SNDTAB = $9E00 Mustertabelle ist hier abgelegt
;; ;
;; ; Struktur der Mustertabelle: wird 32 mal wiederholt
;; ;
;; ; 1.Byte: Frequenzanfang
;; ; 2.Byte: Frequenz Aenderung
;; ; 3.Byte: Lautstaerke Anfang * 16
;; ; 4.Byte: Lautstaerke Aenderung *16
;; ; 5.Byte: Dauer des Sounds in 1/50 sec.
;; ; 6.Byte: Distortion * 16
;; ; 7.Byte: Bit 0-1: Kanalnumer, Bit 2-7:Prioritaet
;; ; 8.Byte: Verweis auf naechstes Muster (255:=NIL)
;; ;
;; ;*************************************************
;; ; OS und Hardwareadressen
;; ;*************************************************
;; ;
;; SETVBV = $E45C O.S. Vektoren
;; XITVBV = $E462
;; ;
;; AUDF1 = $D200    POKEY-Register
;; AUDC1 = $D201
;; AUDCTL = $D208
;; SKCTL = $D20F
;; ;
;; ;*************************************************
;; ; Schnittstellen Adressen
;; ;*************************************************
;; ;
;; SNDFLG = $06FE Aufruf der Sounds 0-7 per Flags
;; SNDNUM = $06FF Aufruf der Sounds 0-31 per Nummer
;; ;
;; ; Interne Adressen f. SOUND
;; ;
;; SNDATA = $9DE0 Anfangsadresse der Variablen
;; ;
;; SNDCNT = SNDATA Zaehler f. Soundlaenge (4 Bytes)
;; SNINDX = SNDATA+4 Index in Mustertabelle (4)
;; SNFREQ = SNDATA+8 aktuelle Frequenz (4)
;; SNDVOL = SNDATA+12 aktuelle Lautstaerke (4)
;; SNDPRI = SNDATA+16 Prioritaet der Sounds (4)
;; SNDCHN = SNDATA+20 Hilfsregister(1 Byte)
;; ;
;; ;
;; ;
;; ;*************************************************
;; ; Sprungleiste zum Aufruf von Basic, Assembler ...
;; ;*************************************************
;;        *= $9C00
;; ;
;;        PLA         fuer BASIC
;;                           - 39 -
;;       JMP SNDINI   SOUND-VBI einschalten, init.
;;       PLA          fuer BASIC
;;       JMP SNDEXT   VBI ausschalten
;; ;
;; ;*************************************************
;; ; VBI-Routine, laeuft alle 1/50 sec.
;; ;*************************************************
;; ;
;; SNDVBI CLD      ;Dezimalmodus
;;        JSR SNINTP Interpreter f. laufende Toene
;;        JSR SNDANF neue Anforderungen pruefen
;;        JMP XITVBV VBI beenden
;; ;
;; ;*************************************************
;; ; Test auf Sound-Anforderung
;; ;*************************************************
;; ;
;; SNDANF LDA #7   Anforderung per F ag pruefen
;;        STA SNDCHN Zaehler f. 8 Bits
;; ;
;; SNANF1 ASL SNDFLG Flag in Carry
;;        BCC SNANF2 ist 0, d.h. keine Anforderung -->
;; ; sonst Sound vorbereiten!
;;        LDA SNDCHN Nummer des Musters (0-7)
;;        JSR SNVORB Sound anstossen >>>
;; ;
;; SNANF2 DEC SNDCHN schon alle 8 Flags geprueft?
;;        BPL SNANF1 nein, weiter --->
;; ;
;;        LDA SNDNUM Anforderung per Musternummer
;;        CMP #255     Code fuer 'keine Anforderung'?
;;        BEQ SNAEND ja, Schluss -->
;; ;
;;        JSR SNVORB sonst Sound vorbereiten >>>
;;        LDA #255     und Flag zuruecksetzen
;;        STA SNDNUM
;; ;
;; SNAEND RTS
;; ;
;; ;*************************************************
;; ; Soundvorbereitung: Parameter aus Tabelle holen
;; ; <A>: Musternummer
;; ;*************************************************
;; ;
;; SNVORB ASL A    ;Index in Mustertabelle
;;        ASL A        ;= Musternummer * 8
;;        ASL A
;;        TAX          Musterindex in X
;;        LDA SNDTAB+5,X Laenge des Sounds:=0?
;;        BEQ SNVEND dann kein Ton -->
;; ;
;;        LDA SNDTAB+6,X Kanal Nr. besorgen
;;        AND #3       ist in Bit 0-1 enthalten
;;        TAY          Kanalnummer nach Y
;;        LDA SNDTAB+6,X zuerst Prioritaet pruefen!
;;        LSR A        Prior. ist Bit 2-7 enthalten
;;        LSR A        d.h. / 4
;;        CMP SNDPRI,Y groesser momentane Prioritaet?
;;        BCC SNVEND ja, Anforderung wird ignoriert -->
;;                          - 40 -
;; ;
;;        STA SNDPRI,Y Prioritaet merken
;;        TXA         Index in Mustertabelle
;;        STA SNINDX,Y fuer Interpreter aufbewahren
;;        LDA SNDTAB+0,X Frequenzanfang
;;        STA SNFREQ,Y in Register f. momentane Freq.
;;        LDA SNDTAB+2,X Lautstaerkeanfang
;;        STA SNDVOL,Y Reg. fuer akt. Lautstaerke
;;        LDA SNDTAB+5,X Laenge des Sounds
;;        STA SNDCNT,Y in Zaehler eintragen
;;        JSR SNDHRD Sound gleich anwerfen >>>
;; SNVEND RTS
;; ;
;; ;*************************************************
;; ; Soundinterpreter fuer alle 4 Kanaele
;; ;*************************************************
;; ;
;; SNINTP LDA #3   alle 4 Kanaele bearbeiten (0-3)
;;        STA SNDCHN in Zaehler ablegen
;; ;
;; SNNXCH JSR SNINTC einzelnen Kanal bearbeiten >>>
;;        DEC SNDCHN schon alle 4?
;;        BPL SNNXCH nein, naechsten Kanal -->
;;        RTS
;; ;
;; ;*************************************************
;; ;Kanal bearbeiten, neue Freq. und Laust. berechnen
;; ;<SNDCHN>: Kanalnummer
;; ;*************************************************
;; ;
;; SNINTC LDY SNDCHN aktuelle Kanalnummer
;;        LDA SNDCNT,Y Kanalzaehler fuer Soundlaenge
;;        BEQ SNIEND Kanal ist nicht aktiv -->
;; ;
;;        SEC         sonst Laenge vermindern
;;        SBC #1      Zaehler dec.
;;        STA SNDCNT,Y ist Zaehler abgelaufen?
;;        BNE SNINOK nein, dann normale Behandlung ->
;; ;
;;        LDX SNINDX,Y sonst pruefen, ob Verkettung
;;        LDA SNDTAB+7,X Naechstes Muster
;;        CMP #255    kein weiteres Muster (=NIL)?
;;        BEQ SNDAUS ja, dann Kanal aus! -->
;; ;
;;        JSR SNVORB sonst Sound vorbereiten >>>
;;        RTS
;; ;
;; SNDAUS LDA #0   Kanal ausschalten
;;        STA SNDPRI,Y Prioritaet=0
;;        STA SNFREQ,Y Frequenz:= 0
;;        STA SNDVOL,Y Lautstaerke:=0
;;        JSR SNDHRD an Pokey >>>>
;;        RTS
;; ;
;; SNINOK LDX SNINDX,Y Index fuer Muster
;;        LDA SNDTAB+1,X Freq.Aenderung aus Tabelle
;;        CLC
;;        ADC SNFREQ,Y neue Freq. berechnen
;;        STA SNFREQ,Y und abspeichern
;;                           - 41 -
;;        LDA SNDTAB+3,X Laut.Aenderung aus Tabelle
;;        CLC
;;        ADC SNDVOL,Y zu bisheriger Lautst. addieren
;;        STA SNDVOL,Y neues Lautst. speichern
;;        JSR SNDHRD in Hardware eintragen>>>
;; SNIEND RTS
;; ;
;; ;*************************************************
;; ;Lautstaerke und Frequenz in POKEY eintragen
;; ;<Y>: Kanalnummer    <X>: Musternummer * 8
;; ;*************************************************
;; ;
;; SNDHRD LDA SNFREQ,Y aktuelle Tonhoehe
;;        PHA         merken
;;        LDA SNDVOL,Y akt. Lautstaerke (*16)
;;        LSR A       dividiert durch 16
;;        LSR A
;;        LSR A
;;        LSR A
;;        ORA SNDTAB+4,X Distortion-Bits dazu
;;        PHA         und auch merken
;;        TYA         Index fuer Hardwareregister
;;        ASL A       ;=<Y> * 2
;;        TAY
;;        PLA         Lautst. und Distortion
;;        STA AUDC1,Y Kanal-Kontrollregister
;;        PLA         Tonhoehe
;;        STA AUDF1,Y Kanal-Frequenzregister
;;        RTS
;; ;
;; ;*************************************************
;; ; Initialisierungsroutine
;; ;*************************************************
;; ;
;; SNDINI LDA #0   alle Kanaele ausschalten
;;        STA SNDFLG Flagaufruf loeschen
;;        LDA #255
;;        STA SNDNUM Nummeraufruf zuruecksetzen
;;        JSR SNDPOK POKEY initialisieren
;; ;
;;        LDX #SNDVBI/256 Hi-Byte der VBI-Routine
;;        LDY #SNDVBI&255 Lo-Byte
;;        LDA #7      fuer 'Deferred VBI'
;;        JSR SETVBV VBI einfuegen >>>
;;        RTS
;; ;
;; ;*************************************************
;; ; SOUND-VBI ausschalten
;; ;*************************************************
;; ;
;; SNDEXT LDX #XITVBV/256 VBI-Vektor restaurieren
;;        LDY #XITVBV&255 Lo-Byte
;;        LDA #7      'Deferred VBI'
;;        JSR SETVBV und ausschalten >>>
;;        JSR SNDPOK alle Kanaele ruhig
;;        RTS
;; ;
;;                           - 42 -
;; ;*************************************************
;; ; POKEY ruecksetzen
;; ;*************************************************
;; ;
;; SNDPOK LDA #0   alle Kanaele ausschalten
;;        LDX #7       insgesamt 8 Register
;; ;
;; SNDP1 STA AUDF1,X AUDF/C 1/2
;;        DEX          schon alle 4?
;;        BPL SNDP1    nein, weiter -->
;; ;
;;        STA AUDCTL Sound-Kontrollregister zurueck
;;        LDA #3       Serial CTL aus
;;        STA SKCTL
;;        RTS
;; ;
;;
