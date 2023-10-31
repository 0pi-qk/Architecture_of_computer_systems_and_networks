#!/bin/bash

key=-o

type=(int float double)

size=1000

n=10

for k in 0 1 2; do
	for i in 0 1 2 3 4; do
		if (("$i" == 4)); then
			g++ lr2.cpp -o lab2
			./lab2 ${type[k]} $size $n none
		else
			g++ $key$i lr2.cpp -o lab2
			./lab2 ${type[k]} $size $n $key$i
		fi
	done
done
