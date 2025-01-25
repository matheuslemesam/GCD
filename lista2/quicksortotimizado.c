#include <stdio.h>

#define less(A, B) ((A) < (B))
#define exch(A, B) { int t = A; A = B; B = t; }

void quicksort(int vetor[], int l, int r){
    int pivo;
    if(r <= l){
        return;
    }
    pivo = separa(vetor, l, r);
    quicksort(vetor, l, pivo-1);
    quicksort(vetor, pivo+1, r);
}

int separa(int *vetor[], int l, int r){
    int pivopos;
    int tamanho = r-l+1;
    int pivo = vetor[r];
    int *menores[] = malloc(sizeof(int)*tamanho); //malloc serve para reservar espaço na memória de tamanho especificado
    int *maiores[] = malloc(sizeof(int)*tamanho);
    int imenor =0, imaior = 0;

    for(int i = l; i <= r; i++){
        if(less(vetor[i], pivo)){
            menores[imenor++] = vetor[i];
        }
        else{
            maiores[imaior++] = vetor[i];
        }
    }

    for(int i = 0; i < imenor; i++){
        vetor[i++] = menores[i];
    }

    vetor[i] = pivo;
    pivopos = i;
    i++;

    for(int j = 0; j < imaior; j++){
        vetor[i++] = maiores[j];
    }

    free(menores);
    free(maiores);
    return pivopos;
}

int main(){

    int n;

    scanf("%d", &n);

    int vetor[n];

    for (int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }

    quicksort(vetor, 0, n-1);

    for (int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }

    return 0;
}