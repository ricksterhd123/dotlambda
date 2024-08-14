#! /usr/bin/bash

set -e
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=$SCRIPT_DIR/../build


mkdir -p $BUILD_DIR
pushd $BUILD_DIR
cmake ..
cmake --build .
popd
