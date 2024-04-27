#!/bin/bash

set -euo pipefail

ARCHS=('x86' 'x64')
COMPILERS=('g++')
BUILDTYPES=('debug' 'release')
BRANCHES=(
    'bgt'
    # 'blade' #new.h
    # 'bms' #mathlib
    # 'contagion' #g_pMemAlloc
    # 'cs2' #new.h
    # 'csgo' #new.h
    'css'
    # 'darkm' #public/game/client
    'dods'
    # 'doi' #new.h
    # 'dota' #new.h
    # 'episode1' #public/game/client
    'eye'
    'gmod'
    'hl2dm'
    # 'insurgency' #new.h
    'l4d'
    'l4d2'
    # 'mcv' #new.h
    'nucleardawn'
    'orangebox'
    # 'portal2' #new.h
    # 'pvkii' #mathlib
    # 'sdk2013' #mathlib
    # 'swarm' #new.h
    'tf2'
)
ROOT=$(pwd)
HL2SDK="$ROOT/include/hl2sdk"

# --depth=1 in workflow runners
if [ "$CI" = "true" ]
then
    cd "$HL2SDK"
    git remote set-branches origin '*'
    git fetch --all
    echo "Available branches:"
    echo "$(git branch --all)"
fi

# make sure build dir exists
if [ -d "bin" ]
then
    rm -r bin
fi
mkdir bin

for BRANCH in "${BRANCHES[@]}"
do
    cd "$HL2SDK"
    git checkout "$BRANCH"
    git pull
    cd "$ROOT"

    for ARCH in "${ARCHS[@]}"
    do
        if [ "$ARCH" = "x64" ]
        then
            if [ ! -d "$HL2SDK/lib/linux64" ]
            then
                echo "$BRANCH does not support 64bit, skipping!"
                continue
            fi
        fi

        for CMP in "${COMPILERS[@]}"
        do
            export CXX="$CMP"

            for TYPE in "${BUILDTYPES[@]}"
            do
                echo ""
                echo "------------------------------------"
                echo "Building $BRANCH-$CMP-$ARCH-$TYPE"
                echo "------------------------------------"
                echo ""
                
                if [ -d "build" ]
                then
                    rm -r build
                fi
                
                meson setup build \
                    -D buildtype="$TYPE" \
                    -D arch="$ARCH"
                cd build

                meson compile
                mv src/server_plugin.so ../bin/"server_plugin-$BRANCH-$CMP-$ARCH-$TYPE.so"
                cd ..
            done
        done
    done
done
