#!/usr/bin/env bash
LOCATIONS=("/usr/local/share/Qt/5.5/gcc_64")
LIBS=("/usr/local/share/Qt/5.5/gcc_64/lib")
INCLUDES=("/usr/local/share/Qt/5.5/gcc_64/include")

LOC=""
LIB=""
INC=""

for loc in ${LOCATIONS[@]}; do
    if [ -e "${loc}" ]; then
        LOC="${loc}"
    fi
done

if [ -z "$LOC" ]; then
    LOC="`pkg-config --variable=bindir Qt5`"
fi

echo -n "QT_PATH=$LOC "

for loc in ${LIBS[@]}; do
    if [ -e "${loc}" ]; then
        LIB="${loc}"
    fi
done

if [ -z "$LIB" ]; then
    LIB="`pkg-config --variable=libdir Qt5`"
fi

echo -n "QT_LIB=$LIB "

for loc in ${INCLUDES[@]}; do
    if [ -e "$loc" ]; then
        INC="$loc"
    fi
done

if [ -z "$INC" ]; then
    INC="`pkg-config --variable=headerdir Qt5`"
fi
echo -n "QT_INC=$INC "

echo
