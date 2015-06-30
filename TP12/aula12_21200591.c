/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Laboratório de Programação Avançada - LPAv
 * Luan de Freitas Uchôa - 21200591
 *
 * 25/07/2014 - Aula 12: pthreads
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>

// Variável para o tamanho do vetor.
int vector_size;

// Variáveis para a marcação de tempo.
double start_time, end_time;

// Mutexes para controle de operações no vetor e no tamanho deste.
pthread_mutex_t mutex_size = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_vector = PTHREAD_MUTEX_INITIALIZER;

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
 * Um mutex gerencia operações na variável global que corresponde ao tamanho do vetor
 * e o outro mutex gerencia as operações na primeira posição do vetor.
 * A variável private_size é utilizada para permitir que a variável do tamanho do
 * vetor não fique travada por mais tempo do que o necessário.
 */
void *threaded_sum_vector(void *vec){
	int *vector,private_size;
	vector=(int*) vec;
	while(vector_size>0){
		pthread_mutex_lock(&mutex_size);
		vector_size--;
		private_size=vector_size;
		pthread_mutex_unlock(&mutex_size);
		
		pthread_mutex_lock(&mutex_vector);
		if (private_size>0)
			vector[0]=vector[0]+vector[private_size];
		pthread_mutex_unlock(&mutex_vector);
		}
	}

// O primeiro parâmetro é o tamanho do vetor, e o segundo é o número de threads.
int main(int argc, char *argv[]){
	if (argc!=3){
		printf("Número incorreto de parâmetros\n");
		printf("Uso: ./<nome do programa> <tam. do vetor> <qtd. de threads>\n");
		return 0;
		}
	int thread_quantity, sum, thread_index, *the_vector;
	double time_main, time_thread;
	// Um vetor de pthreads permite a criação dinâmica de threads.
	pthread_t *thread_vector;
	sscanf(argv[1],"%d",&vector_size);
	sscanf(argv[2],"%d",&thread_quantity);
	printf("vector size: %d, number of threads: %d\n",vector_size,thread_quantity);
	thread_vector=(pthread_t*)malloc(sizeof(pthread_t)*thread_quantity);
	the_vector=(int*)malloc(sizeof(int)*vector_size);
	set_random_values(the_vector);

	// Inicia a soma dos valores e a marcação de tempo.
	set_start_time();
	sum=sum_vector(the_vector);
	set_end_time();
	time_main=end_time-start_time;

	// Cria as threads e inicia a marcação de tempo.
	set_start_time();
	for(thread_index=0;thread_index<thread_quantity;thread_index++)
		pthread_create(thread_vector+thread_index,NULL,threaded_sum_vector,(void*)the_vector);
	for(thread_index=0;thread_index<thread_quantity;thread_index++)
		pthread_join(thread_vector[thread_index],NULL);
	set_end_time();
	time_thread=end_time-start_time;
	
	printf("sum value: %d, time at main: %f seconds\n",sum,time_main);
	printf("sum value: %d, time with threads: %f seconds\n",the_vector[0],time_thread);
	free(the_vector);
	free(thread_vector);
	return 0;
	}
