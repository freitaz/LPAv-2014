/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 10/07/2014 - Aula 10: Funções recursivas, exercício 3
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

/* A lógica é simples nesse caso. Incrementa um enquanto decrementa o outro.
 * Quando um chegar a zero, o outro terá o valor da soma.
 */
int sum(int a, int b){
	if (zero(b)) return a;
	return sum(incr(a),decr(b));
	}

int main(){
	int a, b;
	printf("Digite dois números para a soma, separados por um espaço: > ");
	scanf("%d %d",&a,&b);
	printf("A soma de %d e %d é %d\n",a,b,sum(a,b));
	return 0;
	}
