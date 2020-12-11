# Oxygene Be

Oder Oxygene Part 2

Ein horizontales Ballerspiel das eigentlich nur zeigen soll,
was grafisch auf dem Atari XL/XE möglich ist. Es braucht
64kb RAM und läuft nicht mehr auf den alten 400/800er.

Das einzige, was vom alten Original übernommen wurde,
ist der Raumer, die Gegner und der Zeichensatz für die großen Schiffe. 

Das Spiel ist sonst komplett neu geschrieben worden.

1. Diskette einlegen und booten ohne Basic.
2. Der Loader erscheint nach ein paar Sektoren und begleitet einen bis zum eigentlichen Start der Spiels.
3. Das Hauptmenü erscheint, hier kann der Level gewählt werden und die Mission.
Des weiteren können einige Einstellungen hier direkt überprüft werden. Einfach mit den Cursortasten auswählen.
4. Das Hauptmenü durch Space oder Trigger verlassen, gelangt man in die Missionsübersicht, die zeigt, was alles
zu erledigen ist.
5. Das Spiel startet nach Space oder Trigger. Jetzt heißt es Feuer frei.
Mit seinem kleinen Raumer fliegt man horizontal über
ein großes Schiff und zerstört dabei die feindlichen Jets die
überall auf den Landebahnen herum stehen und auch die Gegner
vor sich. Diese schießen zwar nur vereinzelt, dafür recht gezielt und werden
vergrätzter je mehr man von ihnen abknallt oder je mehr Jets
vernichtet wurden. Die Gegner ändern dann ihre Farbe.
Der Schwierigkeitsgrad steigt somit an.
Wurde die geforderte Anzahl an Jets und Gegnern aus dem Weg geräumt,
muss noch auf dem großen Schiff gelandet werden. Das funktioniert
nur, wenn der kleine Raumer von links die
drei übereinander stehenden Pfeile einer leeren Landebahn gerade
überfliegt, die am Ende der grossen Schiffe ist.
Damit die Mission nicht zu einfach wird, stören hohe Gebäuden
und Masten den freien Flug, erkennbar an langen Schatten, die überall
auf dem großen Schiff herum stehen.
Eine Berührung kostet sehr viel Energy, meist sogar den Raumer,
also obacht.
6. Am Ende gibt es noch einen Statusbericht, was man alles erledigt hat. Daran wird dann auch festgelegt
ob die Mission Erfolgreich war ober fehlgeschlagen ist.
Jetzt kann mit Trigger oder Joystick hoch die nächste Mission gestartet werden.
Hat man alle Missionen erfolgreich beendet, geht es im nächsten Level mit höherem Schwierigkeitsgrad von vorne los.
 
## Technisches

* Alle Raumer-Animationen sind neu erstellt, es gibt mehr und bessere Animationen.
* Selbst die Schüsse vom Raumer und Gegner sind animiert, sieht halt besser aus.
* Es gibt mehr unterschiedliche Feinde, 2-4 werden übereinander dargestellt.
* Die Displaylists sind optimiert, brauchen weniger Speicher, der Oxygene Schriftzug ist auf
 32 Bytes pro Zeile verkleinert.
* Die Displaylist-Interrupts sind neu geschrieben.
* Es gibt wesentlich mehr Farben als im alten Spiel.
* Der Raumer hat ein Energy-Schild, einfache Schüsse führen nicht gleich zum Ableben, aber der Raumer wackelt.
* Das "Joy of Use" wurde gavierend verbessert.
* Es gibt keine dummen Random-Gegner mehr, die einfach losballern.
* Die Gegner kommen immer von vorn und wechseln die Seiten, wenn der Raumer die Richtung wechselt.
* Es gibt 3 verschiedene Arten von Schüssen bei den Gegnern in unterschiedlichen Geschwindigkeiten
* Es schießt immer der am Raumer nächsten stehende Gegner 
* Es existiert eine Art "Böse-Faktor" je mehr man die Gegner oder Jets zerstört, desto böser
 werden die Gegner, zu sehen an dessen Farbe.
* Es existieren jetzt Missionen, die erfüllt werden müssen
* Unterschiedlich viele Jets auf der Oberfläche der großen Schiffe sind zu vernichten,
 unterschiedlich viele Gegner zu killen, dazu läuft die Zeit ab die man hat.
* Dazu gibt es unterschiedliche Schwierigkeitsgerade von God-Mode bis Suicide. (Select key)
* Zusätzlich können etliche Dinge in einem Menü selbst manipuliert werden, um damit mal rumzuspielen.
 (Pfeiltasten)
* Auf Wunsch gibt es jetzt einen Highscore.

## Atari-technisches:
* Das Spiel nutzt die 64 kb fast komplett aus
* Auf der Boot-Diskette wird LiteDOS verwendet, da es einem ~4kb mehr Speicher nutzen läßt.
* die PM-Grafik liegt unter dem OS, auch die Zeichensätze und die großen Schiffe.
* Das Umschalten zw. RAM und OS kommt von TurboBasic. Routinen folgen bei Interesse!
* Die Zeichensätze, Bilder und Schiffsgrafiken liegen in einzelnen Dateien vor, das
 vereinfacht dessen Austausch/Nutzung. 
