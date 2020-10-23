#!/bin/bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Debug . -Bbuild
make -C./build/
cp ./build/dpgen .