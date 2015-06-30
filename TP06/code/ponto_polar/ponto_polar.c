/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 1 - TAD para pontos em coordenadas polares - 06/06/2014
 */

#include <stdlib.h> /* malloc, free, exit */ 
#include <stdio.h> /* printf */ 
#include <math.h> /* sqrt */ 
#include "ponto_polar.h" 
 
// Estrutura de um ponto em coordenadas polares
struct ponto_polar { 
	float module; 
	float argument; 
	};

// Cria uma variável, aloca os valores e retorna o endereço
ponto *create (float module, float argument){ 
	ponto* p = (ponto*) malloc(sizeof(ponto)); 
	if (p == NULL){ 
		printf("Memória insuficiente\n"); 
		exit(1);
		} 
	p->module = module;
	p->argument = argument; 
	return p;
	} 

//Libera um ponto previamente alocado. 
void release (ponto *p){
	free(p);
	}

//Acessa o valor de um ponto previamente alocado.
void access(ponto *p, float *module, float *argument){ 
	*module = p->module;
	*argument = p->argument;
	}

//Atribui um valor para um ponto previamente alocado.
void assign(ponto *p, float module, float argument) {
	p->module = module; 
	p->argument =argument;
	}

/* Calcula a distância entre dois pontos com coordenadas polares,
 * através do método de obtenção das coordenadas euclidianas
 * com base no módulo e no argumento do número.
 */
float distance(ponto *p1, ponto *p2){ 
	float x1,x2,y1,y2;
	x1 = (p1->module)*cos(((p1->argument)*M_PI)/180);
	x2 = (p2->module)*cos(((p2->argument)*M_PI)/180);
	y1 = (p1->module)*sin(((p1->argument)*M_PI)/180);
	y2 = (p2->module)*sin(((p2->argument)*M_PI)/180);
	return sqrt(powf(x1-x2,2)+powf(y1-y2,2));
	}
