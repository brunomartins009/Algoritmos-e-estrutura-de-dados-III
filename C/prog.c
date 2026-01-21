#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float **alocaMatriz(int m, int colunas){
	float **Matriz;
	int i;

	Matriz = (float **)malloc(sizeof(float *)*m);
	if(Matriz == NULL){
		printf("Memoria insuficiente\n");
		exit(1);
	}
	for(i=0;i<m;i++){
		Matriz[i] = (float *)malloc(sizeof(float)*colunas);
		if(Matriz == NULL){
			printf("Memoria insuficiente\n");
			exit(1);
		}
	}
	printf("Matriz de %d linhas alocada\n", i);
	return Matriz;
}

void liberaMatriz(float **M, int m){
	int i;
	for(i=0;i<m;i++)
		free(M[i]);
	printf("Matriz de %d linhas desalocada\n", i);
	free(M);
}

float **leMatriz(char arq[], int m){
	float **M;
	FILE *fp;
	int i, j;

	fp = fopen(arq, "r");
	M = alocaMatriz(m, 3);
	for(i=0; i<m; i++)
		for(j=0; j<3; j++)
			fscanf(fp,"%f", &M[i][j]);
	puts("matriz preenchida");
	fclose(fp);
	return M;
}

float **calculaPesos(float **Pesos, float **M, int m, int*v1, int *v2, int *v3, float *max){
	Pesos = alocaMatriz(m, m);
	int i, j;
	float max1=0, max2=0;

	for(i=0; i<m; i++){
		for(j=i; j<m; j++){
			Pesos[i][j] = sqrt( ((M[i][1]-M[j][1]) * (M[i][1]-M[j][1]))  +  ((M[i][2]-M[j][2]) * (M[i][2]-M[j][2])) );
			Pesos[j][i] = Pesos[i][j];

			if(Pesos[i][j] > max1){
				max1 = Pesos[i][j];
				*v1 = i+1;
				*v2 = j+1;
			}
		}
	}
	i=*v1-1;
	for(j=0;j<m;j++){
		if(Pesos[i][j]>max2 && Pesos[i][j]<max1){
			max2 = Pesos[i][j];
			*v3 = j+1;
		}
	}
	/**max = max1+max2;
	for(i=0; i<m; i++){
		for(j=0; j<m; j++)
			printf("%.3f ", Pesos[i][j]);
		puts("");
	}*/

	return Pesos;
}

void programa(char arquivo[]){
	FILE *p;
	int linhas=0, v1=0, v2=0, v3=0;
	char c;
	float **matrizGrafo;
	float **matrizPesos;
	float pesoSubgrafo;
	printf("iniciando função para o arquivo %s\n", arquivo);
	p = fopen(arquivo,"r");
	if(p==NULL)
		printf("arquivo não encontrado!\n");
	else
	{
		linhas=1;
		do{
			c = fgetc(p);
			if(feof(p))
				break;
			if (c=='\n')
				linhas++;
		} while (1);
		fclose(p);
		int arestas = (linhas*(linhas-1))/2;
		printf("o grafo tem %d linhas e %d arestas\n", linhas, arestas);

		matrizGrafo = leMatriz(arquivo, linhas);
		matrizPesos = calculaPesos(matrizPesos, matrizGrafo, linhas, &v1, &v2, &v3, &pesoSubgrafo);
		printf("%d %d %d\n%f\n",v1,v2,v3, pesoSubgrafo);
		liberaMatriz(matrizPesos, linhas);
		liberaMatriz(matrizGrafo, linhas);

		printf("função encerrada\n\n");
	}
}

int main()
{
	char arquivo[100];
	// programa("a28.txt");
	// programa("att48.txt");
	// programa("att532.txt");
	// programa("berlin52.txt");
	// programa("bier127.txt");
	// programa("brd14051.txt");
	programa("burma14.txt");
	// programa("d15112.txt");
	// programa("eil101.txt");
	return 0;
}