/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 01/08/2014 - Aula 13: mais pthreads, parte 1
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>

// Essa estrutura possibilita a operação das threads sem mutexes.
typedef struct{
	int start;
	int end;
	int index;
	}int_tuple;

/* Variáveis para o tamanho do vetor, a soma dos valores (para as threads)
 * e para o controle de tamanho.
 */

int *the_vector, *sum_vector_values;

int vector_size;

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

// Inicializa um vetor com valores aleatórios de 0 a 200.
void set_random_values(int *vector){
	int counter;
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	srandom(current_time.tv_usec);
	for(counter=0;counter<vector_size;counter++) vector[counter]=(random())%201;
	}

// Soma de vetores que é utilizada na main.
int sum_vector(int *vector){
	int counter;
	int result=0;
	for(counter=0;counter<vector_size;counter++)
		result=result+vector[counter];
	return result;
	}

/* Soma de vetores que é utilizada nas threads.
 * A função foi trabalhada conjuntamente com a main de forma que não é
 * necessário usar mutexes (por mais estranho que pareça).
 *
 * Essencialmente, a função utiliza a estrutura passada como parâmetro
 * para determinar o intervalo de soma. Essa estrutura também carrega
 * um índice que determina onde esses valores devem ser armazenados, de
 * modo que, ainda que hajam leituras concorrentes, nunca ocorre uma
 * escrita concorrente, isto é, as escritas de diferentes threads nunca
 * vão escrever em uma mesma posição.
 */
void *threaded_sum_vector(void *off_vec){
	int sum=0,counter,start,end;
	int_tuple *offset;
	offset=(int_tuple*) off_vec;
	start=offset->start;
	end=offset->end;

	for(counter=start;counter<=end;counter++)
		sum=the_vector[counter]+sum;

	sum_vector_values[offset->index]=sum;
	}

// O primeiro parâmetro é o tamanho do vetor, e o segundo é o número de threads.
int main(int argc, char *argv[]){
	if (argc!=3){
		printf("Número incorreto de parâmetros\n");
		printf("Uso: ./<nome do programa> <tam. do vetor> <qtd. de threads>\n");
		return 0;
		}
	int thread_quantity, sum, sum_thread=0, counter;
	int offset=0, partition_size;
	int_tuple *offset_vector;
	double time_main, time_thread;
	// Um vetor de pthreads permite a criação dinâmica de threads.
	pthread_t *thread_vector;
	sscanf(argv[1],"%d",&vector_size);
	sscanf(argv[2],"%d",&thread_quantity);
	printf("vector size: %d, number of threads: %d\n",vector_size,thread_quantity);

	// Alocação dos diversos valores.
	thread_vector=(pthread_t*)malloc(sizeof(pthread_t)*thread_quantity);
	offset_vector=(int_tuple*)malloc(sizeof(int_tuple)*thread_quantity);
	sum_vector_values=(int*)malloc(sizeof(int)*thread_quantity);
	the_vector=(int*)malloc(sizeof(int)*vector_size);

	//Define o tamanho de cada segmento para as operações das threads.
	partition_size=vector_size/thread_quantity;
	partition_size--;

	//Cria os intervalos que cada partição vai checar.
	for(counter=0;counter<thread_quantity-1;counter++){
		offset_vector[counter].start=offset;
		offset=offset+partition_size;
		offset_vector[counter].end=offset;
		offset++;
		offset_vector[counter].index=counter;
		}

	/* Cria o intervalo para a última thread.
	 * Isso é feito para garantir que não haja valores deixados de fora,
	 * já que a divisão de inteiros não vai gerar partições exatamente
	 * iguais.
	 */
	offset_vector[thread_quantity-1].start=offset;
	offset_vector[thread_quantity-1].end=vector_size-1;
	offset_vector[thread_quantity-1].index=counter;

	set_random_values(the_vector);

	// Inicia a soma dos valores e a marcação de tempo.
	set_start_time();
	sum=sum_vector(the_vector);
	set_end_time();
	time_main=end_time-start_time;

	// Cria as threads e inicia a marcação de tempo; depois as finaliza e termina a marcação.
	set_start_time();
	for(counter=0;counter<thread_quantity;counter++)
		pthread_create(thread_vector+counter,NULL,threaded_sum_vector,(void*)(offset_vector+counter));
	for(counter=0;counter<thread_quantity;counter++)
		pthread_join(thread_vector[counter],NULL);
	set_end_time();
	time_thread=end_time-start_time;
	
	// Soma os valores obtidos por cada thread.
	for(counter=0;counter<thread_quantity;counter++)
		sum_thread=sum_thread+sum_vector_values[counter];

	printf("sum value: %d, time at main: %f seconds\n",sum,time_main);
	printf("sum value: %d, time with threads: %f seconds\n",sum_thread,time_thread);

	//Libera toda a memória alocada.
	free(the_vector);
	free(sum_vector_values);
	free(thread_vector);
	free(offset_vector);
	return 0;
	}
