#include <stdio.h>

#define less(A, B) ((A) < (B))

#define exch(A, B) { int t = A; A = B; B = t; }

void quicksort(int vetor[], int l, int r);

int separa(int *vetor[], int l, int r);

int buscabinaria(int *vetor, int l, int r, int x);

int main (){

    int n, m, buscados, dados;

    scanf("%d %d", &n, &m);

    int vetor[n];

    for (dados = 0; dados<n; dados++) {
        scanf("%d", &vetor[dados]);
    }

    for (buscados = 0; buscados<m; buscados++) {
        scanf("%d", &vetor[buscados]);
    }

    quicksort(vetor, 0, n-1);
    
    for (buscados = 0; buscados<m; buscados++) {
        int indicedoelem = buscabinaria(vetor, n, dados, buscados);
        printf("%d\n", indicedoelem);
    }


    return 0;
}

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

int buscabinaria(int *vetor, int l, int r, int x) {
    if (r < l) {
        return -1;
    }

    int m = l+ (r-l) / 2; //para não dar overflow

    if (vetor[m] == x) {
        return m;
    }

    if (vetor[m] < x) {
        return buscabinaria(vetor, m + 1, r, x);
    }

    return buscabinaria(vetor, l, m - 1, x);
}