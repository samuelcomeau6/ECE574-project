#/bin/bash
while true
do
    inotifywait -emodify ./*.cpp ./*.h
    time ./build.sh
    if [ $? = 0 ]
    then
        ./test.sh
    fi
done