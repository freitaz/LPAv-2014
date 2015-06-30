/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 10/07/2014 - Aula 10: Funções recursivas, exercício 6
 */

#include<stdio.h>

int zero(int x){
	return (x==0);
	}

int decr(int x){
	return (--x);
	}

int incr(int x){
	return (++x);
	}

int equal(int x, int y){
	if (zero(x) && zero(y)) return 1;
	if (zero(x)) return 0;
	if (zero(y)) return 0;
	return equal(decr(x),decr(y));
	}

int sum(int a, int b){
	if (zero(b)) return a;
	return sum(incr(a),decr(b));
	}

int real_multiplier(int a, int b, int c){
	if (zero(b)) return a;
	return real_multiplier(sum(a,c),decr(b),c);
	}

int multiplier(int a, int b){
	return real_multiplier(0, b, a);
	}

/* Na função sequence, as variáveis x e y foram introduzidas com o único propósito
 * de melhorar a legibilidade do código. Elas poderiam ser omitidas sem prejuízo
 * de execução, mas colocar os comandos na linha de retorno tornaria a linha extensa
 * e talvez um pouco mais complexa de entender. Portanto, optei por deixar o cálculo
 * dos termos em linhas separadas e depois somar o resultado acumulado.
 */
int sequence(int n){
	int x,y;
	if (equal(n,1)) return 1;
	if (equal(n,2)) return 2;
	x = multiplier(2,sequence(decr(n)));
	y = multiplier(3,sequence(decr(decr(n))));
	return sum(x,y);
	}

int main(){
	int a;
	printf("Digite um número para o cálculo da sequência: > ");
	scanf("%d",&a);
	printf("O valor da sequência na posição %d é %d\n",a,sequence(a));
	return 0;
	}
