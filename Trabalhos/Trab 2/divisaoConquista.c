#include<stdio.h>
#include<stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int mochila_divisao_conquista(int W, int wt[], int val[], int n) {
    if (n == 0 || W == 0) {  
        return 0;
    }
    if (wt[n-1] > W) {
        return mochila_divisao_conquista(W, wt, val, n-1);
    }
    return max(val[n-1] + mochila_divisao_conquista(W-wt[n-1], wt, val, n-1), mochila_divisao_conquista(W, wt, val, n-1));
}

int main(){
    int n, W;
    scanf("%d %d", &n, &W);
    int *val = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    for(int i=0; i<n; i++) scanf("%d %d", &val[i], &wt[i]);
    printf("%d", mochila_divisao_conquista(W, wt, val, n));
    free(val);
    free(wt);
    return 0;
}
