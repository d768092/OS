#! /usr/bin/bash
policy="FIFO PSJF RR SJF"
for p in $policy
do
	for i in $(seq 1 4)
	do
		echo "$p"_"$i"
		sudo dmesg -c > /dev/null
		./main < OS_PJ1_Test/"$p"_"$i".txt > output/"$p"_"$i"_stdout.txt
		dmesg | grep Project1  > output/"$p"_"$i"_dmesg.txt
	done
done
echo "TIME_MEASUREMENT"
sudo dmesg -c > /dev/null
./main < OS_PJ1_Test/TIME_MEASUREMENT.txt > output/TIME_MEASUREMENT_stdout.txt
dmesg | grep Project1 > output/TIME_MEASUREMENT_dmesg.txt
