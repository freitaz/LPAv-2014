#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Laboratório de Programação Avançada - LPAV
 * Aluno: Luan de Freitas Uchôa - 21200591
 * Aula 04 - Grafos - 23/05/2014
 */


//A estrutura do grafo.
typedef struct strc1{
	int id;
	double x_position;
	double y_position;
	// Este é um ponteiro para a lista de adjacências.
	struct strc2 *neighbours;
	}node;

// A estrutura da lista de adjacências.
typedef struct strc2{
	int id;
	struct strc2 *next;
	}neighbour_list;

//Cria um grafo e inicializa os ponteiros com NULL.
node *create_graph(int size){
	node *graph_pointer;
	int counter;
	graph_pointer=(node*)malloc(sizeof(node)*size);
	for(counter=0;counter<size;counter++){
		(graph_pointer+counter)->neighbours=NULL;
		}
	return graph_pointer;
	}

// Calcula a distância entre dois nós.
double calc_distance(node *first_node, node *second_node){
	double x_param= (first_node->x_position)-(second_node->x_position);
	double y_param= (first_node->y_position)-(second_node->y_position);
	if (x_param<0) x_param=x_param*-1;
	if (y_param<0) y_param=y_param*-1;
	return sqrt((pow(x_param,2))+(pow(y_param,2)));
	}

// Adiciona uma ID à lista de adjacências.
bool add_neighbour(int id_number, node *element){
	neighbour_list *pointer;
	if (!(element->neighbours)){
		element->neighbours=(neighbour_list*)malloc(sizeof(neighbour_list));
		element->neighbours->id=id_number;
		element->neighbours->next=NULL;
		}
	else{
		pointer=element->neighbours;
		while ((pointer->next))	pointer=pointer->next;
		pointer->next=(neighbour_list*)malloc(sizeof(neighbour_list));
		pointer->next->id=id_number;
		pointer->next->next=NULL;
		}
	return true;
	}

// Calcula a distância entre os nós e armazena na lista de adjacências, se necessário.
void update_graph_neighbours(int size, double radius, node *graph){
	int first_counter, second_counter;
	double distance;
	first_counter=0;
	second_counter=1;
	while (first_counter<(size-1)){
		while(second_counter<size){
			distance=calc_distance(graph+first_counter,graph+second_counter);
			if (distance<radius){
				add_neighbour((graph+first_counter)->id,graph+second_counter);
				add_neighbour((graph+second_counter)->id,graph+first_counter);
				}
			second_counter++;
			}
		first_counter++;
		second_counter=first_counter+1;
		}
	}

// Imprime os elementos do grafo junto com a lista de adjacências.
void print_elements(node *graph, int size){
	int counter;
	neighbour_list *pointer;
	counter=0;
	while(counter<size){
		printf("adjacentes ao nó %d: ",(graph+counter)->id);
		pointer=(graph+counter)->neighbours;
		while (pointer->next){
			printf("%d, ",pointer->id);
			pointer=pointer->next;
			}
		counter++;
		printf("%d.\n",pointer->id);
		}
	}

//A main() do código. O código espera apenas um argumento, que deve ser o nome do arquivo.
int main(int argc, char *argv[]){
	if (argc<2){
		printf("Parâmetros insuficientes\n");
		return 0;
		}
	if (argc>2){
		printf("Parâmetros em excesso\n");
		return 0;
		}
	FILE *archive;
	archive=fopen(argv[1],"r");
	if (!archive){
		printf("Erro no arquivo\n");
		return 0;
		}
	int size,counter;
	counter=0;
	double radius;
	node *graph;
	fscanf(archive,"%d\t%lf",&size, &radius);
	graph=(node*)malloc(sizeof(node)*size);
	while(counter<size){
		fscanf(archive,"%d\t%lf\t%lf",&((graph+counter)->id),&((graph+counter)->x_position),&((graph+counter)->y_position));
		counter++;
		}
	update_graph_neighbours(size,radius,graph);
	print_elements(graph,size);
	fclose(archive);
	return 0;
	}
