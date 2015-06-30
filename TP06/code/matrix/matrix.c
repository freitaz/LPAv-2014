/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, parte da questão 4 - TAD para operações com matrizes - 06/06/2014
 */

#include <stdlib.h> /* malloc, free, exit */ 
#include <stdio.h> /* printf */ 
#include "matrix.h" 
 
 // Estrutura de uma matriz
struct matrix_type{ 
	int lines; 
	int columns; 
	float **grid;
	};

// Cria uma matriz, aloca espaços suficientes e retorna o endereço
matrix *create (int lines, int columns){
	int counter;
	matrix *pointer;
	pointer = (matrix*) malloc(sizeof(matrix)); 
	if (pointer == NULL){ 
		printf("Memória insuficiente\n"); 
		exit(1);
		}
	pointer->lines=lines;
	pointer->columns=columns;
	pointer->grid=(float**)malloc(sizeof(float*)*lines);
	for(counter=0;counter<lines;counter++){
		(pointer->grid)[counter]=(float*)malloc(sizeof(float)*columns);
		}
	return pointer;
	} 

// Libera as alocações de uma matriz.
void release (matrix *pointer){
	int counter;
	for (counter=0;counter<pointer->lines;counter++){
		free((pointer->grid)[counter]);
		}
	free(pointer->grid);
	free(pointer);
	} 

// Retorna um valor na posição [index_i][index_j].
void access(matrix *pointer, int index_i, int index_j, float *value){
	*value=(pointer->grid)[index_i][index_j];
	}

//Atribui na posição [index_i][index_j] um valor.
void assign(matrix *pointer, int index_i, int index_j, float value) {
	(pointer->grid)[index_i][index_j]=value;
	}

//Retorna o número de linhas da matriz.
int size_lines(matrix *pointer){
	return pointer->lines;
	}

//Retorna o número de colunas da matriz.
int size_columns(matrix *pointer){
	return pointer->columns;
	}
