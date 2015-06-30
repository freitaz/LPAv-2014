#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

/* Universidade Federal do Amazonas
 * Instituto de Computação
 * Laboratório de Programação Avançada
 * Luan de Freitas Uchôa - 21200591
 * Trabalho Prático 02 - 09/05/2014
 */

// Constante para definir o tamanho do vetor
#define SIZE_VECTOR 50000

// Constante pra definir quantas rodadas de teste com números aleatórios serão feitas
#define MAX_RAND_TESTS 10

// Os contadores de checagens e trocas
long int check_counter, swap_counter;

//Marcadores de tempo
double start_time_counter, finish_time_counter;

//Estrutura para uso com os métodos de comparação com aleatórios
typedef struct{
	double average_time;
	double best_time;
	double worst_time;
	double total_time;
	int average_checks;
	int best_checks;
	int worst_checks;
	unsigned long int total_checks;
	int average_swap;
	int best_swap;
	int worst_swap;
	unsigned long int total_swap;
	}rand_struct;

//O método bubble sort.
void bubblesort(int vector[SIZE_VECTOR]){
    int index_i, index_j, aux_value;
    for(index_i=0; index_i<SIZE_VECTOR; index_i++){
        for(index_j=index_i; index_j<SIZE_VECTOR; index_j++){
            if(vector[index_i]>vector[index_j]) {
                aux_value=vector[index_i];
                vector[index_i]=vector[index_j];
                vector[index_j]=aux_value;
                swap_counter++;
	            }
	            check_counter++;
			}
		}
	}

//O método insertion sort.
void insertion_sort(int vector[SIZE_VECTOR]) {
	int index_i, index_j, aux_value;
	for (index_i = 1; index_i < SIZE_VECTOR; index_i++){
		aux_value = vector[index_i];
		index_j = index_i - 1;
		while ((index_j>=0) && (aux_value < vector[index_j])) {
			check_counter++;
			vector[index_j+1] = vector[index_j];
			swap_counter++;
			index_j--;
			}
		check_counter++;
		vector[index_j+1] = aux_value;
		}
	}

//O método selection sort.
void selection_sort(int vector[SIZE_VECTOR]) { 
	int index_i, index_j, index_min, aux_value;
	for (index_i = 0; index_i < (SIZE_VECTOR-1); index_i++) {
		index_min = index_i;
		for (index_j = (index_i+1); index_j < SIZE_VECTOR; index_j++) {
			check_counter++;
			if(vector[index_j] < vector[index_min]) {
				index_min = index_j;
				}
			}
		if (index_i != index_min) {
			aux_value = vector[index_i];
			vector[index_i] = vector[index_min];
			vector[index_min] = aux_value;
			swap_counter++;
			}
	}
}

// O miolo do merge sort (a conquista).
void merge(int vector[], int vector_size) {
	int middle, index_i, index_j, index_k;
	int* tmp;
	tmp = (int*) malloc(vector_size * sizeof(int));
	if (tmp == NULL) {
		exit(1);
		}
	middle = vector_size / 2;
	index_i = 0;
	index_j = middle;
	index_k = 0;
	while (index_i < middle && index_j < vector_size) {
		check_counter++;
		if (vector[index_i] <= vector[index_j]) {
			tmp[index_k] = vector[index_i++];
			}
		else {
			tmp[index_k] = vector[index_j++];
			}
		++index_k;
		}
	if (index_i == middle) {
		while (index_j < vector_size) {
			tmp[index_k++] = vector[index_j++];
			}
	}
	else {
 		while (index_i < middle) {
			tmp[index_k++] = vector[index_i++];
			}
		}
	for (index_i = 0; index_i < vector_size; ++index_i) {
		swap_counter++;
		vector[index_i] = tmp[index_i];
		}
	free(tmp);
	}

// Outro miolo do merge sort (a divisão)
void mergeSort(int vector[], int vector_size) {
	int middle;
	if (vector_size > 1) {
		middle = vector_size / 2;
		mergeSort(vector, middle);
		mergeSort(vector + middle, vector_size - middle);
		merge(vector, vector_size);
		}
	}

