#include <stdio.h>

// Cabeçalho
void selection_sort(int numeros[], int l, int r);

//defines
#define less(A, B) ((A) < (B))

#define exch(A, B) { int t = A; A = B; B = t; }

int main (void){

    int vetor[999]; //já que o vetor pode ir só até 1000 elementos.
    int ino = 0; //contador de elementos do vetor. (Index Não Ordenado)
    int io = 0; //contador de elementos do vetor. (Index Ordenado)
    
    //eof = ctrl+d no linux, ctrl+z no windows.
    for (ino=0; scanf("%d", &vetor[ino]) != EOF; ino++) {
    }
    printf("\n");

    selection_sort(vetor, 0, ino-1);

    for (io = 0; io < ino; io++){
        printf("%d ", vetor[io]);
    }
    printf("\n");

    return 0;
}

void selection_sort(int numeros[], int l, int r) { //vetor, item mais a esquerda e item mais a direita. 
    for (int i = l; i < r; i++) { //i começa no item mais a esquerda e vai até o item mais a direita.
    //Nesse caso, item l = 0 e item r = 4. 
        int menor = i;
        for (int j = i+1; j <= r; j++) { //j começa no próximo item a esquerda de l e vai até o item mais a direita.
            if (less(numeros[j], numeros[menor])) {
                menor = j; //se o item j for menor que o item menor, menor recebe j.
                }
            }
            exch(numeros[i], numeros[menor]); //troca o valor de l p/ menor após ser verificado qual o menor.
            //selection_sort(numeros, l+1, r); //chama a função novamente, mas com l+1, ou seja, o próximo item a esquerda.
        } 
}