# cdw by 'The Atari Team' 2020
# licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]

CC=wnfc
ASM=atasm

.PHONY: copy_atari_files prepare_atari clean all prepare basic_tests

ASM_FILES=\
oxygene-displaylist.INC \
oxygene-font.INC \
oxygene-menu-font-2.INC \
SHIELDFONT.INC \
oxygene-logo-32.INC

OXYGENE_BUILD_FILES= \
HEXDMP64.65o \
LOADGAME.65o \
OXYGENBE.65o \
SHLDFONT.COM \
FONT.COM \
MENUFONT.COM \
OXYLOGO.COM \
DSPLIST.COM

EDITOR_BUILD_FILES=\
DLISTEDT.COM \
OXYFONTE.COM \
DRAWBLCK.65o

COMPILER_PATH=../compiler

COMPILER_INCLUDES= \
$(COMPILER_PATH)/FAST_SCREEN_OUTPUT.INC \
$(COMPILER_PATH)/SCREEN_OUTPUT.INC \
$(COMPILER_PATH)/PRINTF.INC \
$(COMPILER_PATH)/MATH.INC \
$(COMPILER_PATH)/MATH_SHIFT.INC \
$(COMPILER_PATH)/ARRAY.INC \
$(COMPILER_PATH)/GETCHAR.INC \
$(COMPILER_PATH)/STICK.INC \
$(COMPILER_PATH)/TIME.INC \
$(COMPILER_PATH)/DOS.INC \
$(COMPILER_PATH)/IO.INC \
$(COMPILER_PATH)/BACKCOLORLINE.INC \
$(COMPILER_PATH)/COMPARE.INC \
$(COMPILER_PATH)/BASIC.INC

GAME_INCLUDES=\
SIMPLE-64K.INC \
MEMORY-MAP.INC \
RAUMER-STRUCT.INC \
ENEMY.INC \
RAUMER.INC \
COLLISIONS.INC \
KEYCODE.INC \
OXYGENE-AUDIO-PLAYER.INC \
GAME-STATISTICS.INC \
TAT.INC \
OXYGENE.INC \
HIGHSCORE.INC \
MENU-COLOR.INC

GAME_GENERATED_INCLUDES=\
AUDIOLST.INC \
BINLOAD.INC \
HATEFACT.INC \
MENU.INC \
SHIELD.INC \
OXYLOGO.INC

ALL_INCLUDES=$(COMPILER_INCLUDES) $(GAME_INCLUDES) $(GAME_GENERATED_INCLUDES)

ADDITIONALS=\
oxygene-game.atr

all: $(INCLUDES) oxygene

copy:
	cp $(COMPILER_INCLUDES) ../../lla.oxygene.be/compiler
	cp $(GAME_INCLUDES) ../../lla.oxygene.be/game
	cp $(ASM_FILES) ../../lla.oxygene.be/game

clean::
	rm -f .wnffiles.txt
	rm -f $(ADDITIONALS) $(OXYGENE_BUILD_FILES)
	rm -f $(GAME_GENERATED_INCLUDES)
	rm -f *.COM *.ASM .insert.txt
	rm -f SHIP*.DAT
	rm -f editor.atr
	rm -rf /tmp/atari

clean::
	rm -f $(EDITOR_BUILD_FILES)
	rm -f SHIP-M.DAT

SHLDFONT.COM: SHIELDFONT.INC
	$(ASM) $< -o$@ >/dev/null

FONT.COM: oxygene-font.INC
	$(ASM) $< -o$@ >/dev/null

MENUFONT.COM: oxygene-menu-font-2.INC
	$(ASM) $< -o$@ >/dev/null

# Alternativer Menufont
# MENUFONT.COM: oxygene-menu-font.INC
#	$(ASM) $< -o$@ >/dev/null

OXYLOGO.COM: pictures/oxygene-logo-32.INC OXYLOGO.INC
	$(ASM) $< -o$@ >/dev/null

DSPLIST.COM: oxygene-displaylist.INC DLI.INC RAUMER-STRUCT.INC
	$(ASM) $< -o$@ >/dev/null


OXYLOGO.INC: pictures/oxygene-logo-32.wnf
	$(CC) $< -o .

AUDIOLST.INC: oxygene-audio.wnf RAUMER-STRUCT.INC
	$(CC) $< -O 2

MENU.INC: menu.wnf RAUMER-STRUCT.INC
	$(CC) $< -O 2

SHIELD.INC: shield.wnf RAUMER-STRUCT.INC
	$(CC) $< -O 2

HATEFACT.INC: hatefactor.wnf RAUMER-STRUCT.INC
	$(CC) $< -O 2

OXYGENBE.65o: test-player-missile.wnf $(ALL_INCLUDES)
	$(CC) $< -O 2 -smallHeapPtr -I ../compiler
	$(ASM) $(@:.65o=.ASM) >/dev/null
#	$(ASM) -ha -s $(@:.65o=.ASM) -g$(@:.65o=.lst) -l$(@:.65o=.lab) >$(@:.65o=.log)

#
# Boot-loader
#
LOADGAME.65o: load-game.wnf BINLOAD.INC
	$(CC) $< -O 2 -smallHeapPtr -I ../compiler
	$(ASM) $(@:.65o=.ASM) >/dev/null
#	$(ASM) -ha -s $(@:.65o=.ASM) -g$(@:.65o=.lst) -l$(@:.65o=.lab) >$(@:.65o=.log)

BINLOAD.INC: binload.wnf
	$(CC) $< -O 2



#
# Ship-Editor
#

# Displaylist fuer Editor
DLISTEDT.COM: oxygene2-editor-displaylist.INC
	$(ASM) $< -o$@ >/dev/null

