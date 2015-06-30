/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 01/08/2014 - Aula 13: mais pthreads, parte 2
 */

/* ********************************************
 * ****************** AVISO *******************
 * ********************************************
 *
 * O código utiliza matrizes de long int alocadas dinamicamente.
 * São utilizadas quatro matrizes: as duas que serão multiplicadas,
 * a matriz que armazena os resultados da main() e a matriz que
 * armazena os resultados das threads (para que eu possa comparar).
 *
 * Isso ocupa MUITO espaço, a depender do valor da entrada.
 *
 * A quantidade total de espaço utilizada pode ser calculada, aproximadamente,
 * pela seguinte função:
 *
 * kn²/x = s
 *
 * onde s é o espaço em memória, k = 1.0010624, x = 2^15 e n é o tamanho da
 * matriz (n x n). Essa conta resulta em um consumo de espaço em megabytes.
 * Para comparação, uma conta executada com n = 10000 ocupa 3,5GB de RAM e
 * leva ao menos cinco horas para processamento.
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>

// Essa estrutura possibilita a operação das threads sem mutexes.
typedef struct{
	int start;
	int end;
	}int_tuple;

/* Variáveis que controlam o tamanho do vetor.
 * matrix_a e matrix_b são as matrizes a serem multiplicadas.
 * matrix_result é a matriz que armazena o resultado.
 * matrix_size é uma variável de referência para o tamanho da matriz.
 */

long int **matrix_a, **matrix_b, **matrix_result;

int matrix_size;

// Variáveis para a marcação de tempo.
double start_time, end_time;

// Função para marcar o tempo de início.
void set_start_time(){
	double usec;
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	usec=current_time.tv_usec;
	start_time=current_time.tv_sec+(usec/1000000);
	}
 
// Similar à função acima (de fato, faz quase a mesma coisa)
void set_end_time(){
	double usec;
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	usec=current_time.tv_usec;
	end_time=current_time.tv_sec+(usec/1000000);
	}

/* Função para multiplicar uma linha por uma coluna.
 * No contexto da multiplicação de matrizes, essa função recebe a
 * posição do elemento que deve ser calculado (a posição do elemento
 * na matriz resultado) e multiplica a linha e coluna necessárias que
 * resultam naquele elemento. O elemento calculado é retornado.
 * matrix_a e matrix_b são matrizes globais, assim como a variável
 * matrix_size.
 */
long int multiply_for_element(int index_i, int index_j){
	int counter;
	long int result=0;
	for(counter=0;counter<matrix_size;counter++)
		result=result+(matrix_a[index_i][counter]*matrix_b[counter][index_j]);
	return result;
	}

/* Multiplicação de matrizes utilizada na main.
 * Essa função utilza a função multiply_for_element() para calcular os elementos
 * da matriz resultado, e depois atribui na matriz resultado esses elementos
 * calculados.
 */
void multiply_matrix(){
	int counter1,counter2;
	for(counter1=0;counter1<matrix_size;counter1++){
		for(counter2=0;counter2<matrix_size;counter2++){
			matrix_result[counter1][counter2]=multiply_for_element(counter1,counter2);
			}
		}
	}

// Cria uma matriz quadrada com elementos aleatórios entre 1 e 14.
long int **create_random_matrix(){
	long int **pointer;
	int counter,counter2;
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	srandom(current_time.tv_usec);
	pointer=(long int**)malloc(sizeof(long int*)*matrix_size);
	for(counter=0;counter<matrix_size;counter++)
		pointer[counter]=(long int*)malloc(sizeof(long int)*matrix_size);

	for(counter=0;counter<matrix_size;counter++){
		for (counter2=0;counter2<matrix_size;counter2++)
			pointer[counter][counter2]=(random())%15;
		}
	return pointer;
	}

/* O único propósito desta função é checar se duas matrizes (quadradas)
 * são iguais.
 * matrix_result é variável global.
 */
int check_matrix_match(long int **second_matrix){
	int counter1,counter2;
	for(counter1=0;counter1<matrix_size;counter1++){
		for(counter2=0;counter2<matrix_size;counter2++){
			if(second_matrix[counter1][counter2]!=matrix_result[counter1][counter2]){
				printf("Resultados diferentes!\n");
				return 0;
				}
			}
		}
	printf("Resultados iguais.\n");
	return 1;
	}

