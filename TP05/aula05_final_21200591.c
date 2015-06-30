#include<stdio.h>
#include<stdlib.h>

/* Universidade Federal do Amazonas - Ufam
 * Instituto de Computação - IComp
 * Luan de Freitas Uchôa - 21200591
 */

// Aula 05 - Campo Minado - 30/05/2014

int main(int argc, char *argv[]){
	if (argc<2){
		printf("falta o nome do arquivo\n");
		return 0;
		}
	if (argc>2){
		printf("muitos argumentos na linha de comando\n");
		return 0;
		}
	int lines, columns,counter,counter2,counter_mines,i,j;
	char **matrix;
	FILE *archive;
	archive=fopen(argv[1],"r");
	fscanf(archive,"%d %d\n",&lines,&columns);
	matrix=(char**)malloc(sizeof(char*)*lines);
	for (counter=0;counter<lines;counter++){
		matrix[counter]=(char*)malloc(sizeof(char)*columns);
		}
	
	// Lê a disposição das minas de um arquivo.
	for (counter=0;counter<lines;counter++){
		for (counter2=0;counter2<columns;counter2++){
			matrix[counter][counter2] = fgetc(archive);
			if (matrix[counter][counter2]=='\n') matrix[counter][counter2]=fgetc(archive);
			}
		}

	// Checa a disposição das minas e imprime.
	for (counter=0;counter<lines;counter++){
		for (counter2=0;counter2<columns;counter2++){
			if(matrix[counter][counter2]=='*') printf(" *");
			else{
				counter_mines=0;
				for(i=counter-1;i<counter+2;i++){
					for(j=counter2-1;j<counter2+2;j++){
						if (i>=0&&j>=0&&i<lines&&j<columns){
							if (matrix[i][j]=='*') counter_mines++;
							}
						}
					}
				printf(" %d",counter_mines);
				}
			}
		printf("\n");
		}
	return 0;
	}
