set -e
./build.sh
if [ $1 = "gdb" ]
then
    gdb -args ./hlsynd ./newtest/$2 $3 fds.v
else
    if [ $1 = "sim" ]
    then
        ./hlsynr ./newtest/$2 $3 ./newtest/${2/.c/.v}
        ./sim.sh ${2/.c/.v}
        cat ./newtest/${2/.c/.v}
    fi
fi