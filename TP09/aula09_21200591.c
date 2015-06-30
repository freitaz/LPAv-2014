/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 27/06/2014 - Aula 09: Transformação de matrizes em grafos e DFS
 */

#include <stdio.h>
#include <stdlib.h>

/* Estrutura que será utilizada para a lista de adjacências.
 * O ponteiro "node" aponta para um vértice do grafo.
 * O ponteiro "next" aponta para a próxima posição da lista.
 */
typedef struct strc1{
	struct strc2 *node;
	struct strc1 *next;
	} node_list;

/* Estrutura que será usada para armazenar a lista de vértices.
 * O campo "mark" é um sinalizador para indicar se esse vértice já foi visitado.
 * As variáveis x e y indicam as coordenadas do ponto, da esquerda para a direita
 * e de cima para baixo.
 * O ponteiro "adjacent" aponta para a lista de adjacências do vértice.
 */
typedef struct strc2{
	int x;
	int y;
	short int mark;
	node_list *adjacent;
	struct strc2 *next;
	} graph_list;

/* A estrutura que armazena os dados lidos do arquivo.
 * Ela foi reaproveitada da atividade 8.
 */
typedef struct{
	int lines;
	int columns;
	short int **grid;
	}maze;

/* Função que cria a estrutura "maze" para armazenar os dados lidos do arquivo.
 */
maze *create_grid(int lines,int columns){
	int counter;
	maze *pointer;
	pointer = (maze*) malloc(sizeof(maze));
	if (!pointer){
		printf("Memória insuficiente\n");
		exit(1);
		}
	pointer->lines=lines;
	pointer->columns=columns;
	pointer->grid=(short int**)malloc(sizeof(short int*)*lines);
	for (counter=0;counter<lines;counter++){
		(pointer->grid)[counter]=(short int*)malloc(sizeof(short int)*columns);
		}
	return pointer;
	}

/* Função que cria um elemento do tipo "node_list".
 * A função aloca uma variável e atribui NULL aos ponteiro "next",
 * além de vincular um vértice.
 */
node_list *create_nodelist_element(graph_list *node){
	node_list *pointer;
	pointer=(node_list*)malloc(sizeof(node_list));
	pointer->node = node;
	pointer->next=NULL;
	return pointer;
	}

/* Função que cria um elemento do tipo "graph_list".
 * A função atribui as coordenadas de um vértice e NULL aos ponteiros.
 * Adicionalmente, inicializa "mark" com 0.
 */
graph_list *create_node_element(int x, int y){	
	graph_list *pointer;
	pointer=(graph_list*)malloc(sizeof(graph_list));
	pointer->x=x;
	pointer->y=y;
	pointer->adjacent=NULL;
	pointer->next=NULL;
	pointer->mark=0;
	return pointer;
	}

/* Função que cria uma lista de adjacências para os elementos do grafo.
 * A função percorre todo o grafo para criar a lista de adjacências para os vértices.
 */
void *create_adjacent_list(graph_list *graph, int lines, int columns){
	node_list *pointer_list, *aux_pointer_list;
	graph_list *pointer,*aux_pointer;
	pointer=graph;
	int index_i,index_j;
	// "pointer_list" será usado como um HEAD para a lista de fato.
	pointer_list=create_nodelist_element(NULL);
	aux_pointer_list=pointer_list;
	// "pointer" aponta para uma lista de vértices. A lista é percorrida até o fim.
	while(pointer){
	// Os dois "for" são usados para buscar os elementos adjacentes.	
		for (index_i=pointer->x-1;index_i<=pointer->x+1;index_i++){
			for(index_j=pointer->y-1;index_j<=pointer->y+1;index_j++){
/* As condições de checagem abaixo (os três "if") eram utilizadas na atividade 8.
 * Eram usadas com o propósito de evitar acessos à posições indevidas de memória,
 * i.e. fora da matriz que representa o labirinto.
 * Essa checagem poderia ser dispensada no código, mas foi mantida para economizar algumas
 * buscas desnecessárias.
 * Na verdade, enquanto escrevia me dei conta que provavelmente isso gera mais
 * overhead do que benefício; no entanto a verificação será mantida.
 * Adicionalmente, o primeiro "if" é estritamente necessário para que um vértice não
 * seja adicionado como seu próprio vizinho.
 */
				if ((index_i!=pointer->x)||(index_j!=pointer->y)){
				if ((0<=index_i)&&(0<=index_j)){
				if ((lines>index_i)&&(columns>index_j)){
					aux_pointer=graph;
					while(aux_pointer){
						if ((aux_pointer->x==index_i)&&(aux_pointer->y==index_j)){
/* Se corresponde ao índice que eu procuro, adiciono na lista de adjacentes.
 * O ponteiro que aponta para a lista completa dos vértices recebe NULL para interromper
 * a busca. A lista não é perdida, pois há outro ponteiro que aponta para ela.
 */
							aux_pointer_list->next=create_nodelist_element(aux_pointer);							
							aux_pointer_list=aux_pointer_list->next;
							aux_pointer=NULL;
							}
						if(aux_pointer) aux_pointer=aux_pointer->next;
						}
				}
				}
				}
				}
			}
		//Passo para o próximo vértice, e continuo o procedimento...
		pointer->adjacent=pointer_list->next;
		pointer=pointer->next;
		aux_pointer_list=pointer_list;
		}
	}

