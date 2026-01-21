#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int peso;
    int beneficio;
} type_item;

void algoritmo_1(type_item *items, int n, int capacidade) {
    int i, j, k, l;
    int max_beneficio = 0;
    int atual_beneficio = 0;
    int atual_peso = 0;
    int *solucao = (int *)malloc(n * sizeof(int));
    int *melhor_solucao = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        solucao[i] = 0;
        melhor_solucao[i] = 0;
    }

    for (i = 0; i < (1 << n); i++) {
        atual_beneficio = 0;
        atual_peso = 0;

        for (j = 0; j < n; j++) {
            if (i & (1 << j)) {
                atual_beneficio += items[j].beneficio;
                atual_peso += items[j].peso;
                solucao[j] = 1;
            } else {
                solucao[j] = 0;
            }
        }

        if (atual_peso <= capacidade && atual_beneficio > max_beneficio) {
            max_beneficio = atual_beneficio;
            for (k = 0; k < n; k++) {
                melhor_solucao[k] = solucao[k];
            }
        }
    }

    printf("Solucao:\n");
    for (l = 0; l < n; l++) {
        printf("%d ", melhor_solucao[l]);
    }
    printf("\nBeneficio Total: %d\n", max_beneficio);

    free(solucao);
    free(melhor_solucao);
}

int algoritmo_2(type_item *items, int n, int capacidade) {
    // Caso base
    if (n == 0 || capacidade == 0) {
        return 0;
    }

    // Verifica se o item n/2 cabe na mochila
    if (items[n/2].peso > capacidade) {
        // O item n/2 não cabe na mochila, então só consideramos os itens de 1 a n/2-1
        return algoritmo_2(items, n/2, capacidade);
    } else {
        // O item n/2 pode ou não estar na mochila
        int beneficio_com_n2 = items[n/2].beneficio + algoritmo_2(items, n/2, capacidade - items[n/2].peso);
        int beneficio_sem_n2 = algoritmo_2(items + n/2 + 1, n - n/2 - 1, capacidade);

        // Retorna o benefício máximo entre considerar ou não o item n/2 na mochila
        return (beneficio_com_n2 > beneficio_sem_n2) ? beneficio_com_n2 : beneficio_sem_n2;
    }
}

void algoritmo_3(type_item *items, int n, int capacidade) {
    int i, j, capacidade_restante;
    int *mochila = (int *)calloc(n, sizeof(int));

    // calcula a relação benefício-peso de cada item
    float *ratio = (float *)malloc(n * sizeof(float));
    for (i = 0; i < n; i++) {
        ratio[i] = (float) items[i].beneficio / items[i].peso;
    }

    // ordena os itens em ordem decrescente de relação benefício-peso
    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                swap_float(&ratio[i], &ratio[j]);
                swap_type_item(&items[i], &items[j]);
            }
        }
    }

    // adiciona os itens à mochila enquanto há espaço disponível
    capacidade_restante = capacidade;
    for (i = 0; i < n; i++) {
        if (items[i].peso <= capacidade_restante) {
            mochila[i] = 1;
            capacidade_restante -= items[i].peso;
        } else {
            break;
        }
    }

    // imprime a solução
    int beneficio_total = 0;
    for (i = 0; i < n; i++) {
        if (mochila[i]) {
            printf("Item %d adicionado à mochila\n", i+1);
            beneficio_total += items[i].beneficio;
        }
    }
    printf("Benefício total: %d\n", beneficio_total);

    free(mochila);
    free(ratio);
}



void imprimir_items(type_item *items, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Peso: %d, Beneficio: %d\n", items[i].peso, items[i].beneficio);
    }
}

type_item *ler_items(char *filename, int *n_items, int *capacidad) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        puts("Não foi possível abrir o arquivo");
        exit(0);
    }

    fscanf(fp, "%d %d", n_items, capacidad);
    printf("Número de elementos: %d, Capacidade: %d\n", *n_items, *capacidad);

    type_item *items = (type_item *)malloc(*n_items * sizeof(type_item));

    for (int i = 0; i < *n_items; i++) {
        fscanf(fp, "%d %d", &items[i].peso, &items[i].beneficio);
    }

    fclose(fp);

    return items;
}


int main(int argc, char *argv[]) {
    int n_items, capacidad;

    if (argc != 3) {
        printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
        return 1;
    }

    type_item *items = ler_items(argv[1], &n_items, &capacidad);
    imprimir_items(items, n_items);

    if (argv[2][0] == '1') {
        algoritmo_1(capacidad, items, n_items);
    } else if (argv[2][0] == '2') {
        algoritmo_2(capacidad, items, n_items);
    } else if (argv[2][0] == '3') {
        algoritmo_3(capacidad, items, n_items);
    } else {
        printf("Escolha um algoritmo entre 1 e 3\n");
        return 1;
    }
    free(items);
    return 0;
}
