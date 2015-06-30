#!/bin/zsh

#clear
#gcc -lpthread aula12_21200591.c -o program

./script-500.sh   > log-vector-500.txt
./script-1000.sh  > log-vector-1000.txt
./script-2000.sh  > log-vector-2000.txt
./script-5000.sh  > log-vector-5000.txt
./script-10000.sh > log-vector-10000.txt
./script-50000.sh > log-vector-50000.txt
