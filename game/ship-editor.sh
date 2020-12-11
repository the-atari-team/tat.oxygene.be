#!/bin/bash

COMPILERPATH=../compiler
MACRO_N_RUNTIME=$(pwd)/${COMPILERPATH}
MORE_INCLUDES=$(pwd)

cd /tmp/atari

cp ${MACRO_N_RUNTIME}/starter20.atr .
cp ${MACRO_N_RUNTIME}/Turbo-Basic_XL_2.0.com .
cp ${MACRO_N_RUNTIME}/AUTORUN.TUR .
cp ${MORE_INCLUDES}/DLISTEDT.COM .
cp ${MORE_INCLUDES}/OXYFONTE.COM .
cp ${MORE_INCLUDES}/DRAWBLCK.COM .
cp ${MORE_INCLUDES}/ship-editor.lst .
cp ${MORE_INCLUDES}/TRYOPEN.LST .
cp -v ${MORE_INCLUDES}/ship-packer/*.LST .


SHIP_LIST="1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
index=1

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


#cp -v ${MORE_INCLUDES}/ships/SHIPJ.DAT SHIP-J.DAT
#cp -v ${MORE_INCLUDES}/ships/SHIPK.DAT SHIP-K.DAT # 1. Abbuc Ship
#cp -v ${MORE_INCLUDES}/ships/SHIPL.DAT SHIP-L.DAT # 2.
#cp -v ${MORE_INCLUDES}/ships/SHIPM.DAT SHIP-M.DAT # 3
## cp -v ${MORE_INCLUDES}/ships/SHIPN.DAT SHIP-N.DAT
#cp -v ${MORE_INCLUDES}/ships/SHIPO.DAT SHIP-O.DAT # 5
#cp -v ${MORE_INCLUDES}/ships/SHIPP.DAT SHIP-P.DAT # 6
#cp -v ${MORE_INCLUDES}/ships/SHIPQ.DAT SHIP-Q.DAT # 7
#cp -v ${MORE_INCLUDES}/ships/SHIPS.DAT SHIP-S.DAT #
#cp -v ${MORE_INCLUDES}/ships/SHIPT.DAT SHIP-T.DAT # 9
#cp -v ${MORE_INCLUDES}/ships/SHIPY.DAT SHIP-Y.DAT
#cp -v ${MORE_INCLUDES}/ships/SHIPZ.DAT SHIP-Z.DAT

cat >.insert.txt <<EOF
Turbo-Basic_XL_2.0.com -> AUTORUN.SYS
AUTORUN.TUR
ship-editor.lst -> AUTORUN.LST
TRYOPEN.LST
DLISTEDT.COM
OXYFONTE.COM
DRAWBLCK.COM
EOF

# cat .assembled.txt >>.insert.txt

xldir starter20.atr insert .insert.txt editor.atr

DISK_NEW=editor.atr

if [ "$OS" == "Windows_NT" ]; then
  WINDOWSIZE="-win-width 682 -win-height 482"
else
  WINDOWSIZE="-win-width 1008 -win-height 720"
fi

atari800 \
    -hreadwrite \
    -H2 /tmp/atari \
    -xlxe_rom ${MACRO_N_RUNTIME}/../firmware/ATARIXL.ROM \
    -xl -xl-rev 2 \
    -pal -showspeed \
    -windowed $WINDOWSIZE \
    -no-vsync -video-accel -nosound \
    -turbo \
    ${DISK_NEW}

exit 0
