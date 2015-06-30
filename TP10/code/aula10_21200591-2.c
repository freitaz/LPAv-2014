/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 10/07/2014 - Aula 10: Funções recursivas, exercício 2
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

int real_symmetric(int x,int y){
	if (zero(x)) return y;
	return real_symmetric(decr(x),decr(y));
	}
/* A função symmetric é apenas um envoltório para a função que vai computar o
 * simétrico de fato. Ela chama a função real_symmetric com dois parâmetrros e
 * o segundo é zero. A função real_symmetric decrementará ambos ao mesmo tempo,
 * então quando o primeiro elemento for zero o segundo terá o valor desejado.
 */
int symmetric(int x){
	return real_symmetric(x, 0);
	}

int main(){
	int a;
	printf("Digite um número: > ");
	scanf("%d",&a);
	printf("O simétrico de %d é %d\n",a,symmetric(a));
	return 0;
	}
