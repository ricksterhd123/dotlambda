#! /usr/bin/bash

set -e
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=$SCRIPT_DIR/../build

mkdir -p $BUILD_DIR
pushd $BUILD_DIR
    if [ ! -d $BUILD_DIR/chibi-scheme ]; then
        git clone https://github.com/ashinn/chibi-scheme.git chibi-scheme
    fi
    pushd ./chibi-scheme
        make
        sudo make install
    popd
popd
