#!/bin/bash

for i in 0 1 2 3; do
	g++ dgemm_opt_$i.cpp -o lab3
	if (("$i" == 2)); then
		minSpeed=999;
		blockSize=-1;
		for ((bs = 2; bs <= 2048; bs*=2));do
			res=`./lab3 1024 $bs`
			if [ 1 -eq "$(echo "${res} < ${minSpeed}" | bc)" ];then
				minSpeed=${res};
				blockSize=${bs};
			fi
		done
		echo "Размер блока с максимальным ускорением - $blockSize"
	fi
	for ((N = 100; N <= 1500; N+=100));do
		if (("$i" == 2)); then
			./lab3 $N $blockSize &> /dev/null
		else
			./lab3 $N
		fi
	done
done

for i in 0 1 2 3; do
	g++ dgemm_opt_$i.cpp -o lab3
	prom=`(perf stat -e cache-misses ./lab3 512) 2>&1 | grep "cache-misses" | awk '{print $1}'`
	echo "Количество промахов (dgemm_opt_$i) - $prom"
done

rm lab3
