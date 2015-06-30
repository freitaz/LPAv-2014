#!/bin/zsh

#clear
#gcc -lpthread aula12_21200591.c -o program

echo "Calculando para matrizes 100 x 100..."
./script-matrix-100.sh  > ../matrix-logs/log-script-100.txt
echo "Calculando para matrizes 200 x 200..."
./script-matrix-200.sh  > ../matrix-logs/log-script-200.txt
echo "Calculando para matrizes 400 x 400..."
./script-matrix-400.sh  > ../matrix-logs/log-script-400.txt
echo "Calculando para matrizes 800 x 800..."
./script-matrix-800.sh  > ../matrix-logs/log-script-800.txt
echo "Calculando para matrizes 1000 x 1000..."
./script-matrix-1000.sh > ../matrix-logs/log-script-1000.txt

echo "Pronto."
