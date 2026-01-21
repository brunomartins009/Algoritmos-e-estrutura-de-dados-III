#include<bits/stdc++.h>  
using namespace std;

float mochila_divisao_conquista(float W, float wt[], float val[], int n) {
    
   if (n == 0 || W == 0) {  
       return 0;  
   }
   if (wt[n-1] > W) {  
       return mochila_divisao_conquista(W, wt, val, n-1);  
   }
   
   return max(val[n-1] + mochila_divisao_conquista(W-wt[n-1], wt, val, n-1), mochila_divisao_conquista(W, wt, val, n-1));
}

int main(){
    ifstream arquivo("knapPI_1_10000_1000_1");
    int n;
    float W;  
    arquivo >> n >> W;  
    float val[n], wt[n];  
    for(int i=0; i<n; i++) arquivo >> val[i] >> wt[i];  
    arquivo.close();

    cout << mochila_divisao_conquista(W, wt, val, n);  
    return 0;
}