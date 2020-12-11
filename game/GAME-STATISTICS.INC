; -*- text -*-
; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;
; OXYGENE#2 Game statistics
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;

 .local

; setzt alle Game Statistic zaehler zurueck auf 0
@initGameStatistics
 LDA #0
 STA @RS_STAT_jets_DESTROYED
 STA @RS_STAT_enemies_DESTROYED
 STA @RS_STAT_enemies_DESTROYED+1
 STA @RS_STAT_hits
 STA @RS_STAT_shoots
 STA @RS_STAT_shoots+1
 STA @RS_STAT_buildingCollisions
 RTS


@incrementJetsDestroyed
 INC @RS_STAT_jets_DESTROYED
 RTS

@getDestroyedJets
 LDY @RS_STAT_jets_DESTROYED
 LDX #0
 RTS

@getJetsToDestroy
 LDY @RS_MISSION_JETS
 LDX #0
 RTS

@getEnemiesToDestroy
 LDY @RS_MISSION_ENEMIES
 LDX #0
 RTS

@incrementEnemiesDestroyed
 WINC @RS_STAT_enemies_DESTROYED
 RTS

@getKilledEnemies
 LDY @RS_STAT_enemies_DESTROYED
 LDX @RS_STAT_enemies_DESTROYED+1
 RTS


@incrementRaumerHits
 INC @RS_STAT_hits
 RTS


@getRaumerHits
 LDY @RS_STAT_hits
 LDX #0
 RTS


@incrementRaumerShoots
 WINC @RS_STAT_shoots
 RTS

@getRaumerShoots
 LDY @RS_STAT_shoots
 LDX @RS_STAT_shoots+1
 RTS


@incrementBuildingCollisions
 INC @RS_STAT_buildingCollisions
 RTS

@getBuildingCollisions
 LDY @RS_STAT_buildingCollisions
 LDX #0
 RTS


@getLanding
 LDY @RS_STAT_landing
 LDX #0
 RTS
