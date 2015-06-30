/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 1 - Código que utiliza o TAD implementado - 06/06/2014
 */

#include<stdio.h>
#include"ponto_polar.h"

int main(){
	ponto *p1,*p2;
	float arg1,arg2,mod1,mod2,distance_value;
	printf("Digite módulo e argumento em graus do ponto 1, separados por espaços: > ");
	scanf("%f %f",&mod1,&arg1);
	printf("Digite módulo e argumento em graus do ponto 2, separados por espaços: > ");
	scanf("%f %f",&mod2,&arg2);
	p1=create(mod1,arg1);
	p2=create(mod2,arg2);
	arg1=0;
	arg2=0;
	mod1=0;
	mod2=0;
	access(p1,&mod1,&arg1);
	access(p2,&mod2,&arg2);
	printf("O módulo do ponto 1 é %.2f e o valor do ângulo é %.2f graus\n",mod1,arg1);
	printf("O módulo do ponto 2 é %.2f e o valor do ângulo é %.2f graus\n",mod2,arg2);
	distance_value=distance(p1,p2);
	printf("A distância entre os dois pontos inseridos é de %.3f unidades\n",distance_value);
	release(p1);
	release(p2);
	return 0;
	}
