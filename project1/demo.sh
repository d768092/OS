#! /usr/bin/bash
policy=(FIFO PSJF RR SJF)
for i in $(seq 1 4)
do
	p=${policy[$i-1]}
	echo "$p"_"$i"
	sudo dmesg -c > /dev/null
	sudo ./main < OS_PJ1_Test/"$p"_"$i".txt
	echo "dmesg"
	dmesg | grep Project1
done
echo "TIME_MEASUREMENT"
sudo dmesg -c > /dev/null
sudo ./main < OS_PJ1_Test/TIME_MEASUREMENT.txt
echo "dmesg"
dmesg | grep Project1
