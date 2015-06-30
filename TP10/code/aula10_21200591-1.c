/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 11/07/2014 - Aula 10: Funções recursivas, exercício 1
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

int main(){
	int a,b;
	printf("Digite dois números separados por um espaço: > ");
	scanf("%d %d",&a,&b);
	if (equal(a,b)) printf("Os dois números são iguais\n");
	else printf("Os dois números não são iguais\n");
	return 0;
	}
