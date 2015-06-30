/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 2 - definir o header do TAD para pontos no R3 - 06/06/2014
 */

/* TAD: Ponto polar(module,argument) */ 
 
/*----------------*/ 
/* Tipo exportado */ 
/*----------------*/ 
typedef struct ponto_r3 ponto; 

/*--------------------*/ 
/* Funcoes exportadas */ 
/*--------------------*/ 
 
/* Funcao cria 
** Aloca e retorna um ponto com módulo module e ângulo argument 

*/ 
ponto *create (float x, float y, float z); 
 
/* Funcao libera 
** Libera a memoria de um ponto previamente criado. 
*/ 
void release (ponto *p); 
 
/* Funcao acessa 
** Devolve os valores das coordenadas de um ponto 
*/ 
void access (ponto *p, float *x, float *y, float *z); 
 
/* Funcao atribui 
** Atribui novos valores as coordenadas de um ponto 
*/ 
void assign (ponto *p, float x, float y, float z); 
 
/* Funcao distancia 
** Retorna a distancia entre dois pontos 
*/ 
float distance (ponto *p1, ponto *p2);
