for i in {1..6};do
    echo "Testing circuit $i"
    ./dpgen ./test/*74a_circuit"$i".txt|diff --suppress-common-lines -sy ./test/circuit"$i"out.txt -
done
for i in {1..3};do
    echo "Testing unsigned $i"
    ./dpgen ./test/ucircuit"$i".txt|diff --suppress-common-lines -sy ./test/ucircuit"$i"out.txt -
done
for i in {1..3};do
    echo "Testing mixed $i"
    ./dpgen ./test/mixedcircuit"$i".txt|diff --suppress-common-lines -sy ./test/mcircuit"$i"out.txt -
done
for i in {1..4};do
    echo "Testing error $i"
    ./dpgen ./test/error"$i".txt|diff --suppress-common-lines -sy ./test/error"$i"out.txt -
done
