;; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Raumer Structure
;
; Hier alle Variablen ablegen, die ueberall gebraucht werden

 .local

; sichern der aktuellen Adresse
?OLD_ADDRESS=*

 *=$0572 ; MEMORY_STRUCT

; TODO: menucolor_generator, um ein paar Bytes hier zu sparen?
@MENUCOLOR
 .byte 0,0
 .byte 0,$84,$86,$88,$8a,$8c,$8e,$8e,$8e,0
 .byte 0,$04,$06,$08,$0a,$0c,$0e,$0e,$0e,0
 .byte 0,$3e,$3c,$3a,$38,$36,$34,$34,$34,0
 .byte 0,$04,$06,$08,$0a,$0c,$0e,$0e,$0e,0
; .byte 0,$ee,$ec,$ea,$e8,$e6,$e4,$e2,$e2,0
 .byte 0,$e6,$e8,$ea,$ec,$ea,$e8,$e6,$e6,0
 .byte 0,$5e,$5c,$5a,$58,$56,$54,$54,$54,0
 .byte 0,$b4,$b6,$b8,$ba,$bc,$be,$be,$be,0
 .byte 0,$02,$02,$04,$04,$06,$06,$06,$06,0
 .byte 0,$08,$08,$0a,$0a,$0c,$0c,$0c,$0e,0
; .byte 0,$34,$36,$38,$3a,$3c,$3e,$3e,$3e,0
 .byte 0,$36,$38,$3a,$3c,$3a,$38,$36,$36,0
 .byte 0,$0c,$0c,$0a,$0a,$08,$08,$08,$08,0
 .byte 0,$06,$06,$04,$04,$02,$02,$02,$02,0
 .byte 0,$34,$36,$38,$3a,$3c,$3e,$3e,$3e,0
 .byte $3c,$3a,$38,$36,$34,$32,$30,$30,0,0

; @RS_VCOUNT_VBI
;  .byte 0,0,0,0,0

;@RS_VCOUNT_VBI_END
; .byte 0

 .byte $FF, $FF

@SHIP_X_POSITION
 .word 0

@SHIP_HSCROL
 .byte 0

@ENEMY_XPOS
 .byte 0

@RS_SHIELD_SHIP_XPOS
 .byte 48+6

@ENEMY_SHOT_XPOS
 .byte 0

@SHIELD_DECREASER
 .byte 0

@RAUMER_IN_EXPLOSION
 .byte 0

; Welche Displaylist ist gerade aktiv
; 0 == ship
; 1 == Menu
; 2 == done (after landing)
@RS_SHOW_DISPLAY_LIST
 .byte 0

@RS_NEED_INIT_ENEMY
 .byte 0

@RS_INIT_DONE
 .byte 0

; wir muessen diese Werte per DLI setzen, weil ein anderer DLI player 1 verbiegt
@RS_XPOS_PLAYER1 ; white Raumer
 .byte 0
@RS_XPOS_PLAYER2 ; red Raumer
 .byte 0
@RS_XPOS_MISSILE1 ; white Raumer
 .byte 0
@RS_XPOS_PLAYER3  ; Shadow Raumer
 .byte 0
@RS_XPOS_MISSILE3 ; Shadow Raumer
 .byte 0

@RAUMER_SHOT_XPOS
 .byte 0

@RS_TAT_XPOS
 .byte 116 ; 48+80-12

@RS_TEXT_HSCROL_XPOS
 .byte 0

; Hier alle Farben ablegen

@RS_STATLINE_COLOR
 .byte 4,4,8,12,14,12,8,4

@RS_ALL_COLOR

; Status Zeile farben
@RS_TEXT_COLOR
 .byte $08
 .byte $b8
 .byte $e8
 .byte $38

; TAT Symbol (Player Missiles)
@RS_TAT_COLOR0
 .byte 0
@RS_TAT_COLOR1
 .byte 0

; OXYGENE Letter Box
@RS_OXYGENE_LOGO_TEXT_COLOR
 .byte 0

@RS_OXYGENE_LOGO_TAT_SIGN
 .byte $32

; will fill somewhere else in test-player-missile code
@RS_OXYGENE_LOGO_COLOR
 .byte 2,2
 .byte 4,6
 .byte 8,10
 .byte 12,14
 .byte 12,10
 .byte 8,6
 .byte 4,2
 .byte 0

; Alle anderen Farben
@RS_ENEMY_COLOR
 .byte 0

@RS_RAUMER_COLOR_LIGHT
 .byte 0
@RS_RAUMER_COLOR_INNER
 .byte 0
@RS_RAUMER_COLOR_SHADOW
 .byte 0

@RS_SHIP_COLBK
 .byte 0
@RS_SHIP_COLOR0 ; light
 .byte 0
@RS_SHIP_COLOR1 ; shadow
 .byte 0
@RS_SHIP_COLOR2 ; normal
 .byte 0

@RS_SHIP_COLOR3STAR ; fourth color, starboard, steuerboard gruen
 .byte 0

@RS_SHIP_COLOR3MID  ; fourth color, mid ship ???
 .byte 0

@RS_SHIP_COLOR3PORT ; fourth color, port, backboard rot
 .byte 0

@RS_SHIELD_SHIP_COLOR
 .byte $8c
@RS_SHIELD_BACKGROUND2
 .byte 2
@RS_SHIELD_VERLAUF
 .byte $28
 .byte $18
 .byte $e8
 .byte $d8
 .byte $c8
 .byte $b8