/* Multiplicação de matrizes que é utilizada nas threads.
 * A função foi trabalhada conjuntamente com a main de forma que não é
 * necessário usar mutexes (por mais estranho que pareça).
 * Essa função age conforme a ideia proposta para a melhoria de desempenho da
 * soma de vetores com threads.
 */
void *threaded_matrix_multiplier(void *off_vec){
	int counter1,counter2,start,end;
	int_tuple *offset;
	offset=(int_tuple*) off_vec;
	start=offset->start;
	end=offset->end;

	for(counter1=start;counter1<=end;counter1++){
		for(counter2=0;counter2<matrix_size;counter2++)
			matrix_result[counter1][counter2]=multiply_for_element(counter1,counter2);
		}
	}

// O primeiro parâmetro é o tamanho do vetor, e o segundo é o número de threads.
int main(int argc, char *argv[]){
	if (argc!=3){
		printf("Número incorreto de parâmetros\n");
		printf("Uso: ./<nome do programa> <ordem da matriz> <qtd. de threads>\n");
		return 0;
		}
	int thread_quantity, sum, sum_thread=0, counter;
	int offset=0, partition_size;
	long int **matrix_copy;
	int_tuple *offset_vector;
	double time_main, time_thread;
	// Um vetor de pthreads permite a criação dinâmica de threads.
	pthread_t *thread_vector;
	sscanf(argv[1],"%d",&matrix_size);
	sscanf(argv[2],"%d",&thread_quantity);

	printf("Criando dados para as matrizes... ");
	thread_vector=(pthread_t*)malloc(sizeof(pthread_t)*thread_quantity);
	offset_vector=(int_tuple*)malloc(sizeof(int_tuple)*thread_quantity);
	partition_size=matrix_size/thread_quantity;
	partition_size--;

	for(counter=0;counter<thread_quantity-1;counter++){
		offset_vector[counter].start=offset;
		offset=offset+partition_size;
		offset_vector[counter].end=offset;
		offset++;
		}

	offset_vector[thread_quantity-1].start=offset;
	offset_vector[thread_quantity-1].end=matrix_size-1;
	
	matrix_a=create_random_matrix();
	matrix_b=create_random_matrix();
	printf("feito.\n\n");

	matrix_result=(long int**)malloc(sizeof(long int*)*matrix_size);
	for(counter=0;counter<matrix_size;counter++)
		matrix_result[counter]=(long int*)malloc(sizeof(long int)*matrix_size);

	printf("Iniciando as contas na função main().\n");

	set_start_time();
	multiply_matrix();
	set_end_time();
	time_main=end_time-start_time;

	printf("As contas na main() foram finalizadas.\n");

	/* Aloca uma nova matriz para fazer uma cópia do resultado.
	 * Isso é feito para saber se a multiplicação está igual.
	 */
	matrix_copy=(long int**)malloc(sizeof(long int*)*matrix_size);
	for(counter=0;counter<matrix_size;counter++)
		matrix_copy[counter]=(long int*)malloc(sizeof(long int)*matrix_size);

	for(counter=0;counter<matrix_size;counter++){
		for(offset=0;offset<matrix_size;offset++)
			matrix_copy[counter][offset]=matrix_result[counter][offset];
		}

	printf("\nIniciando as contas com %d threads.\n",thread_quantity);

	// Inicia as contas com as threads, assim como a marcação de tempo.
	set_start_time();
	for(counter=0;counter<thread_quantity;counter++)
		pthread_create(thread_vector+counter,NULL,threaded_matrix_multiplier,(void*)(offset_vector+counter));
	for(counter=0;counter<thread_quantity;counter++)
		pthread_join(thread_vector[counter],NULL);
	set_end_time();
	time_thread=end_time-start_time;

	printf("As threads foram finalizadas.\n\n");

	check_matrix_match(matrix_copy);
	printf("\n");

	printf("Tempo na main(): %f segundos\n",time_main);
	printf("Tempo com threads: %f segundos\n",time_thread);
	
	//Libera tudo que foi alocado.
	free(thread_vector);
	free(offset_vector);
	for(counter=0;counter<matrix_size;counter++){
		free(matrix_a[counter]);
		free(matrix_b[counter]);
		free(matrix_result[counter]);
		free(matrix_copy[counter]);
		}
	free(matrix_a);
	free(matrix_b);
	free(matrix_result);
	free(matrix_copy);
	return 0;
	}
