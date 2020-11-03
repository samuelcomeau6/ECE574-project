for i in {1..6};do
    echo "Generating circuit $i"
    ./dpgen ./test/*74a_circuit"$i".txt ./test/circuit"$i"out.v
done
for i in {1..3};do
    echo "Generating unsigned $i"
    ./dpgen ./test/ucircuit"$i".txt ./test/ucircuit"$i"out.v
done
for i in {1..3};do
    echo "Generating mixed $i"
    ./dpgen ./test/mixedcircuit"$i".txt ./test/mcircuit"$i"out.v
done
for i in {1..4};do
    echo "Generating error $i"
    ./dpgen ./test/error"$i".txt ./test/error"$i"out.v
done