* Das TAT-Sign basiert auf Player-Missile-Grafik. Spart ordentlich Speicher.
* Der Raumer braucht insgesamt 3 Player mit Schatten und 2 Missiles.
* Der Raumer-Schuss nutzt einen Missile
* Die Gegner nutzen einen Player. Aufgrund der wenigen Zeit die der 8-Bitter einem lässt
 wurde hier auf DLI-Tricks verzichtet.
* Der Gegner-Schuss nutzt einen Missile, diese sind unterschiedlich animiert
 und unterschiedlich gefährlich.
* Das große Schiff benötigt 17*512 Bytes und wird immer wieder von Diskette nachgeladen,
 um dessen Größe etwas zu verkleinern sind diese Run-length-encoded mit einem alten Algorithmus aus
 der Happy-Computer.
* Für Interessierte, es existiert ein kleiner Editor mit dem sich "leicht" weitere Schiffe erstellen lassen.
* Die Energy-Level-Zeile ist mittels GTIA-Trick (PRIOR=$80) und einer Graphics 0-Zeile
nebst einem kleinen Zeichensatz entstanden. War ein Trick aus der Hexenküche von P.Finzel.
Mittels Dithering gaukelt man so einen Farbverlauf mit 11 Farben in einer Zeile vor.
Das kleine Schiff rechts davon ist ein Player. 
* Die Sounds sind komplett neu und ähnlich wie der Soundgenerator aus der Hexenküche von P.Finzel. 
* Leider gibt es aktuell keine Titelmelodie, sign.
 
## Technisches zum Spiel:
Das Spiel ist jetzt auf einer Boot-Diskette mit LiteDOS 3.01.
Es gibt einen Game-Loader, der grob anzeigt, das beim Laden etwas passiert, weil fast 64kb
erstmal geladen werden müssen.
Dann öffnet sich das Hauptmenü, hier kann der Level und die Mission gewählt werden(Select/Option).
* Es existieren 8 Level, gestartet wird mit Easy, was nicht dem ersten Level entspricht, weil es sonst
einfach zuu leicht wäre. Mit etwas Übung lassen sich auch die höheren Level noch spielen. 
* Per Cursor-Tasten kann man ein paar Dinge direkt anpassen, dann geht es aber in den Free-Style-Mode.
Zum Üben existiert auch ein God-Mode, wo Treffer von Gegnern und Berührungen mit hohen Gebäuden einem
nichts anhaben.
* Weiter mit Space, oder Feuerknopf.
* Es wird die Mission angezeigt, wie viele Gegner zu vernichten sind und wie viele Jets vom Schiff
geschossen werden müssen. Man möge auf die Zeit und die eigene Energy achten.
Am Ende soll man auf dem Schiff landen.
* Mit Feuerknopf oder Space geht es zum Spiel.
* Mit Esc kann das Spiel abgebrochen werden.
 
## Technisches beim Entwickeln: 
Große Teile des Spiels wurden in einer ALGOL ähnlichen Hochsprache
geschrieben, und warum nicht Action!?
Weil mir damals (1988) Action! einfach zu teuer war (350,-DM).
Also habe ich mir aus der
öffentlichen Bibliothek ein paar Bücher über Compiler(bau) angelesen
und einen Compiler selbst gebaut.
In TurboBasic wohlgemerkt. Diesen Compiler habe ich jetzt nochmals
überarbeitet und die
eklatantesten Fehler beseitigt. Er unterstützt die Datentypen Byte und Word auch als Array.
Damit auch Strings(Byte Arrays) kennt Proceduren/Funktionen mit mehreren Parametern,
kann rekursiv arbeiten, bis der 6502-Stack überläuft. Der Compiler kann mit relativ komplizierteren
Ausdrücken hantieren, 2er-Komplement Multiplikationen/Divisionen werden per Shift übersetzen.
Er kennt if-then-else und for-, while-, repeat-until-Schleifen.
Der Overhead zu reinem Assembler ist da, aber dafür ist der Source-Code sehr
viel einfacher zu warten. Er arbeitet auch sehr gut mit Assembler zusammen und
ein Goody, die erstellten Programme laufen fast immer in (Turbo)Basic.
Der Compiler erstellt Code, der nur die Floatingpoint-Register verwendet. Es sei denn, man weist den Variablen andere
Speicherbereiche zu.
Der Compiler lädt die Sourcen stückweise von Diskette/Harddisk,
übersetzt den Code in Assembler (fast) MAC/65 kompatibel, aber voll atasm kompatibel.
Mit dem atari800 Emulator, der im Turbo-Mode locker Faktor 200 schneller als der original
Atari ist, kann man einigermaßen flott arbeiten. Den Atari800 Emulator habe ich mir etwas gepatcht,
damit ich den atari800-Emulator auch per illegaler Instruction "von innen" beenden kann.
Dazu ein paar Bash-Scripte und ein Editor wie IntelliJ und fertig ist die eigene Entwicklungsumgebung.
Ach ja, den Altirra nutze ich gerne zum Gegenprüfen und debuggen, die atasm-Labels werden
automatisch per Parameter eingelesen.

Es macht Spass wieder für den Atari 8bitter zu entwickeln, 
das einzige wirklich große Übel, der ständige Speichermangel bei 64kb.


August 2020, Lars
