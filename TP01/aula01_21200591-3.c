/* Laboratório de Programação Avançada - LPAV
 * Aluno: Luan de Freitas Uchôa - 21200591
 * Trabalho Prático 01 - 02/05/2014
 * Questão 01
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
	double time;
	int target;
	int type;
	} evento_t;

typedef struct strc1{
	evento_t *event;
	struct strc1 *next_event;
	} lista_eventos_t;

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *new;
	new=(lista_eventos_t*)malloc(sizeof(lista_eventos_t));
	new->event=evento;
	new->next_event=NULL;
	lista_eventos_t *pointer;
	if (!(*lista)){
		*lista=new;
		return true;
		}
	if (((*lista)->event->time)>(new->event->time)){
		new->next_event=(*lista);
		*lista=new;
		return true;
		}
	if((((*lista)->event->time)>(new->event->time))&&(!((*lista)->next_event))){
		(*lista)->next_event=new;
		return true;
		}
		
	pointer=*lista;
	while ((pointer->next_event)&&((new->event->time)>(pointer->next_event->event->time))){
		pointer=pointer->next_event;
		}
	new->next_event=pointer->next_event;
	pointer->next_event=new;
	return true;
	}

evento_t *novo_evento(double tempo, int alvo, int tipo){
	evento_t *tmp;
	tmp=(evento_t*)malloc(sizeof(evento_t));
	tmp->time=tempo;
	tmp->target=alvo;
	tmp->type=tipo;
	return tmp;
	}

void lista_eventos_listar(lista_eventos_t *lista){
	while (lista){
		printf("%3.6f\t%d\t%d\n",lista->event->time,lista->event->target,lista->event->type);
		lista=lista->next_event;
		}
	}

void libertar_lista(lista_eventos_t *lista){
	//Liberdade, ar puro...
	lista_eventos_t *tmp;
	while (lista){
		tmp=lista->next_event;
		free(lista->event);
		free(lista);
		lista=tmp;
		}
	}

int main(int argc, char *argv[]){
	if (argc<2){
		printf("falta o nome do arquivo\n");
		return 0;
		}
	if (argc>2){
		printf("muitos argumentos na linha de comando\n");
		return 0;
		}
	double tempo_lido;
	int alvo_lido,tipo_lido;
	evento_t *evento_lido;
	lista_eventos_t *lista;
	lista=NULL;
	evento_lido=(evento_t*)malloc(sizeof(evento_t));
	FILE *arquivo;
	arquivo=fopen(argv[1],"r");
	while (!feof(arquivo)){
		fscanf(arquivo,"%lf\t%d\t%d\n",&tempo_lido,&alvo_lido,&tipo_lido);
		if(!lista_eventos_adicionar_ordenado(novo_evento(tempo_lido,alvo_lido,tipo_lido),&lista)){
			printf("houve alguma falha na hora de inserir\n");
			return 0;
			}
		}
	lista_eventos_listar(lista);
	libertar_lista(lista);
	return 0;
	}
