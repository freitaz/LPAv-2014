/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 20/06/2014 - Aula 08: Transformação de matrizes em grafos
 */

#include <stdio.h>
#include <stdlib.h>

/* Estrutura da matriz. Serve para facilitar as operações,
 * visto que a quantidade de linhas e colunas é guardada para facilitar a checagem.
 * A estrutura foi reaproveitada parcialmente da última atividade (TP07).
 */
typedef struct{
	int lines;
	int columns;
	int **grid;
	}maze;

/* Estrutura que será a lista de adjacências.
 * O ponteiro "adjacent" guarda a lista de adjacências para um dado vértice.
 * O ponteiro "next" aponta para o próximo vértice da lista.
 */
typedef struct strc1{
	int x;
	int y;
	struct strc1 *adjacent;
	struct strc1 *next;
	}graph_list;

/* Cria uma estrutura para uma matriz e aloca posições.
 */
maze *create_grid (int lines, int columns){
	int counter;
	maze *pointer;
	pointer = (maze*) malloc(sizeof(maze)); 
	if (pointer == NULL){ 
		printf("Memória insuficiente\n"); 
		exit(1);
		}
	pointer->lines=lines;
	pointer->columns=columns;
	pointer->grid=(int**)malloc(sizeof(int*)*lines);
	for(counter=0;counter<lines;counter++){
		(pointer->grid)[counter]=(int*)malloc(sizeof(int)*columns);
		}
	return pointer;
	}

// Cria um elemento da lista encadeada para fazer parte da lista de adjacências.
graph_list *create_element(int x,int y){
	graph_list *pointer;
	pointer=(graph_list*)malloc(sizeof(graph_list));
	pointer->x=x;
	pointer->y=y;
	pointer->adjacent=NULL;
	pointer->next=NULL;
	return pointer;
	}

// Cria uma lista de adjacências para a posição (x,y) da matriz.
graph_list *adjacent_list(maze *pointer, int x, int y){
	graph_list *adjacent_pointer,*aux_pointer;
	// O elemento abaixo serve apenas como uma "head" e não tem valor real.
	adjacent_pointer=create_element(-1,-1);
	aux_pointer=adjacent_pointer;
	int index_i,index_j;
	// Os dois comandos "for" checam as vizinhanças da posição em x,y.
	for (index_i=x-1;index_i<=x+1;index_i++){
		for (index_j=y-1;index_j<=y+1;index_j++){
		/* Abaixo estão as checagens.
		 * O primeiro if verifica se os valores são menores que zero.
		 * O segundo verifica se os valores são maiores que o número de linhas/colunas.
		 * O terceiro verifica se eu estou checando a própria posição.
		 * Se essas condições são satisfeitas, é criado um elemento com a posição que
		 * foi checada, e este é inserido no final da lista.
		 */
			if ((index_i!=x)||(index_j!=y)){
				if ((0<=index_i)&&(0<=index_j)){
					if ((pointer->lines>index_i)&&(pointer->columns>index_j)){
						if (!((pointer->grid)[index_i][index_j])){
							aux_pointer->adjacent=create_element(index_i,index_j);
							aux_pointer=aux_pointer->adjacent;
							}
						}
					}
				}
			//A chave abaixo corresponde ao "for" interno.
			}
		}
	// É retornado o segundo elemento porque o primeiro é a "head" da lista.
	return adjacent_pointer->adjacent;
	}

/* Com base na matriz previamente lida, gera uma representação da matriz em
 * lista de adjacências.
 */
graph_list *convert_into_a_graph(maze *matrix){
	graph_list *graph,*aux_pointer;
	//Elemento que serve como uma "head" da lista.
	graph=create_element(-2,-2);
	aux_pointer=graph;
	int index_i,index_j;
	/* Checa a matriz inteira. Se o valor na posição (index_i,index_j)
	 * possui valor zero, então ele é interpretado como um vértice e a função
	 * busca os elementos adjacentes.
	 */
	for(index_i=0;index_i<matrix->lines;index_i++){
		for(index_j=0;index_j<matrix->columns;index_j++){
			if(!(matrix->grid)[index_i][index_j]){
				aux_pointer->next=create_element(index_i,index_j);
				aux_pointer=aux_pointer->next;
				aux_pointer->adjacent=adjacent_list(matrix,index_i,index_j);
				}
			}
		}
	// É retornado o segundo elemento porque o primeiro é a "head" da lista.
	return graph->next;
	}

// Imprime a representação do grafo em lista de adjacências.
void print_graph(graph_list *pointer){
	graph_list *aux_pointer;
	printf("Lista de adjacências:\n");
	while(pointer){
		printf("%d_%d:",pointer->x,pointer->y);
		aux_pointer=pointer->adjacent;
		while(aux_pointer){
			printf(" %d_%d",aux_pointer->x,aux_pointer->y);
			aux_pointer=aux_pointer->adjacent;
			}
		pointer=pointer->next;
		printf("\n");
		}
	printf("\n");
	}

/* A função main.
 * A função espera um único argumento de entrada, que é o nome de um arquivo.
 * A função espera que o arquivo esteja nesse formato:
 
 <número de linhas> <número de colunas>
 0  1   1   1  ... 1
 1 v21 v22 v23 ... 1
 1 v31 v32 v33 ... 1
 .  .   .   .  .   .
 .  .   .   .   .  .
 .  .   .   .    . .
 1  1   1   1  ... 0
 
 * Todos os valores são separados por tabulação.
 */
int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Número inválido de argumentos!\n");
		return 0;
		}
	int lines,columns;
	int index_i,index_j;
	int value;
	FILE *archive;
	maze *matrix_maze;
	graph_list *graph_pointer,*freedom_pointer,*auxiliary_freedom_pointer;
	archive=fopen(argv[1],"r");
	if (!archive){
		printf("Erro na abertura do arquivo!\n");
		exit(1);
		}
	fscanf(archive,"%d\t%d",&lines,&columns);
	matrix_maze = create_grid(lines,columns);
	// Atribui valores na matriz.
	for(index_i=0;index_i<lines;index_i++){
		for(index_j=0;index_j<columns;index_j++){
			fscanf(archive,"%d",&value);
			(matrix_maze->grid)[index_i][index_j]=value;
			}
		}
	/* Inicia a função que gera um grafo na representação de lista de adjacências
	 * a partir da matriz que foi lida do arquivo.
	 * O retorno é um ponteiro para a lista.
	 */
	graph_pointer=convert_into_a_graph(matrix_maze);
	if (!graph_pointer){
		printf("Nenhum caminho foi encontrado!\n");
		return 0;
		}
	print_graph(graph_pointer);
	
	// Libera as variáveis alocadas.
	for(index_i=0;index_i<lines;index_i++){
			free((matrix_maze->grid)[index_i]);
			}
	free(matrix_maze->grid);
	free(matrix_maze);
	while(graph_pointer){
		freedom_pointer=graph_pointer;
		graph_pointer=graph_pointer->next;
		while(freedom_pointer){
			auxiliary_freedom_pointer=freedom_pointer->adjacent;
			free(freedom_pointer);
			freedom_pointer=auxiliary_freedom_pointer;
			}
		}
	return 0;
	}
