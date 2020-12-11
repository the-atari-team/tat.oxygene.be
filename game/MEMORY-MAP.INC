; cdw by 'The Atari Team' 2020
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

 .local

MEMORY_STRUCT=$0572

MEMORY_DISPLAYLISTS=$1000
MEMORY_OXYGENE_LETTERING=$15e0

MEMORY_GAME=$1900

; wir muessen etwas unter $b190 bleiben, sonst ueberschreiben wir load-game.wnf
MEMORY_LOAD_BUFFER=$bc00

MEMORY_OXYGENE_MENU_FONT=$ca00  ;  512 bytes fuer menu font
MEMORY_OXYGENE_FONT=$cc00       ; 1024 bytes oxygene font
MEMORY_OXYGENE_SHIELD_FONT=$F800

MEMORY_SHIP=$D800

MEMORY_PLAYMISSILE=$F800        ; hier liegt auch der SHIELD_FONT, ab $FA00
MEMORY_SHIELD=$Fad8             ; 40 bytes fuer die Zeile
