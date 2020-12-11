;; -*- text -*-
;
; OXYGENE#2 testgame-starter
;

 .local

; sichern der aktuellen Adresse
?OLD_ADDRESS=*

 *=736

 .word $4000


; wiederherstellen der aktuellen Adresse
 *=?OLD_ADDRESS

