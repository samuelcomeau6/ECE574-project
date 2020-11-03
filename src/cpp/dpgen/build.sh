#!/bin/bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=release . -Bbuild
make -C./build/
cp ./build/dpgen .