@RS_MENU_COLOR_AND
 .byte $ff

@loadShipStatus
 .byte 0


; Hier die 4 Zeiger auf zu spielende Audio Listen, pro Kanal einer
; immer low- high-Byte
; wenn high-Byte == 0, ist der Kanal frei

@AUDIO_BUFFER_PTR
 .word 0,0,0,0

@AUDIO_NOT_PLAYED
 .byte 0

@AUDIO_TYPE
 .byte 0,0,0,0

; wird gerufen zum Abspielen von Sound, sobald initialisiert
@RS_AUDIO_PLAYER
 JMP $0000

; OPTIONS
; NICHT die Reihenfolge aendern, das wird exact so in einem array abgelegt

@OPTION_ENEMY_MAX_QUANTITY ; #0
 .byte 2

@OPTION_ENEMY_SHOT_ACCURACY
 .byte 1

@OPTION_ENEMY_SHOT_TYPE
 .byte 1

; TODO: der Killerschuss wird nicht aufgehalten, deshalb zaehlt der bei 1 gleich 8 runter!
@OPTION_ENEMY_SHOT_STRENGTH
 .byte 1

@OPTION_ENEMY_COLOR_MODE ; 0 simple color, 1 = add, 2 = random
 .byte 0

; Nur die Farbe, helligkeit ist immer $0c
@OPTION_ENEMY_COLOR ; Farbe
 .byte 12

; Shield size: 1(22), 2(34), 3(44), 4(56), 5(66)
@OPTION_RAUMER_SHIELD_STRENGTH
 .byte 5

@OPTION_IS_ENERGY_SLOWDOWN
 .byte 0

@OPTION_IS_FIRE_SLOWDOWN
 .byte 1

@OPTION_SHIP_COLLISION
 .byte 1

; Ship Farbe, helligkeit ist entsprechend $06 und $02 (shadow) damit die Sterne weiss bleiben immer $0c
@OPTION_SHIP_COLOR ; Farbe   #10
 .byte 0

; Gibt an, welches Schiff nachtraeglich geladen werden soll. D1:SHIP1.DAT mehr als 9 Schiffe passen nicht auf die Platte!
@OPTION_SHIP_NUMBER
 .byte 1

@OPTION_SHIELD_SLOWDOWN ; #12
 .byte 3

@OPTION_RAUMER_SHOT_SPEED
 .byte 3

@OPTION_HATEFACTOR_MODE ; #14
 .byte 1

@OPTION_HATEFACTOR_WAIT ; #15
 .byte 2

@OPTION_HATEFACTOR_ENEMY_HIT ; #16
 .byte 3

@OPTION_HATEFACTOR_RAUMER_HIT ; #17
 .byte 1

@OPTION_HATEFACTOR_RAUMER_SHOT ; #18
 .byte 1

@OPTION_ENEMY_SHOT_SPEEDUP ; Nicht einstellbar, kommt ueber Hatefactor
 .byte 0

@OPTION_FIRE_SLOWDOWN ; Nicht einstellbar, kommt aus Level/Mission
 .byte 255

@OPTION_ENERGY_SLOWDOWN ; Nicht einstellbar, kommt aus Level/Mission
 .byte 255

@OPTION_RAUMERMOVE_SLOWDOWN ; Nicht einstellbar, kommt aus Level/Mission
 .byte 128

; Diese Optionen ergeben sich aus dem aktuellen Level
@USE_LEVEL
 .byte 1

@CURRENT_LEVEL
 .byte 3      ; easy ist der Level beim ersten Start

@START_HATE_FACTOR
 .byte 0,0

@OPTION_HF_GETDOWN
 .byte 0

@OPTION_RAUMERSHOT_HF_ADD
 .byte 0

@OPTION_RAUMERHIT_HF_SUB
 .byte 0

@OPTION_JET_DESTORY_HF_ADD
 .byte 0

@OPTION_ENEMY_DESTROY_HF_ADD
 .byte 0


; Statistics
@RS_STAT_jets_DESTROYED
 .byte 0

@RS_STAT_enemies_DESTROYED
 .word 0

@RS_STAT_hits
 .byte 0

@RS_STAT_shoots
 .word 0

; TODO: buildingCollisions
@RS_STAT_buildingCollisions
 .byte 0

@RS_STAT_landing
 .byte 0

@RS_STAT_TIME
 .word 0

; will decrement when @RS_STAT_TIME arrives 0
@RS_STAT_TIME_STATUS
 .byte 0

; Mission Goals
@RS_MISSION_JETS
 .byte 0

@RS_MISSION_ENEMIES
 .byte 0

; die Mission Time ist 1/19 der Gesamtzeit, wird jeder 1/50s um 1 runtergezaehlt
@RS_MISSION_TIME
 .word 0

@RS_MISSION_HITS
 .byte 0

@RS_MISSION_SHOOTS
 .byte 0

; TODO: noch nicht ausgegoren
@RS_MISSION_ENERGY
 .byte 0

@RS_MISSION_ENDLESS_SHIP = $DA00
;  .byte 0

; Mission status

@RS_MISSION_FAILED ; bei 1 ist die Mission fehlgeschlagen
 .byte 0

@RS_CURRENT_MISSION
 .byte 1

@RS_DMA
 .byte 1

; wiederherstellen der aktuellen Adresse
 *=?OLD_ADDRESS