// Uma porcariazinha que apenas faz a primeira chamada de merge sort
void mergesort(int vector[SIZE_VECTOR]){
	mergeSort(vector,SIZE_VECTOR);
	}

// O método quick sort
void quickSort(int vector[], int left_bound, int right_bound){
	int index_i, index_j, pivot_value, aux_value;
	index_i = left_bound;
	index_j = right_bound;
	pivot_value = vector[(left_bound+right_bound) / 2];
    while(index_i <= index_j){
		while(vector[index_i] < pivot_value && index_i < right_bound){
			check_counter++;
			index_i++;
			}
		check_counter++;
		while(vector[index_j] > pivot_value && index_j > left_bound){
			index_j--;
			check_counter++;
			}
		check_counter++;
		if(index_i <= index_j){
			aux_value = vector[index_i];
			vector[index_i] = vector[index_j];
			vector[index_j] = aux_value;
			swap_counter++;
			index_i++;
			index_j--;
			}
		}
	if(index_j > left_bound){
		quickSort(vector, left_bound, index_j);
		}
	if(index_i < right_bound){
		quickSort(vector, index_i, right_bound);
		}
	}

// Uma porcariazinha que apenas chama o quick sort pela primeira vez
void quicksort(int vector[SIZE_VECTOR]){
	quickSort(vector, 0, SIZE_VECTOR-1);	
	}

// Copia um vetor para outro. O primeiro parâmetro é o vetor que receberá a cópia,
// e o segundo parâmetro é o vetor que será copiado.
void copy_vector(int vector[SIZE_VECTOR], int reserve_vector[SIZE_VECTOR]){
	int counter;
	counter=0;
	while (counter<SIZE_VECTOR){
		vector[counter]=reserve_vector[counter];
		counter++;
		}	
	}

// Carrega o vetor com valores em ordem crescente.
void set_crescent_values(int vector[SIZE_VECTOR]){
	int value,counter;
	value=SIZE_VECTOR/2;
	counter=0;
	while (counter<SIZE_VECTOR){
		vector[counter]=value;
		value++;
		counter++;
		}
	}

// Carrega o vetor com valores em ordem decrescente.
void set_decrescent_values(int vector[SIZE_VECTOR]){
	int value,counter;
	value=(3*SIZE_VECTOR)/2;
	counter=0;
	while (counter<SIZE_VECTOR){
		vector[counter]=value;
		value--;
		counter++;
		}
	}

// Carrega o vetor com valores aleatórios. A data atual é usada para aumentar o
// "grau" de aleatoriedade.
void set_random_values(int vector[SIZE_VECTOR]){
	int counter;
	counter=0;
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	srand(current_time.tv_usec);
	while (counter<SIZE_VECTOR){
		vector[counter]=rand();
		counter++;
		}
	}

// Altera o marcador de tempo start_time_counter. Algumas contas são feitas para que
// o valor caiba em uma variável double.
void start_counter(){
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	start_time_counter=current_time.tv_usec;
	start_time_counter=current_time.tv_sec+(start_time_counter/1000000);
	}

// Similar à função acima (de fato, faz a mesma coisa :v)
void end_counter(){
	struct timeval current_time;
	gettimeofday(&current_time,NULL);
	finish_time_counter=current_time.tv_usec;
	finish_time_counter=current_time.tv_sec+(finish_time_counter/1000000);
	}

