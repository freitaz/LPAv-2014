/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 1 - header do TAD para pontos em coordenadas polares - 06/06/2014
 */

/* TAD: Ponto polar(module,argument) */ 
 
/*----------------*/ 
/* Tipo exportado */ 
/*----------------*/ 
typedef struct ponto_polar ponto; 

/*--------------------*/ 
/* Funcoes exportadas */ 
/*--------------------*/ 
 
/* Funcao cria 
** Aloca e retorna um ponto com módulo module e ângulo argument 

*/ 
ponto *create (float module, float argument); 
 
/* Funcao libera 
** Libera a memoria de um ponto previamente criado. 
*/ 
void release (ponto *p); 
 
/* Funcao acessa 
** Devolve os valores das coordenadas de um ponto 
*/ 
void access (ponto *p, float *module, float *argument); 
 
/* Funcao atribui 
** Atribui novos valores as coordenadas de um ponto 
*/ 
void assign (ponto *p, float module, float argument); 
 
/* Funcao distancia 
** Retorna a distancia entre dois pontos 
*/ 
float distance (ponto *p1, ponto *p2);
