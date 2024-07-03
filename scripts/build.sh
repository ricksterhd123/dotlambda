#! /usr/bin/bash

set -e
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=$SCRIPT_DIR/../build

# Build raylib
function build_raylib() {
    if [ ! -d $BUILD_DIR/raylib ]; then
        git clone --depth 1 https://github.com/raysan5/raylib.git raylib
    fi

    pushd ./raylib/src
    make RAYLIB_RELEASE_PATH=../..
    popd
}

mkdir -p $BUILD_DIR
pushd $BUILD_DIR

build_raylib

cmake ..
cmake --build .
popd
