#!/bin/bash
set -e
rm -f ./hlsynd
rm -f ./hlsynr
mkdir -p build/debug
mkdir -p build/release
cmake -DCMAKE_BUILD_TYPE=DEBUG . -Bbuild/debug
cmake -DCMAKE_BUILD_TYPE=RELEASE . -Bbuild/release
make -C./build/debug
make -C./build/release
success=$?
cp ./build/debug/hlsyn ./hlsynd
cp ./build/release/hlsyn ./hlsynr
exit $success