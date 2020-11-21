#!/bin/bash
if [ -z "$1" ]
then
    buildtype=DEBUG
else
    buildtype=$1
fi
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=$buildtype . -Bbuild
make -C./build/
success=$?
cp ./build/hlsyn .
exit $success