void compare_with_ordered(int vector[SIZE_VECTOR],int reserve_vector[SIZE_VECTOR]){
	/* Compara o desempenho dos métodos de ordenamento.
	 * O vetor deverá estar ordenado antes da chamada da função, ou diretamente
	 * ou reversamente. No entanto, vetores desordenados não levam a função à falhar. 
	 */
	double time_gap; //receberá a diferença entre tempos de início e fim
	printf("method\t\ttime\t\tcheck\t\tswap\n");

// Processo para o bubble sort.	
	check_counter=0;
	swap_counter=0;
	start_counter();		
	bubblesort(vector);
	end_counter();
	time_gap=finish_time_counter-start_time_counter;
	printf("bubble\t\t%f\t%10d\t%10d\n",time_gap,check_counter,swap_counter);

// Processo para o insertion sort.
	check_counter=0;
	swap_counter=0;
	copy_vector(vector,reserve_vector);
	finish_time_counter=0;
	start_time_counter=0;
	start_counter();		
	insertion_sort(vector);
	end_counter();
	time_gap=finish_time_counter-start_time_counter;
	printf("insertion\t%f\t%10d\t%10d\n",time_gap,check_counter,swap_counter);

// Processo para o selection sort.
	check_counter=0;
	swap_counter=0;
	copy_vector(vector,reserve_vector);
	finish_time_counter=0;
	start_time_counter=0;
	start_counter();		
	selection_sort(vector);
	end_counter();
	time_gap=finish_time_counter-start_time_counter;
	printf("selection\t%f\t%10d\t%10d\n",time_gap,check_counter,swap_counter);

// Processo para o merge sort.
	check_counter=0;
	swap_counter=0;
	copy_vector(vector,reserve_vector);
	finish_time_counter=0;
	start_time_counter=0;
	start_counter();		
	mergesort(vector);
	end_counter();
	time_gap=finish_time_counter-start_time_counter;
	printf("merge\t\t%f\t%10d\t%10d\n",time_gap,check_counter,swap_counter);

// Processo para o quick sort.
	check_counter=0;
	swap_counter=0;
	copy_vector(vector,reserve_vector);
	finish_time_counter=0;
	start_time_counter=0;
	start_counter();		
	quicksort(vector);
	end_counter();
	time_gap=finish_time_counter-start_time_counter;
	printf("quick\t\t%f\t%10d\t%10d\n",time_gap,check_counter,swap_counter);
	printf("\n");
	}

/* A função abaixo executa uma sequência de ordenamentos de vetores.
 * O valor é definido por MAX_RAND_TESTS. A cada execução de um método,
 * os valores são armazenados em uma estrutura e ao final é tirada uma média.
 * A cada interação definida por MAX_RAND_TESTS, o mesmo vetor é usado; ao término
 * da interação é gerado um novo vetor.
 */

