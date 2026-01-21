#include<bits/stdc++.h>  // inclui todas as bibliotecas do C++ padrão
using namespace std;

/*
Esta é a função principal do algoritmo, que utiliza a recursão para percorrer todas as possíveis combinações de elementos da mochila. 
Os parâmetros da função são:
W: capacidade máxima da mochila;
wt[]: um array com os pesos de cada item;
val[]: um array com os valores de cada item;
n: o número de itens na mochila.
*/ 
int mochila_divisao_conquista(int W, int wt[], int val[], int n) {
    
   if (n == 0 || W == 0) {  // condição de parada da recursão, quando não há mais elementos ou a capacidade da mochila é zero
       return 0;  // retorna zero, pois não há mais elementos para adicionar na mochila
   }
   if (wt[n-1] > W) {  // se o peso do último elemento é maior que a capacidade restante da mochila
       return mochila_divisao_conquista(W, wt, val, n-1);  // simplesmente chama a função recursiva com o último elemento ignorado
   }
   // retorna o máximo entre a soma do valor do último elemento e a solução para a mochila com capacidade reduzida (W-wt[n-1])
   // e a solução para a mochila sem o último elemento (n-1)
   return max(val[n-1] + mochila_divisao_conquista(W-wt[n-1], wt, val, n-1), mochila_divisao_conquista(W, wt, val, n-1));
}

int main(){
    int n = 10 , W = 269;  // variáveis para armazenar o número de elementos e a capacidade da mochila
    //cin >> n >> W;  // lê o número de elementos e a capacidade da mochila
    int val[] = {55, 10, 47, 5, 4, 50, 8, 61, 85, 87}, wt[] = {95, 4, 60, 32, 23, 72, 80, 62, 65, 46};  // cria arrays para armazenar os valores e pesos dos elementos
    //for(int i=0; i<n; i++) cin >> val[i] >> wt[i];  // lê os valores e pesos de cada elemento
    cout << mochila_divisao_conquista(W, wt, val, n);  // chama a função para encontrar a solução e imprime o resultado
    return 0;
}

/*
O algoritmo de divisão e conquista para o problema da mochila é uma melhoria do algoritmo de força bruta, onde o problema
é dividido em dois subproblemas menores e independentes. A ideia é calcular a solução para metade dos elementos 
selecionados para entrar na mochila e metade dos elementos restantes e então escolher a melhor solução dentre essas duas.
Em seguida, é repetido o mesmo processo para os subproblemas até que se tenha uma única solução.

A complexidade do algoritmo de divisão e conquista para o problema da mochila é O(n*log(n)), já que o algoritmo divide o 
problema pela metade a cada chamada recursiva e cada chamada percorre todos os elementos. Isso torna o algoritmo mais 
eficiente do que o algoritmo de força bruta em casos onde n é grande.
*/