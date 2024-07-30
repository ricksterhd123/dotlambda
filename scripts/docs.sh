#! /usr/bin/bash

set -e
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=$SCRIPT_DIR/../docs

mkdir -p $BUILD_DIR

pushd $BUILD_DIR
wget https://small.r7rs.org/attachment/r7rs.pdf
popd
