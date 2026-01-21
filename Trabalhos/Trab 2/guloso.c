#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double first;
    int second;
} pair;

int cmp(const void *a, const void *b) {
    pair *pa = (pair *)a;
    pair *pb = (pair *)b;
    return pb->first > pa->first ? 1 : -1;
}

int mochila_gulosa(int W, int wt[], int val[], int n) {
    pair valor_peso[n];
    for (int i = 0; i < n; i++) {
        valor_peso[i].first = (double)val[i] / (double)wt[i];
        valor_peso[i].second = i;
    }
    qsort(valor_peso, n, sizeof(pair), cmp);

    int peso_atual = 0;
    int valor_atual = 0;
    for (int i = 0; i < n; i++) {
        if (peso_atual + wt[valor_peso[i].second] <= W) {
            peso_atual += wt[valor_peso[i].second];
            valor_atual += val[valor_peso[i].second];
        }
    }
    return valor_atual;
}

int main() {
    int n, W;
    scanf("%d %d", &n, &W);

    int val[n], wt[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &val[i], &wt[i]);
    }

    printf("%d", mochila_gulosa(W, wt, val, n));
    return 0;
}
