#!/usr/bin/env bash
LOCATIONS=("/usr/lib64/qt5" "/usr/local/share/Qt-5.5.1/5.5/gcc_64")
LIBS=("/usr/lib64/qt5" "/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib")
INCLUDES=("/usr/include/qt5" "/usr/local/share/Qt-5.5.1/5.5/gcc_64/include")

if [ ! $# = 1 ]; then
    exit 0
fi

if [ $1 = "-f" ]; then
    for loc in ${LOCATIONS[@]}; do
        if [ -e "$loc" ]; then
            echo "$loc"
            exit 0
        fi
    done
fi

if [ $1 = "-l" ]; then
    for loc in ${LIBS[@]}; do
        if [ -e "$loc" ]; then
            echo "$loc"
            exit 0
        fi
    done
fi

if [ $1 = "-i" ]; then
    for loc in ${INCLUDES[@]}; do
        if [ -e "$loc" ]; then
            echo "$loc"
            exit 0
        fi
    done
fi
