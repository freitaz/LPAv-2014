/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 10/07/2014 - Aula 10: Funções recursivas, exercício 4
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

int sum(int a, int b){
	if (zero(b)) return a;
	return sum(incr(a),decr(b));
	}

int real_multiplier(int a, int b, int c){
	if (zero(b)) return a;
	return real_multiplier(sum(a,c),decr(b),c);
	}

/* Assim como no exercício dois com a função symmetric, a função multiplier
 * é apenas um envoltório para a função que faz o cálculo de fato. A função
 * real_multiplier utiliza três parâmetros: o primeiro é o número acumulador da
 * soma, o segundo é o multiplicador (quantas vezes eu devo realizar a soma) e
 * o terceiro é o valor que deve ser somado a cada chamada da função, tanto é
 * que o terceiro parâmetro é constante através das chamadas recursivas.
 */
int multiplier(int a, int b){
	return real_multiplier(0, b, a);
	}

int main(){
	int a, b;
	printf("Digite dois números para multiplicação, separados por espaços: > ");
	scanf("%d %d",&a,&b);
	printf("O produto entre %d e %d é %d\n",a,b,multiplier(a,b));
	return 0;
	}
