/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 */

/* Aula 06, questão 3 - header da TAD para uma matriz - 06/06/2014
/* TAD: matrix(linhas,colunas) */ 
 
/*----------------*/ 
/* Tipo exportado */ 
/*----------------*/ 
typedef struct matrix_type matrix; 

/*--------------------*/ 
/* Funcoes exportadas */ 
/*--------------------*/ 
 
/* Funcao cria 
** Aloca e retorna um ponteiro para uma estrutura matrix de ordem lines x columns 

*/
matrix *create(int lines,int columns);
 
/* Funcao libera 
** Libera a memoria de uma matriz.
*/ 
void release (matrix *pointer);
 
/* Funcao acessa 
** Devolve os valores de uma posição da matriz. 
*/ 
void access (matrix *pointer, int index_i, int index_j, float *value);
 
/* Funcao atribui 
** Atribui novos valores para uma posição de uma matriz.
*/ 
void assign (matrix *pointer, int index_i, int index_j, float value); 
 
/* Funcao size_lines
** Retorna a quantidade de linhas na matriz. 
*/ 
int size_lines(matrix *pointer);

/* Funcao size_columns
** Retorna a quantidade de colunas na matriz.
*/

int size_columns(matrix *pointer);
