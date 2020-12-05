fail=0
if [ -n "$1" ]
then
    outfile=$1
else
    outfile=/dev/null
fi
echo > $outfile
lat=(4 6 10 8 11 34 8 8 4 9 2 4 6 6 4 4 8 4)
for i in {1..8};do
    l=${lat[$i-1]}
    printf "Testing hls_test$i.c $l..........."
    ./hlsynr ./newtest/hls_test"$i".c $l ./newtest/hls_test"$i".v >> $outfile
    diff --suppress-common-lines -sy ./newtest/hls_test"$i"out.v ./newtest/hls_test"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "....FAILED!\n"
    fi
    printf "\tsimulating...\t\t"
    ./sim.sh hls_test"$i".v
    if [ $? -eq 0 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "....FAILED!\n"
    fi
done
for i in {1..6};do
    l=${lat[$i+7]}
    printf "Testing hls_lat_test$i.c $l......."
    ./hlsynr ./newtest/hls_lat_test"$i".c $l ./newtest/hls_lat_test"$i".v >> $outfile
    diff --suppress-common-lines -sy ./newtest/hls_lat_test"$i"out.v ./newtest/hls_lat_test"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "....FAILED!\n"
    fi
    printf "\tsimulating...\t\t"
    ./sim.sh hls_lat_test"$i".v
    if [ $? -eq 0 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "....FAILED!\n"
    fi
done
for i in {1..4};do
    l=${lat[$i+13]}
    printf "Testing test_if$i.c $l......."
    ./hlsynr ./newtest/test_if"$i".c $l ./newtest/test_if"$i".v >> $outfile
    diff --suppress-common-lines -sy ./newtest/test_if"$i"out.v ./newtest/test_if"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "....FAILED!\n"
    fi
    printf "\tsimulating...\t\t"
    ./sim.sh test_if"$i".v
    if [ $? -eq 0 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "....FAILED!\n"
    fi
done
for i in {1..3};do
    printf "Testing error $i\n"
    ./hlsynr ./newtest/error"$i".c 20 ./newtest/error"$i".v >> $outfile
    if [ $? -eq 1 ]
    then
        printf "Passed\n"
    else
        fail=1
        printf "\t\t\t....FAILED!\n"
    fi
done
exit $fail