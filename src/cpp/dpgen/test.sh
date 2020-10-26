for i in {1..3};do
    echo "Testing circuit $i"
    ./dpgen ./test/474a_circuit"$i".txt|diff --suppress-common-lines -sy ./test/circuit"$i"out.txt -
done
