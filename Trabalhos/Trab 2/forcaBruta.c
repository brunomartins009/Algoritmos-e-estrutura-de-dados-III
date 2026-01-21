#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b)? a : b;
}

int mochila_forca_bruta(int W, int wt[], int val[], int n) {
    if (n == 0 || W == 0) {
        return 0;
    }
    if (wt[n-1] > W) {
        return mochila_forca_bruta(W, wt, val, n-1);
    }
    return max(val[n-1] + mochila_forca_bruta(W-wt[n-1], wt, val, n-1), mochila_forca_bruta(W, wt, val, n-1));
}

int main() {
    int n, W;
    scanf("%d %d", &n, &W);
    int val[n], wt[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &val[i], &wt[i]);
    }
    printf("%d", mochila_forca_bruta(W, wt, val, n));
    return 0;
}
