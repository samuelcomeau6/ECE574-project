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
    echo "Testing hls_test$i.c $l"
    ./hlsynr ./newtest/hls_test"$i".c $l ./newtest/hls_test"$i"out.v >> $outfile
done
for i in {1..6};do
    l=${lat[$i+7]}
    echo "Testing hls_lat_test$i.c $l"
    ./hlsynr ./newtest/hls_lat_test"$i".c $l ./newtest/hls_lat_test"$i"out.v >> $outfile
done
for i in {1..4};do
    l=${lat[$i+13]}
    echo "Testing test_if$i.c $l"
    ./hlsynr ./newtest/test_if"$i".c $l ./newtest/test_if"$i"out.v >> $outfile
done
exit $fail