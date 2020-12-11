#!/bin/bash

COMPILERPATH=../compiler
MACRO_N_RUNTIME=$(pwd)/${COMPILERPATH}
MORE_INCLUDES=$(pwd)

mkdir -p /tmp/atari

cd /tmp/atari

cp ${MACRO_N_RUNTIME}/starter20.atr /tmp/atari
cp ${MACRO_N_RUNTIME}/Turbo-Basic_XL_2.0.com /tmp/atari
cp ${MACRO_N_RUNTIME}/AUTORUN.TUR /tmp/atari

cp -v ${MORE_INCLUDES}/ship-packer/*.LST /tmp/atari


SHIP_LIST="1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
index=1

if [ -e SHIPK.COM ]; then
  SIZE=$(stat --format=%s SHIPK.COM)
  if [ $SIZE -ne 8710 ]; then
    echo "SHIPS already packed"
    exit 0
  fi
fi

echo "copy ships"
for SHIP in $SHIP_LIST; do
  SHIPNAME_SOURCE="SHIP${SHIP}.DAT"
  echo -n "copy $SHIPNAME_SOURCE "
  if [ -e ${MORE_INCLUDES}/ships/$SHIPNAME_SOURCE ]; then
    SHIPNAME_DEST="SHIP-${SHIP}.DAT"
    if [ -e $SHIPNAME_DEST ]; then
      echo "already exist as $SHIPNAME_DEST, will not copy!"
    else
      cp  ${MORE_INCLUDES}/ships/${SHIPNAME_SOURCE} ${SHIPNAME_DEST}
      echo "copyed as ${SHIPNAME_DEST}"
    fi
    index=$(($index + 1))
  else
    echo "does not exist."
  fi
done

${MACRO_N_RUNTIME}/os-type.sh >.os.txt

cat >.insert.txt <<EOF
Turbo-Basic_XL_2.0.com -> AUTORUN.SYS
AUTORUN.TUR
.wnffiles.txt -> WNFFILES.TXT
.os.txt -> OS.TXT
SHIP-PACKER.LST -> AUTORUN.LST
EOF


xldir starter20.atr insert .insert.txt packer.atr

DISK_NEW=packer.atr
WINDOWSIZE="-win-width 682 -win-height 482"

if [[ "$OS" != "Windows_NT" ]]; then
  ATARI800_OPTIONS="-exitEmulatorAtOpCode02"
else
  ATARI800_OPTIONS="-bbrk"
fi

atari800 \
    -hreadwrite \
    -H2 /tmp/atari \
    -xlxe_rom ${MACRO_N_RUNTIME}/../firmware/ATARIXL.ROM \
    -xl -xl-rev 2 \
    -pal -showspeed \
    -windowed $WINDOWSIZE \
    -no-vsync -video-accel -nosound -nojoystick \
    ${ATARI800_OPTIONS} \
    -turbo \
    ${DISK_NEW}

exit 0
