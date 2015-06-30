/* Laboratório de Programação Avançada - LPAV
 * Aluno: Luan de Freitas Uchôa - 21200591
 * Aula 03 - Tabelas Hash - 02/05/2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int size_hash_table;

// Estrutura para cada indivíduo
typedef struct strc1{
	char name[50];
	long long int cpf;
	int age;
	struct strc1 *next;
	} person_field;

// Estrutura para a tabela
typedef struct{
	person_field *person;
	} hash_table;

// Cálculo do hash (nesse caso, o resto do cpf dividido pelo tamanho da tabela
int do_hash(long long int cpf, int size){
	return cpf%size;
	}

// Inicializa os ponteiros da tabela com NULL
void initialize_table(hash_table *table){
	int counter=0;
	while (counter<size_hash_table){
		(table+counter)->person=NULL;
		counter++;
		}
	}

// Insere posições na tabela, sempre no início (caso hajam colisões)
bool insert_on_table(hash_table *table, person_field *person){
	person_field *tmp;	
	int hash_position;
	hash_position=do_hash(person->cpf,size_hash_table);
	tmp=(table+hash_position)->person;
	(table+hash_position)->person=person;
	(table+hash_position)->person->next=tmp;
	return true;
	}

// Lista as posições da tabela que têm nomes inseridos, assim como os nomes
void list_table(hash_table *table){
	int counter=0;
	person_field *person;
	while (counter<size_hash_table){
		person=(table+counter)->person;
		if (person){
			printf ("Posição %d da tabela:\n",counter);
			while (person){
				printf("- %s\t%lld\t%d\n",person->name,person->cpf,person->age);
				person=person->next;
				}
			}
		person=NULL;
		counter++;
		}
	}

// A main do código.
// argv[1] deve ser o tamanho da tabela e argv[2] deve ser um arquivo
int main(int argc, char *argv[]){
	if (argc<3){
		printf("Parâmetros insuficientes\n");
		return 0;
		}
	if (argc>3){
		printf("Parâmetros em excesso\n");
		return 0;
		}
	int hash_position;
	person_field *person_read;
	FILE *arquivo;
	sscanf(argv[1],"%d",&size_hash_table);
	hash_table *table=(hash_table*)malloc(sizeof(hash_table)*size_hash_table);
	initialize_table(table);

	arquivo=fopen(argv[2],"r");
	if (!arquivo){
		printf("erro no arquivo\n");
		return 0;
		}

	while (!feof(arquivo)){
		person_read=(person_field*)malloc(sizeof(person_field));
		fscanf(arquivo,"%50[^\t]\t%lld\t%d\n",&(person_read->name),&(person_read->cpf),&(person_read->age));
		insert_on_table(table,person_read);
		}

	list_table(table);

	printf("\n");
	return 0;
	}
