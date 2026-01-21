#include<bits/stdc++.h> 
using namespace std;

bool cmp(pair<double, int>& a, pair<double, int>& b){
    return a.first > b.first;
}


int mochila_gulosa(int W, float wt[], float val[], int n) {
   vector<pair<double, int>> valor_peso; 
   for (int i = 0; i < n; i++) {
       valor_peso.push_back(make_pair((double)val[i]/(double)wt[i], i)); 
   }
   sort(valor_peso.begin(), valor_peso.end(), cmp); 

   float peso_atual = 0; 
   float valor_atual = 0; 
   for (int i = 0; i < n; i++) {
       if (peso_atual + wt[valor_peso[i].second] <= W) { 
           peso_atual += wt[valor_peso[i].second]; 
           valor_atual += val[valor_peso[i].second]; 
       }
   }
   return valor_atual; 
}


int main(){
    ifstream arquivo("knapPI_3_10000_1000_1"); // abre o arquivo "entrada.txt"
    int n, W;
    arquivo >> n >> W; // lê os valores de n e W do arquivo
    float val[n], wt[n]; 
    for(int i=0; i<n; i++) arquivo >> val[i] >> wt[i]; // lê os valores de val e wt do arquivo

    arquivo.close(); // fecha o arquivo

    cout << mochila_gulosa(W, wt, val, n); 
    return 0; 
}











    return 0;
}```
Se o número de itens disponíveis for igual a zero ou a capacidade máxima da mochila for igual a zero, a função retorna zero, pois não é possível colocar itens na mochila.

```if (wt[n - 1] > W) { 
    return mochila_forca_bruta(W, wt, val, n - 1);
}```
Se o peso do último item disponível for maior do que a capacidade máxima da mochila, então não é possível colocar esse item na mochila. Nesse caso, a função chama a si mesma novamente, mas agora com n-1 (pois o último item não pode ser usado) e retorna o valor resultante.

```return max(val[n - 1] + mochila_forca_bruta(W - wt[n - 1], wt, val, n - 1), mochila_forca_bruta(W, wt, val, n - 1));```
Aqui ocorre a maior parte da lógica do algoritmo. A função chama a si mesma duas vezes:
- A primeira chamada usa o valor atual de n-1 (ignorando o último item), diminui a capacidade máxima da mochila em wt[n-1] (já que o item está sendo adicionado na mochila), e adiciona o valor do último item (val[n-1]) ao valor resultante. Essa chamada recursiva busca a solução ótima para a capacidade restante da mochila, após adicionar o item.
- A segunda chamada usa o valor atual de n-1 (ignorando o último item) e a capacidade máxima original da mochila (já que o item não está sendo adicionado na mochila). Essa chamada recursiva busca a solução ótima sem adicionar o item.

A função retorna o valor máximo encontrado pelas duas chamadas recursivas, usando a função "max".


