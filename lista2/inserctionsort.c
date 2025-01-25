#include <stdio.h>

#define less(A, B) ((A) < (B))
#define exch(A, B) { int t = A; A = B; B = t; }
#define cmpexch(A, B) { if (less(B, A)) exch(A, B); }

//Inserction Sort Otimizado

void inserctionsort(int vetor[], int l, int r){
    for (int i = r; i > l; i--){ //faz o menor elemento ir para a primeira posição.
        cmpexch(vetor[i-1], vetor[i]);
    }
    for (int i = l+2; i <= r; i++){
        int j = i;
        int tmp = vetor[j]; //guardar o valor de j.
        for(;less(tmp, vetor[j-1]); j--){ //enquanto o valor de j for menor que o valor de j-1.
            vetor[j] = vetor[j-1]; //o valor de j-1 vai para j..
        }
        vetor[j] = tmp;
    }
}

int main(){

    int vetor [49999];
    int ino = 0; //Index Não Ordenado
    int io = 0; //Index Ordenado
    
    for (ino=0; scanf("%d", &vetor[ino]) != EOF; ino++) {
    }
    printf("\n");

    inserctionsort(vetor, 0, ino-1);

    for (io = 0; io < ino; io++){
        printf("%d ", vetor[io]);
    }
    printf("\n");


    return 0;
}