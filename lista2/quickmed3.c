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

int main() {
    int n;

    scanf("%d", &n);

    int vetor[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    quicksort(vetor, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}