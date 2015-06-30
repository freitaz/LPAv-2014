/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 10/07/2014 - Aula 10: Funções recursivas, exercício 5
 */

#include<stdio.h>

int zero(int x){
	return (x==0);
	}

int decr(int x){
	return (--x);
	}

float incr(float x){
	return (++x);
	}

int equal(int x, int y){
	if (zero(x) && zero(y)) return 1;
	if (zero(x)) return 0;
	if (zero(y)) return 0;
	return equal(decr(x),decr(y));
	}

float somatorio(int a){
	if (equal(a,1)) return 1.0;
	return (1.0/(float)a)+somatorio(decr(a));
	}

int main(){
	int a;
	printf("Digite número para o cálculo do somatório: > ");
	scanf("%d",&a);
	printf("O valor do somatório é %f\n",somatorio(a));
	return 0;
	}
	
