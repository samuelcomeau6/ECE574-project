#!/bin/bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=$1 . -Bbuild
make -C./build/
success=$?
cp ./build/dpgen .
exit $success