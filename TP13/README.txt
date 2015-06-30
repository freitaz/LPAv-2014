----- Informações gerais sobre os códigos -----

>> Sobre os códigos

O códigos para o trabalho 13 de LPAv foram feitos em ambiente Linux, portanto não se
sabe se eles funcionam em ambiente Windows.

>> Instruções de compilação

Seja "threads.c" o nome do código fonte. A linha de comando do gcc deverá seguir
o exemplo abaixo:

gcc -lpthread threads.c -o program

"program" é o nome do arquivo de saída. Pode ser inserido qualquer nome aqui.

>> Instruções de execução

Seja "program" o nome do arquivo executável. Para a execução do programa 1 (que opera
com vetores), a linha de comando deverá se assemelhar ao seguinte:

./program <tamanho do vetor> <número de threads>

Para a execução do programa 2 (multiplicação de matrizes), a linha de comando deverá se
assemelhar ao seguinte:

./program <ordem do vetor> <número de threads>

Isto é, se o primeiro parâmetro é 800, então as matrizes terão tamanho 800 x 800.

Exemplo típico de execução: ./program 5000 20
Para o primeiro programa, 5000 é o tamanho do vetor.
Para o segundo programa, 5000 é a ordem da matriz (5000 x 5000).

É desejável criar um script para a automatização de testes em um mesmo grupo de
números (i.e. todos os testes com um vetor de 5000 posições).

>> Descrição da solução proposta

A função que realiza a soma de um vetor trabalha em conjunto com uma estrutura que
define o intervalo de soma de cada thread, de modo que mutexes podem ser dispensados
seguramente. Cada thread calcula o resultado do seu intervalo e no final a main soma
os resultados.

De maneira similar, a função que multiplica matrizes trabalha em conjunto com uma
estrutura similar que define intervalos de multiplicações e uma função que calcula
uma posição da matriz resultado e faz a multiplicação de uma determinada linha por
uma determinada coluna. De maneira similar à ideia do vetor, mutexes são dispensados,
e as threads colocam os resultados de multiplicações de linhas por colunas já em sua
posição final.
