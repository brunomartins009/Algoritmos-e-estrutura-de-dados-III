#include <stdio.h>
#include <stdlib.h>

int contador(int count){
    int caracter;
    FILE *arq;
    arq = fopen("grafos.txt", "rt");
    if (arq == NULL){
        printf("Arq. não encontrado\n");
        return;
    }
    do{
        caracter = fgetc(arq);
        if (caracter == '\n'){
            count++;
        }
    }while(caracter != EOF);
    return (count);
}

int **AlocaMatriz(int m, int n){
  int **M;
  int i;
 
  M = (int **)malloc(sizeof(int *)*m);
  if(M == NULL){
    printf("Memoria insuficiente.\n");
    exit(1);
  }
  for(i = 0; i < m; i++){
    M[i] = (int *)malloc(sizeof(int)*n);
    if(M[i] == NULL){
      printf("Memoria insuficiente.\n");
      exit(1);
    }
  }
  return M;
}

int **LeMatriz(char filename[], int *m, int *n){
  int **M;
  FILE *fp;
  int mm,nn,i,j;
 
  fp = fopen("grafos.txt", "r");
  if(fp == NULL){
    printf("Erro na leitura do arquivo.\n");
    exit(1);
  }
  fscanf(fp,"%d %d",&mm,&nn);
  *m = mm;
  *n = nn;
 
  M = AlocaMatriz(mm, nn);
  for(i = 0; i < mm; i++){
    for(j = 0; j < nn; j++){
      fscanf(fp,"%d",&M[i][j]);
    }
  }
  fclose(fp);
  return M;
}

void ImprimeMatriz(int **M, int m, int n){
  int i,j;
  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      printf(" %2d ",M[i][j]);
    }
    printf("\n");
  }
}

void LiberaMatriz(int **M, int m){
  int i;
  for(i = 0; i < m; i++)
    free(M[i]);
  free(M);
}

void main () {
    int result, count = 0;
    int **A;
    int **B;
    int mB,nB,mA,nA;
    
    result = contador(count);
    printf ("O arquivo tem %d linhas!\n", result);

    A = LeMatriz("grafos.txt", &mA, &nA);
    ImprimeMatriz(A, mA, nA);
    printf("\n");
    
    
    ImprimeMatriz(B, mB, nB);
    printf("\n");
    
    LiberaMatriz(A, mA);
    LiberaMatriz(B, mB);

    return 0;
}