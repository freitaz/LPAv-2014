/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 2 - definir TAD para pontos no R3 - 06/06/2014
 */

#include <stdlib.h> /* malloc, free, exit */ 
#include <stdio.h> /* printf */ 
#include <math.h> /* sqrt, powf */ 
#include "ponto_r3.h" 
 
// Estrutura de um ponto em coordenadas polares
struct ponto_r3{ 
	float x; 
	float y; 
	float z;
	};

// Cria uma variável, aloca os valores e retorna o endereço
ponto *create (float x, float y, float z){ 
	ponto* p = (ponto*) malloc(sizeof(ponto)); 
	if (p == NULL){ 
		printf("Memória insuficiente\n"); 
		exit(1);
		} 
	p->x = x;
	p->y = y;
	p->z = z;
	return p;
	} 

//Libera uma variável previamente alocada. 
void release (ponto *p){
	free(p);
	}

//Acessa o valor de uma variável.
void access(ponto *p, float *x, float *y, float *z){ 
	*x = p->x;
	*y = p->y;
	*z = p->z;
	}

//Atribui valor para uma variável.
void assign(ponto *p, float x, float y, float z) {
	p->x = x; 
	p->y = y;
	p->z = z;
	}
 
//Calcula a distância entre dois pontos.
float distance(ponto *p1, ponto *p2){ 
	return sqrt(powf((p1->x)-(p2->x),2)+powf((p1->y)-(p2->y),2)+powf((p1->z)-(p2->z),2));
	}
