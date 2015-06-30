----- Informações gerais sobre o código -----


>> Sobre o código

O código para o trabalho 12 de LPAv foi feito em ambiente Linux, portanto não se
sabe se ele funciona em ambiente Windows.

>> Instruções de compilação

Seja "threads.c" o nome do código fonte. A linha de comando do gcc deverá seguir
o exemplo abaixo:

gcc -lpthread threads.c -o program

"program" é o nome do arquivo de saída. Pode ser inserido qualquer nome aqui.

>> Instruções de execução

Seja "program" o nome do arquivo executável. Para a execução, a linha de comando
deverá se assemelhar ao seguinte:

./program <tamanho do vetor> <número de threads>

Por exemplo: ./program 5000 20

É desejável criar um script para a automatização de testes em um mesmo grupo de
números (i.e. todos os testes com um vetor de 5000 posições).

>> Descrição da solução proposta

A função que realiza a soma trabalha com dois mutexes: um que gerencia o tamanho
do vetor e outro que gerencia operações no vetor. A cada interação, a última
posição do vetor é somada com a primeira posição e o resultado é armazenado de
volta na primeira posição. A função continua até que o tamanho do vetor seja 1.
Após o processamento, a primeira posição do vetor conterá a soma de todos os
elementos deste.
