if ./build.sh
then
    if [ $1 = "gdb" ]
    then
        gdb -args ./hlsyn ./newtest/hls_test2.c 5 fds.v
    else
        ./hlsyn ./newtest/hls_test2.c 5 fds.v
    fi
fi