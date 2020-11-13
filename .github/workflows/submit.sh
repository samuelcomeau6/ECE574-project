#!/bin/bash
cd ../../
dir = $PWD
subfolder = "./submission/NetID1_NetID2_NetID3_dpgen"
mkdir $subfolder
cp ./src/cpp/dpgen/*.cpp $subfolder/src/
cp ./src/cpp/dpgen/*.h $subfolder/src/
cp ./src/cpp/dpgen/CMakeLists.txt $subfolder/src/