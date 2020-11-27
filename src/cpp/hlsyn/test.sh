fail=0
if [ -n "$1" ]
then
    outfile=$1
else
    outfile=/dev/null
fi
echo > $outfile
for i in {1..8};do
    echo "Testing hls_test$i.c"
    ./hlsyn ./newtest/hls_test"$i".c 40 ./newtest/hls_test"$i".v >> $outfile
    diff --suppress-common-lines -sy ./newtest/hls_test"$i"out.v ./newtest/hls_test"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        echo "Passed"
    else
        fail=1
        echo "...FAILED!"
    fi
done
for i in {1..6};do
    echo "Testing hls_lat_test$i.c"
    ./hlsyn ./newtest/hls_lat_test"$i".c 20 ./newtest/hls_lat_test"$i".v >> $outfile
    diff --suppress-common-lines -sy ./newtest/hls_lat_test"$i"out.v ./newtest/hls_lat_test"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        echo "Passed"
    else
        fail=1
        echo "...FAILED!"
    fi
done
for i in {1..4};do
    echo "Testing test_if$i.c"
    ./hlsyn ./newtest/test_if"$i".c 20 ./newtest/test_if"$i".v >> $outfile
    diff --suppress-common-lines -sy ./newtest/test_if"$i"out.v ./newtest/test_if"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        echo "Passed"
    else
        fail=1
        echo "...FAILED!"
    fi
done
for i in {1..3};do
    echo "Testing error $i"
    ./hlsyn ./newtest/error"$i".c 20 ./newtest/error"$i".v >> $outfile
    if [ $? -eq 1 ]
    then
        echo "Passed"
    else
        fail=1
        echo "...FAILED!"
    fi
done
exit $fail