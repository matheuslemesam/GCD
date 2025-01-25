#include <stdio.h>

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

int main(){

    int n, m;

    scanf("%d %d", &n, &m);

    int vetor[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
    }   

    buscabinaria(vetor, 0, n-1, m);
    
    return 0;
}