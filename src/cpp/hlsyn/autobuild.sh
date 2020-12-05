#/bin/bash
while true
do
inotifywait -emodify ./*.cpp ./*.h
time ./build.sh
./test.sh
done