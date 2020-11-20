#!/bin/bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=notDEBUG . -Bbuild
make -C./build/
success=$?
cp ./build/hlsyn .
exit $success