/* Diferentemente da função homônima existente na atividade 8, essa função apenas
 * gera uma lista de vértices com base no labirinto. Posteriormente são adicionados
 * os vértices.
 * A separação foi feita porque adicionar os adjacentes no momento da leitura de um
 * vértice requer endereços de memória inexistentes no momento da leitura. A opção
 * foi adicionar os adjacentes depois.
 */
graph_list *convert_into_a_graph(maze *matrix){
	graph_list *graph,*aux_pointer;
	// "graph" é usado como um HEAD para a lista que contém os vértices de fato.
	graph=create_node_element(-2,-2);
	aux_pointer=graph;
	int index_i,index_j;
	for(index_i=0;index_i<matrix->lines;index_i++){
		for(index_j=0;index_j<matrix->columns;index_j++){
			if(!(matrix->grid)[index_i][index_j]){
				aux_pointer->next=create_node_element(index_i,index_j);
				aux_pointer=aux_pointer->next;
				}
			}
		}
	return graph->next;
	}

/* A função que percorre o grafo com DFS.
 * Ela retorna um ponteiro para um node_list; esse ponteiro aponta para uma lista
 * que corresponde ao caminho percorrido.
 * x_final e y_final são usados para saber quando eu cheguei ao final do grafo;
 * opcionalmente a variável "mark" poderia receber um valor diferenciado no último
 * vértice no momento da leitura - essa foi uma ideia que eu tive após o código
 * estar concluído.
 */
node_list *find_a_path_with_DFS(graph_list *node,int x_final,int y_final){
	node_list *pointer;
	//Caso base 1: se eu já visitei, retorno NULL.
	if(node->mark){
		return NULL;
		}
	// Caso base 2: se as coordenadas batem com o final, retorna o endereço do vértice.
	if ((node->x==x_final)&&(node->y==y_final)){
		pointer=create_nodelist_element(node);
		return pointer;
		}
	// Sinaliza que eu visitei o vértice.
	node->mark=1;
	node_list *adjacent_list,*return_pointer;
	adjacent_list=node->adjacent;
	while(adjacent_list){
	//Percorre a lista dos adjacentes e chama o DFS para cada um deles.
		pointer=find_a_path_with_DFS(adjacent_list->node,x_final,y_final);
		if (pointer){
	//Se o retorno não é NULL, insiro o endereço em uma lista e retorno a lista.
			return_pointer=create_nodelist_element(node);
			return_pointer->next=pointer;
			return return_pointer;
			}
		adjacent_list=adjacent_list->next;
		}
	// Não achei nada, então retorna NULL.
	return NULL;
	}

// Função simples que imprime o caminho no formato desejado.
void print_path(node_list *path){
	while(path){
		printf("L(%d,%d)\n",path->node->x,path->node->y);
		path=path->next;
		}
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
	if(argc!=2){
		printf("Número inválido de argumentos\n");
		return 0;
		}
	int lines,columns;
	int index_i,index_j;
	int value;
	FILE *archive;
	graph_list *graph_pointer,*freedom_pointer;
	node_list *the_path,*path_freedom_pointer;
	maze *matrix;
	archive=fopen(argv[1],"r");
	if (!archive){
		printf("Erro na abertura do arquivo\n");
		return 0;
		}
	fscanf(archive,"%d\t%d",&lines,&columns);
	matrix=create_grid(lines,columns);
	for(index_i=0;index_i<lines;index_i++){
		for(index_j=0;index_j<columns;index_j++){
			fscanf(archive,"%d",&value);
			(matrix->grid)[index_i][index_j]=value;
			}
		}
	graph_pointer=convert_into_a_graph(matrix);
	create_adjacent_list(graph_pointer,lines,columns);
	// é passado lines-1 e columns-1 para o DFS conseguir encontrar o fim.
	the_path=find_a_path_with_DFS(graph_pointer,lines-1,columns-1);
	// Se há caminho, imprime o caminho; senão imprime que não há caminho.
	if (the_path) print_path(the_path);
	else printf("Nenhum caminho foi encontrado\n");
	//Libera todas as variáveis alocadas.
	for(index_i=0;index_i<lines;index_i++){
			free((matrix->grid)[index_i]);
			}
	free(matrix->grid);
	free(matrix);
	while(graph_pointer){
		freedom_pointer=graph_pointer->next;
		free(graph_pointer);
		graph_pointer=freedom_pointer;
		}
	while(the_path){
		path_freedom_pointer=the_path->next;
		free(the_path);
		the_path=path_freedom_pointer;
		}
	return 0;
	}
