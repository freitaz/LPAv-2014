/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 2 - código que utiliza o TAD implementado - 06/06/2014
 */

#include<stdio.h>
#include"ponto_r3.h"

int main(){
	ponto *p1,*p2;
	float x,y,z,distance_value;
	p1=create(0,0,0);
	p2=create(0,0,0);
	printf("Digite coordenadas x, y e z do ponto 1, separadas por espaços: > ");
	scanf("%f %f %f",&x,&y,&z);
	assign(p1,x,y,z);
	printf("Digite coordenadas x, y e z do ponto 2, separadas por espaços: > ");
	scanf("%f %f %f",&x,&y,&z);
	assign(p2,x,y,z);
	x=0;
	y=0;
	z=0;
	access(p1,&x,&y,&z);
	printf("As coordenadas do ponto 1 são (%.2f, %.2f, %.2f).\n",x,y,z);
	access(p2,&x,&y,&z);
	printf("As coordenadas do ponto 2 são (%.2f, %.2f, %.2f).\n",x,y,z);
	distance_value=distance(p1,p2);
	printf("A distância entre os dois pontos inseridos é de %.3f unidades\n",distance_value);
	release(p1);
	release(p2);
	return 0;
	}
