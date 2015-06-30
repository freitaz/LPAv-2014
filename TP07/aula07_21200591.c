/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 13/06/2014 - Aula 07: Backtracking e busca - O labirinto do rato
 */

#include <stdio.h>
#include <stdlib.h>

/* Estrutura para uma posição da matriz que representa
 * o labirinto. O campo "flag_is_used" serve como um auxílio para o backtrack.
 */
typedef struct{
	short int value;
	short int flag_is_used;
	}maze_element;

/* Estrutura da matriz inteira. Serve para facilitar as operações,
 * visto que a quantidade de linhas e colunas é guardada para facilitar a checagem.
 */
typedef struct{
	int lines;
	int columns;
	maze_element **grid;
	}maze;

/* Uma lista encadeada simples para armazenar as coordenadas do caminho que
 * foi percorrido. É usada para imprimir o caminho e uma representação
 * visual da matriz.
 */
typedef struct strc1{
	int line_value;
	int column_value;
	struct strc1 *next;
	}path_list;

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
	pointer->grid=(maze_element**)malloc(sizeof(maze_element*)*lines);
	for(counter=0;counter<lines;counter++){
		(pointer->grid)[counter]=(maze_element*)malloc(sizeof(maze)*columns);
		}
	return pointer;
	}

// Cria um elemento da lista encadeada para a rota.
path_list *create_route(int x,int y){
	path_list *pointer;
	pointer=(path_list*)malloc(sizeof(path_list));
	pointer->line_value=x;
	pointer->column_value=y;
	pointer->next=NULL;
	return pointer;
	}

// A função que vai varrer o labirinto em busca da rota.
path_list *find_maze_exit(maze *pointer, maze_element **matrix, int x_position, int y_position){
	path_list *route;
	route=create_route(x_position,y_position);
	
	//Retorna NULL se eu saí dos limites da matriz.
	if (x_position<0 || y_position<0 || x_position>(pointer->lines) || y_position>(pointer->columns)) return NULL;
	
	//Retorna o último elemento da rota se eu cheguei no extremo final do labirinto.
	if ((x_position+1==pointer->lines)&&(y_position+1==pointer->columns)) return route;
	
	//Retorna NULL se há barreira ou se essa posição já foi olhada.
	if (((matrix[x_position][y_position]).value)||((matrix[x_position][y_position]).flag_is_used)) return NULL;
	
	//Sinaliza que a posição atual já foi visitada.
	(matrix[x_position][y_position]).flag_is_used=1;
	
	//Checagem ao sul.
	route->next=find_maze_exit(pointer,matrix,x_position+1,y_position);
	if (route->next) return route;

	//Checagem ao leste.
	route->next=find_maze_exit(pointer,matrix,x_position,y_position+1);
	if (route->next) return route;
	
	//Checagem ao sudeste.
	route->next=find_maze_exit(pointer,matrix,x_position+1,y_position+1);
	if (route->next) return route;

	//Checagem ao sudoeste.
	route->next=find_maze_exit(pointer,matrix,x_position-1,y_position+1);
	if (route->next) return route;

	//Checagem ao oeste.
	route->next=find_maze_exit(pointer,matrix,x_position-1,y_position);
	if (route->next) return route;

	//Checagem ao nordeste.
	route->next=find_maze_exit(pointer,matrix,x_position+1,y_position-1);
	if (route->next) return route;

	//Checagem ao noroeste.
	route->next=find_maze_exit(pointer,matrix,x_position-1,y_position-1);
	if (route->next) return route;

	//Checagem ao norte.
	route->next=find_maze_exit(pointer,matrix,x_position-1,y_position);
	if (route->next) return route;
	
	/* Nenhuma alternativa era válida.
	 * É retornado um NULL para a chamada anterior.
	 */
	return NULL;
	}

// Imprime o caminho que foi percorrido.
void print_path(path_list *pointer){
	printf("Caminho seguido:\n");
	printf("Início -> ");
	while (pointer){
		printf("(%d,%d) -> ",pointer->line_value,pointer->column_value);
		pointer=pointer->next;
		}
	printf("Fim\n\n");
	}

//Imprime uma representação visual da matriz.
void print_matrix(path_list *path, maze *matrix){
	printf("Representação do labirinto:\n");
	int index_i,index_j;
	path_list *tmp;
	tmp=path;
	while(tmp){
		((matrix->grid)[tmp->line_value][tmp->column_value]).flag_is_used=2;
		tmp=tmp->next;
		}
	for(index_i=0;index_i<matrix->lines;index_i++){
		for(index_j=0;index_j<matrix->columns;index_j++){
			if (((matrix->grid)[index_i][index_j]).value) printf("##");
			else{
				if (((matrix->grid)[index_i][index_j]).flag_is_used==2) printf("**");
				else printf("  ");
				}
			}
		printf("\n");
		}
	printf("\n");
	printf("# = barreira, ' ' (espaço) = passagem, * = caminho seguido\n\n");
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
	path_list *path_pointer,*freedom_pointer;
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
			(matrix_maze->grid)[index_i][index_j].value=value;
			}
		}
	/* Inicia a função de backtrack na posição inicial da matriz.
	 * O retorno da função é um ponteiro para a rota completa
	 * desde a entrada até a saída do labirinto, ou NULL se
	 * nenhuma saída foi encontrada.
	 */
	path_pointer=find_maze_exit(matrix_maze,(*matrix_maze).grid,0,0);
	if (!path_pointer){
		printf("Nenhum caminho foi encontrado!\n");
		return 0;
		}
	printf("Um caminho foi encontrado!\n");
	print_path(path_pointer);
	print_matrix(path_pointer,matrix_maze);
	return 0;
	// Libera as variáveis alocadas.
	for(index_i=0;index_i<lines;index_i++){
			free((matrix_maze->grid)[index_i]);
			}
	free(matrix_maze->grid);
	free(matrix_maze);
	while(path_pointer){
		freedom_pointer=path_pointer->next;
		free(path_pointer);
		path_pointer=freedom_pointer;
		}
	}
	
