set -e
./build.sh
if [ $1 = "gdb" ]
then
    gdb -args ./hlsyn ./newtest/$2 30 fds.v
else
    if [ $1 = "sim" ]
    then
        ./hlsyn ./newtest/$2 30 ./newtest/${2/.c/.v}
        ./sim.sh ${2/.c/.v}
    fi
fi