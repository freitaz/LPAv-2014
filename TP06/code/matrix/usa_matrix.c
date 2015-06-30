/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * Aula 06, questão 04 - transposição de matriz - 06/06/2014
 */

#include<stdio.h>
#include"matrix.h"

// Função para transpôr uma matriz.
matrix *transpose_matrix(matrix *pointer){
	int lines,columns,index_i,index_j;
	float value;
	matrix *transposed_matrix;
	lines=size_lines(pointer);
	columns=size_columns(pointer);
	transposed_matrix=create(columns,lines);
	for(index_i=0;index_i<lines;index_i++){
		for(index_j=0;index_j<columns;index_j++){
			access(pointer,index_i,index_j,&value);
			assign(transposed_matrix,index_j,index_i,value);
			}
		}
	return transposed_matrix;
	}

// Função para imprimir uma matriz.
void print_matrix(matrix *pointer){
	int lines,columns,index_i,index_j;
	float value;
	lines=size_lines(pointer);
	columns=size_columns(pointer);
	printf(" *\t");
	for(index_i=0;index_i<columns;index_i++) printf("%d\t",index_i+1);
	printf("\n");
	for(index_i=0;index_i<lines;index_i++){
		printf(" %d\t",index_i+1);
		for(index_j=0;index_j<columns;index_j++){
			access(pointer,index_i,index_j,&value);
			printf("%3.2f\t",value);
			}
			printf("\n");
		}
	printf("\n");
	}

/* Função main.
 * A função espera um único argumento.
 * O argumento deve ser o nome de um arquivo no seguinte formato:
 
 num_linhas num_colunas
 a11 a12 a13 ... a1n
 a21 a22 a23 ... a2n
  .   .   .  .    .
  .   .   .   .   .
  .   .   .    .  .
 am1 am2 am3 ... amn
 
 * Os termos são separados por espaços.
 * num_linhas e num_colunas DEVEM ser inteiros.
 * Os termos podem ser em ponto flutuante.
 */
int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Número inválido de argumentos!\n");
		return 0;
		}
	int lines,columns;
	int index_i,index_j;
	float value;
	FILE *archive;
	archive=fopen(argv[1],"r");
	fscanf(archive,"%d %d",&lines,&columns);
	matrix *pointer_matrix,*transposed_matrix;	
	pointer_matrix = create(lines,columns);
	// Atribui valores na matriz.
	for(index_i=0;index_i<lines;index_i++){
		for(index_j=0;index_j<columns;index_j++){
			fscanf(archive,"%f ",&value);
			assign(pointer_matrix,index_i,index_j,value);
			}
		}
	printf("A matriz possui %d linhas e %d colunas.\nElementos:\n\n",lines,columns);
	//Imprime a matriz original, antes de realizar a transposição.
	print_matrix(pointer_matrix);
	transposed_matrix=transpose_matrix(pointer_matrix);
	lines=size_lines(transposed_matrix);
	columns=size_columns(transposed_matrix);
	printf("A matriz transposta possui %d linhas e %d colunas.\nElementos:\n\n",lines,columns);
	// Imprime a matriz transposta.
	print_matrix(transposed_matrix);
	release(transposed_matrix);
	release(pointer_matrix);
	return 0;
	}
