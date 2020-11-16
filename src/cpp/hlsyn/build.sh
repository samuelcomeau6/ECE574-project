#!/bin/bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=DEBUG . -Bbuild
make -C./build/
success=$?
cp ./build/hlsyn .
exit $success