# Font fuer Editor (andere Addresse)
OXYFONTE.COM: oxygene-font-editor.INC
	$(ASM) $< -o$@ >/dev/null

# Draw Blocks, wird nur im Editor verwendet
DRAWBLCK.65o: drawblock.wnf
	$(CC) $< -O 2 -I ../compiler
	$(ASM) $(@:.65o=.ASM) >/dev/null
	cp $@ $(@:.65o=.COM)


# Hexdump Editor, der OS-ROM/OS-RAM umschalten kann
HEXDMP64.65o: hexdump64.wnf BINLOAD.INC
	$(CC) $< -O 2 -I ../compiler
	$(ASM) $(@:.65o=.ASM) >/dev/null
	cp $@ $(@:.65o=.COM)



copy_atari_files:
	../compiler/os-type.sh >.os.txt

SHIPS=\
SHIPK.COM \
SHIPJ.COM \
SHIPL.COM \
SHIP-M.DAT \
SHIPN.COM \
SHIPO.COM \
SHIPP.COM \
SHIPQ.COM \
SHIPS.COM \
SHIPT.COM

$(SHIPS):
	./packer.sh
	cp /tmp/atari/SHIP-K.PAK SHIPK.COM
	cp /tmp/atari/SHIP-J.PAK SHIPJ.COM
	cp /tmp/atari/SHIP-L.PAK SHIPL.COM
	cp /tmp/atari/SHIP-M.DAT SHIP-M.DAT
	cp /tmp/atari/SHIP-N.PAK SHIPN.COM
	cp /tmp/atari/SHIP-O.PAK SHIPO.COM
	cp /tmp/atari/SHIP-P.PAK SHIPP.COM
	cp /tmp/atari/SHIP-Q.PAK SHIPQ.COM
	cp /tmp/atari/SHIP-S.PAK SHIPS.COM
	cp /tmp/atari/SHIP-T.PAK SHIPT.COM

prepare_atari ::
	echo "ASCIISHP.DAT" >.insert.txt
	echo "SHLDFONT.COM" >>.insert.txt
#	echo "SHIELDFONT.65o -> SHLDFONT.COM" >>.insert.txt
	echo "FONT.COM" >>.insert.txt
#	echo "oxygene-font.65o -> FONT.COM" >>.insert.txt
	echo "# oxygene-menu-font.65o -> OXYMFONT.COM" >>.insert.txt
	echo "# 583" >>.insert.txt
	echo "MENUFONT.COM" >>.insert.txt
#	echo "oxygene-menu-font-2.65o -> MENUFONT.COM" >>.insert.txt
	echo "# shield.lst -> SHIELD.LST" >>.insert.txt
	echo "# # 466 + 360 + 722" >>.insert.txt
	echo "DSPLIST.COM" >>.insert.txt
#	echo "oxygene-displaylist.65o -> DSPLIST.COM" >>.insert.txt
	echo "# 60" >>.insert.txt
	echo "OXYLOGO.COM" >>.insert.txt
#	echo "oxygene-logo-32.65o -> OXYLOGO.COM" >>.insert.txt
	echo "OXYGENBE.65o -> OXYGENBE.COM" >>.insert.txt
	echo "#" >>.insert.txt
	echo "SHIPK.COM -> SHIP1.COM" >>.insert.txt
	echo "SHIPJ.COM -> SHIP2.COM" >>.insert.txt
	echo "SHIPL.COM -> SHIP3.COM" >>.insert.txt
	echo "SHIP-M.DAT -> SHIP4.COM" >>.insert.txt
	echo "SHIPN.COM -> SHIP5.COM" >>.insert.txt
	echo "SHIPO.COM -> SHIP6.COM" >>.insert.txt
	echo "SHIPP.COM -> SHIP7.COM" >>.insert.txt
	echo "SHIPQ.COM -> SHIP8.COM" >>.insert.txt
	echo "SHIPS.COM -> SHIP9.COM" >>.insert.txt
	echo "SHIPT.COM -> SHIPA.COM" >>.insert.txt
	echo "#" >>.insert.txt
	echo "# HEXDUMP.65o -> HEXDUMP.COM" >>.insert.txt
	echo "# LOADGAME.COM -> AUTORUN.SYS LiteDOS kennt die AUTORUN.SYS nicht" >>.insert.txt
	echo "LOADGAME.65o -> LOADGAME.AU0" >>.insert.txt
	echo "abbuc/description-long.md -> README.MD" >>.insert.txt
	echo "abbuc/beschreibung-lang.md -> LIESMICH.MD" >>.insert.txt


oxygene_disk: copy_atari_files prepare_atari LiteDOS-ED-starter.atr $(SHIPS) .insert.txt
	xldir LiteDOS-ED-starter.atr insert .insert.txt oxygene-game.atr

atari_oxygene: oxygene_disk
	atari800 \
    -xlxe_rom ../firmware/ATARIXL.ROM \
    -xl -xl-rev 2 \
    -ntsc -showspeed -nobasic \
    -windowed -win-width 682 -win-height 482 \
    -vsync -video-accel -sound \
    oxygene-game.atr


prepare:
	rm -f .wnffiles.txt

oxygene: prepare $(OXYGENE_BUILD_FILES) oxygene_disk

start-game: atari_oxygene

editor: $(EDITOR_BUILD_FILES)
	./ship-editor.sh

help:
	@echo "Makefile for the Atari 8bit game Oxygene-BE 2020"
	@echo "usage:"
	@echo "make             - to create the whole game disk"
	@echo "make clean       - remove all build files"
	@echo "make start-game  - start Oxygene BE in atari800 emulator"
	@echo "make help        - show this list"
	@echo "make editor      - start ship editor"
