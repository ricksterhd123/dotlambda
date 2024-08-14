#! /usr/bin/bash

set -e
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=$SCRIPT_DIR/../build

mkdir -p $BUILD_DIR
pushd $BUILD_DIR
    if [ ! -d $BUILD_DIR/raylib ]; then
        git clone --depth 1 https://github.com/raysan5/raylib.git raylib
    fi
    pushd $BUILD_DIR/raylib
        mkdir -p build
        pushd $BUILD_DIR/raylib/build
            cmake -DBUILD_SHARED_LIBS=ON ..
            make
            sudo make install
        popd
    popd
popd
