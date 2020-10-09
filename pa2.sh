//This must function properly according to description
cd ${{ secrets.netids }}_dpgen
mkdir build
cd build
cmake ..
make
./src/dpgen
