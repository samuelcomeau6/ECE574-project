#!/bin/bash
cd ../../
dir=$PWD
subfolder="./submission/NetID1_NetID2_NetID3_dpgen"
rm -rf $subfolder
mkdir -p $subfolder/src
cp ./src/cpp/dpgen/*.cpp $subfolder/src/
cp ./src/cpp/dpgen/*.h $subfolder/src/
cp ./src/cpp/dpgen/*.vh $subfolder/src/
cp ./src/cpp/dpgen/CMakeLists.txt $subfolder/src/
cp ./src/cpp/dpgen/CMakeLists.txt $subfolder/
printf "add_subdirectory(src)" > $subfolder/CMakeLists.txt