void compare_with_random(int vector[SIZE_VECTOR],int reserve_vector[SIZE_VECTOR]){
	/* Para os vetores: o índice segue a seguinte ordem:
	 * 0. Bubble Sort
	 * 1. Insertion Sort
	 * 2. Selection Sort
	 * 3. Merge Sort
	 * 4. Quick Sort
	 */
	rand_struct result_methods[5];
	
	int current_method;
	int counter;
	double time_gap;
	counter=0;
	while(counter<MAX_RAND_TESTS){
		finish_time_counter=0;
		start_time_counter=0;
		check_counter=0;
		swap_counter=0;
		current_method=0;
		printf("Execução %d dos métodos, total de %d.\n",counter+1,MAX_RAND_TESTS);
		
// Execução para o bubble sort.
		start_counter();
		bubblesort(vector);
		end_counter();
		time_gap=finish_time_counter-start_time_counter;
		if (!counter){
			result_methods[current_method].best_time=time_gap;
			result_methods[current_method].worst_time=time_gap;
			result_methods[current_method].total_time=time_gap;
			result_methods[current_method].best_checks=check_counter;
			result_methods[current_method].worst_checks=check_counter;
			result_methods[current_method].total_checks=check_counter;
			result_methods[current_method].best_swap=swap_counter;
			result_methods[current_method].worst_swap=swap_counter;
			result_methods[current_method].total_swap=swap_counter;
			}
		else{
			if (result_methods[current_method].best_time>time_gap){
				result_methods[current_method].best_time=time_gap;
				}
			if (result_methods[current_method].worst_time<time_gap){
				result_methods[current_method].worst_time=time_gap;
				}
			result_methods[current_method].total_time=result_methods[current_method].total_time+time_gap;
			if (result_methods[current_method].best_checks>check_counter){
				result_methods[current_method].best_checks=check_counter;
				}
			if (result_methods[current_method].worst_checks<check_counter){
				result_methods[current_method].worst_checks=check_counter;
				}
			result_methods[current_method].total_checks=result_methods[current_method].total_checks+check_counter;
			if (result_methods[current_method].best_swap>swap_counter){
				result_methods[current_method].best_swap=swap_counter;
				}
			if (result_methods[current_method].worst_swap<swap_counter){
				result_methods[current_method].worst_swap=swap_counter;
				}
			result_methods[current_method].total_swap=result_methods[current_method].total_swap+swap_counter;
			}

//Execução para o insertion sort.
		copy_vector(vector,reserve_vector);
		finish_time_counter=0;
		start_time_counter=0;
		check_counter=0;
		swap_counter=0;
		current_method=1;
		start_counter();
		insertion_sort(vector);
		end_counter();
		time_gap=finish_time_counter-start_time_counter;
		if (!counter){
			result_methods[current_method].best_time=time_gap;
			result_methods[current_method].worst_time=time_gap;
			result_methods[current_method].total_time=time_gap;
			result_methods[current_method].best_checks=check_counter;
			result_methods[current_method].worst_checks=check_counter;
			result_methods[current_method].total_checks=check_counter;
			result_methods[current_method].best_swap=swap_counter;
			result_methods[current_method].worst_swap=swap_counter;
			result_methods[current_method].total_swap=swap_counter;
			}
		else{
			if (result_methods[current_method].best_time>time_gap){
				result_methods[current_method].best_time=time_gap;
				}
			if (result_methods[current_method].worst_time<time_gap){
				result_methods[current_method].worst_time=time_gap;
				}
			result_methods[current_method].total_time=result_methods[current_method].total_time+time_gap;
			if (result_methods[current_method].best_checks>check_counter){
				result_methods[current_method].best_checks=check_counter;
				}
			if (result_methods[current_method].worst_checks<check_counter){
				result_methods[current_method].worst_checks=check_counter;
				}
			result_methods[current_method].total_checks=result_methods[current_method].total_checks+check_counter;
			if (result_methods[current_method].best_swap>swap_counter){
				result_methods[current_method].best_swap=swap_counter;
				}
			if (result_methods[current_method].worst_swap<swap_counter){
				result_methods[current_method].worst_swap=swap_counter;
				}
			result_methods[current_method].total_swap=result_methods[current_method].total_swap+swap_counter;
			}

//Execução para o selection sort.
		copy_vector(vector,reserve_vector);
		finish_time_counter=0;
		start_time_counter=0;
		check_counter=0;
		swap_counter=0;
		current_method=2;
		start_counter();
		selection_sort(vector);
		end_counter();
		time_gap=finish_time_counter-start_time_counter;
		if (!counter){
			result_methods[current_method].best_time=time_gap;
			result_methods[current_method].worst_time=time_gap;
			result_methods[current_method].total_time=time_gap;
			result_methods[current_method].best_checks=check_counter;
			result_methods[current_method].worst_checks=check_counter;
			result_methods[current_method].total_checks=check_counter;
			result_methods[current_method].best_swap=swap_counter;
			result_methods[current_method].worst_swap=swap_counter;
			result_methods[current_method].total_swap=swap_counter;
			}
		else{
			if (result_methods[current_method].best_time>time_gap){
				result_methods[current_method].best_time=time_gap;
				}
			if (result_methods[current_method].worst_time<time_gap){
				result_methods[current_method].worst_time=time_gap;
				}
			result_methods[current_method].total_time=result_methods[current_method].total_time+time_gap;
			if (result_methods[current_method].best_checks>check_counter){
				result_methods[current_method].best_checks=check_counter;
				}
			if (result_methods[current_method].worst_checks<check_counter){
				result_methods[current_method].worst_checks=check_counter;
				}
			result_methods[current_method].total_checks=result_methods[current_method].total_checks+check_counter;
			if (result_methods[current_method].best_swap>swap_counter){
				result_methods[current_method].best_swap=swap_counter;
				}
			if (result_methods[current_method].worst_swap<swap_counter){
				result_methods[current_method].worst_swap=swap_counter;
				}
			result_methods[current_method].total_swap=result_methods[current_method].total_swap+swap_counter;
			}

// Execução para o merge sort.
		copy_vector(vector,reserve_vector);
		finish_time_counter=0;
		start_time_counter=0;
		check_counter=0;
		swap_counter=0;
		current_method=3;
		start_counter();
		mergesort(vector);
		end_counter();
		time_gap=finish_time_counter-start_time_counter;
		if (!counter){
			result_methods[current_method].best_time=time_gap;
			result_methods[current_method].worst_time=time_gap;
			result_methods[current_method].total_time=time_gap;
			result_methods[current_method].best_checks=check_counter;
			result_methods[current_method].worst_checks=check_counter;
			result_methods[current_method].total_checks=check_counter;
			result_methods[current_method].best_swap=swap_counter;
			result_methods[current_method].worst_swap=swap_counter;
			result_methods[current_method].total_swap=swap_counter;
			}
		else{
			if (result_methods[current_method].best_time>time_gap){
				result_methods[current_method].best_time=time_gap;
				}
			if (result_methods[current_method].worst_time<time_gap){
				result_methods[current_method].worst_time=time_gap;
				}
			result_methods[current_method].total_time=result_methods[current_method].total_time+time_gap;
			if (result_methods[current_method].best_checks>check_counter){
				result_methods[current_method].best_checks=check_counter;
				}
			if (result_methods[current_method].worst_checks<check_counter){
				result_methods[current_method].worst_checks=check_counter;
				}
			result_methods[current_method].total_checks=result_methods[current_method].total_checks+check_counter;
			if (result_methods[current_method].best_swap>swap_counter){
				result_methods[current_method].best_swap=swap_counter;
				}
			if (result_methods[current_method].worst_swap<swap_counter){
				result_methods[current_method].worst_swap=swap_counter;
				}
			result_methods[current_method].total_swap=result_methods[current_method].total_swap+swap_counter;
			}
		
//Execução para o quick sort.
		copy_vector(vector,reserve_vector);
		finish_time_counter=0;
		start_time_counter=0;
		check_counter=0;
		swap_counter=0;
		current_method=4;
		start_counter();
		quicksort(vector);
		end_counter();
		time_gap=finish_time_counter-start_time_counter;
		if (!counter){
			result_methods[current_method].best_time=time_gap;
			result_methods[current_method].worst_time=time_gap;
			result_methods[current_method].total_time=time_gap;
			result_methods[current_method].best_checks=check_counter;
			result_methods[current_method].worst_checks=check_counter;
			result_methods[current_method].total_checks=check_counter;
			result_methods[current_method].best_swap=swap_counter;
			result_methods[current_method].worst_swap=swap_counter;
			result_methods[current_method].total_swap=swap_counter;
			}
		else{
			if (result_methods[current_method].best_time>time_gap){
				result_methods[current_method].best_time=time_gap;
				}
			if (result_methods[current_method].worst_time<time_gap){
				result_methods[current_method].worst_time=time_gap;
				}
			result_methods[current_method].total_time=result_methods[current_method].total_time+time_gap;
			if (result_methods[current_method].best_checks>check_counter){
				result_methods[current_method].best_checks=check_counter;
				}
			if (result_methods[current_method].worst_checks<check_counter){
				result_methods[current_method].worst_checks=check_counter;
				}
			result_methods[current_method].total_checks=result_methods[current_method].total_checks+check_counter;
			if (result_methods[current_method].best_swap>swap_counter){
				result_methods[current_method].best_swap=swap_counter;
				}
			if (result_methods[current_method].worst_swap<swap_counter){
				result_methods[current_method].worst_swap=swap_counter;
				}
			result_methods[current_method].total_swap=result_methods[current_method].total_swap+swap_counter;
			}
		
		counter++;
		if (counter<MAX_RAND_TESTS){
			set_random_values(vector);
			copy_vector(reserve_vector,vector);
			}
		
		}
	
	counter=0;
	while(counter<5){
		result_methods[counter].average_time=result_methods[counter].total_time/MAX_RAND_TESTS;
		result_methods[counter].average_checks=result_methods[counter].total_checks/MAX_RAND_TESTS;
		result_methods[counter].average_swap=result_methods[counter].total_swap/MAX_RAND_TESTS;
		counter++;
		}

// Impressão de resultados diversos.
	printf("method\t\tav. time\tav. check\tav. swap\n");
	printf("bubble\t\t%f\t%10d\t%10d\n",result_methods[0].average_time,result_methods[0].average_checks,result_methods[0].average_swap);
	printf("insertion\t%f\t%10d\t%10d\n",result_methods[1].average_time,result_methods[1].average_checks,result_methods[1].average_swap);
	printf("selection\t%f\t%10d\t%10d\n",result_methods[2].average_time,result_methods[2].average_checks,result_methods[2].average_swap);
	printf("merge\t\t%f\t%10d\t%10d\n",result_methods[3].average_time,result_methods[3].average_checks,result_methods[3].average_swap);
	printf("quick\t\t%f\t%10d\t%10d\n",result_methods[4].average_time,result_methods[4].average_checks,result_methods[4].average_swap);
	
	printf("\n");
	
	printf("method\t\tworst time\tworst check\tworst swap\n");
	printf("bubble\t\t%f\t%10d\t%10d\n",result_methods[0].worst_time,result_methods[0].worst_checks,result_methods[0].worst_swap);
	printf("insertion\t%f\t%10d\t%10d\n",result_methods[1].worst_time,result_methods[1].worst_checks,result_methods[1].worst_swap);
	printf("selection\t%f\t%10d\t%10d\n",result_methods[2].worst_time,result_methods[2].worst_checks,result_methods[2].worst_swap);
	printf("merge\t\t%f\t%10d\t%10d\n",result_methods[3].worst_time,result_methods[3].worst_checks,result_methods[3].worst_swap);
	printf("quick\t\t%f\t%10d\t%10d\n",result_methods[4].worst_time,result_methods[4].worst_checks,result_methods[4].worst_swap);
	
	printf("\n");
	
	printf("method\t\tbest time\tbest check\tbest swap\n");
	printf("bubble\t\t%f\t%10d\t%10d\n",result_methods[0].best_time,result_methods[0].best_checks,result_methods[0].best_swap);
	printf("insertion\t%f\t%10d\t%10d\n",result_methods[1].best_time,result_methods[1].best_checks,result_methods[1].best_swap);
	printf("selection\t%f\t%10d\t%10d\n",result_methods[2].best_time,result_methods[2].best_checks,result_methods[2].best_swap);
	printf("merge\t\t%f\t%10d\t%10d\n",result_methods[3].best_time,result_methods[3].best_checks,result_methods[3].best_swap);
	printf("quick\t\t%f\t%10d\t%10d\n",result_methods[4].best_time,result_methods[4].best_checks,result_methods[4].best_swap);
	}

// SIZE_VECTOR e MAX_RAND_TESTS devem ser alterados convenientemente.
int main(){
	int vector[SIZE_VECTOR];
	int reserve_vector[SIZE_VECTOR];
	check_counter=0;
	swap_counter=0;
		
	printf("Parte 1: checagem com um vetor ordenado de forma crescente.\n");
	printf("Tamanho do vetor: %d.\n",SIZE_VECTOR);
	set_crescent_values(vector);
	copy_vector(reserve_vector,vector);
	compare_with_ordered(vector,reserve_vector);

	printf("Parte 2: checagem com um vetor ordenado de forma decrescente.\n");
	printf("Tamanho do vetor: %d.\n",SIZE_VECTOR);
	set_decrescent_values(vector);
	copy_vector(reserve_vector,vector);
	compare_with_ordered(vector,reserve_vector);
	
	printf("Parte 3: checagem com vetores ordenados de forma aleatória.\n");
	printf("Tamanho do vetor: %d. Número de checagens: %d.\n",SIZE_VECTOR,MAX_RAND_TESTS);
	set_random_values(vector);
	copy_vector(reserve_vector,vector);
	compare_with_random(vector,reserve_vector);
	
	printf("Fim das checagens.\n");	
	return 0;
	}
