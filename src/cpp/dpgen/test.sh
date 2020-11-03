if [ -n "$1" ]
then
    outfile=$1
else
    outfile=/dev/null
fi
echo > $outfile
for i in {1..6};do
    echo "Testing circuit $i"
#    rm ./test/circuit"$i".v
    ./dpgen ./test/*74a_circuit"$i".txt ./test/circuit"$i".v >> $outfile
    diff --suppress-common-lines -sy ./test/circuit"$i"out.v ./test/circuit"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        echo "Passed"
    else
        echo "...FAILED!"
    fi
done
for i in {1..3};do
    echo "Testing unsigned $i"
#    rm ./test/ucircuit"$i".v
    ./dpgen ./test/ucircuit"$i".txt ./test/ucircuit"$i".v >> $outfile
    diff --suppress-common-lines -sy ./test/ucircuit"$i"out.v ./test/ucircuit"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        echo "Passed"
    else
        echo "...FAILED!"
    fi
done
for i in {1..3};do
    echo "Testing mixed $i"
#    rm ./test/mcircuit"$i".v
    ./dpgen ./test/mixedcircuit"$i".txt ./test/mcircuit"$i".v >> $outfile
    diff --suppress-common-lines -sy ./test/mcircuit"$i"out.v ./test/mcircuit"$i".v >> $outfile
    if [ $? -eq 0 ]
    then
        echo "Passed"
    else
        echo "...FAILED!"
    fi
done
for i in {1..4};do
    echo "Testing error $i"
    ./dpgen ./test/error"$i".txt ./test/error"$i".v >> $outfile
    if [ $? -eq 1 ]
    then
        echo "Passed"
    else
        echo "...FAILED!"
    fi
done
