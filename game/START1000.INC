; -*- text -*-
;
; OXYGENE#2 testgame-starter
;
; VORSICHT, wir starten ab $1000
; Das geht nur mit den alt bekannten Game-Loadern oder LiteDOS
;

 .local

; sichern der aktuellen Adresse
?OLD_ADDRESS=*

 *=736

 .word $1000


; wiederherstellen der aktuellen Adresse
 *=?OLD_ADDRESS

