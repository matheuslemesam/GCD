#include <stdio.h>

#define less(A, B) ((A) < (B))
#define exch(A, B) { int t = A; A = B; B = t; }

int medianade3(int *vetor, int l, int r) {
    if (r - l <= 2) {
        if (less(vetor[r], vetor[l])) {
            exch(vetor[l], vetor[r]);
        }
        return r;
    }

    int mediana = (l + r) / 2;

    if (less(vetor[mediana], vetor[l])) {
        exch(vetor[mediana], vetor[l]);
    }
    if (less(vetor[r], vetor[l])) {
        exch(vetor[r], vetor[l]);
    }
    if (less(vetor[r], vetor[mediana])) {
        exch(vetor[r], vetor[mediana]);
    }

    exch(vetor[mediana], vetor[r - 1]);
    return r - 1; 
}

int separa(int *vetor, int l, int r) {
    int pivo = medianade3(vetor, l, r);
    int i = l, j = r - 1;

    while (1) {
        while (less(vetor[++i], vetor[pivo]));
        while (less(vetor[pivo], vetor[--j]));
        if (i >= j) break;
        exch(vetor[i], vetor[j]);
    }
    exch(vetor[i], vetor[pivo]);
    return i;
}

void quicksort(int vetor[], int l, int r) {
    if (r <= l) {
        return;
    }
    int j = separa(vetor, l, r);
    quicksort(vetor, l, j - 1);
    quicksort(vetor, j + 1, r);
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

int main (){

    int n, m, buscados, dados;

    scanf("%d %d", &n, &m);

    int vetor[n], vetor2[m];

    for (dados = 0; dados<n; dados++) {
        scanf("%d", &vetor[dados]);
    }

    for (buscados = 0; buscados<m; buscados++) {
        scanf("%d", &vetor2[buscados]);
    }

    quicksort(vetor, 0, n-1);
    
    for (buscados = 0; buscados<m; buscados++) {
        int indicedoelem = buscabinaria(vetor, dados, n, buscados);
        printf("%d\n", indicedoelem);
    }

    return 0;
}