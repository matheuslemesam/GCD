#include <stdio.h>

// Cabeçalhs
void selection_sort(int numeros[], int l, int r);

int less(int a, int b);

void exch(int a, int b);

int main (void){

    int vetor[999]; //já que o vetor pode ir só até 1000 elementos.
    int ino;  

    for (ino=0; scanf("%d", &vetor[ino]) != EOF; ino++) {
        selection_sort(vetor, 0, ino);
    }


    for (int io = 0; io < ino; io++){
        printf("%d ", vetor[io]);
    }

    return 0;
}

int less(int a, int b) { //função que verifica se a é menor que b.
    return a < b;
}

void exch(int a, int b) { //função que troca os valores de a e b.
    int t = a;
    a = b;
    b = t;
}

void selection_sort(int numeros[], int l, int r) { //vetor, item mais a esquerda e item mais a direita. 
            for (int i = l; i < r; i++) { //i começa no item mais a esquerda e vai até o item mais a direita.
            //Nesse caso, item l = 0 e item r = 4. 
            int menor = i;
            for (int j = i+1; j <= r; j++) { //j começa no próximo item a esquerda de l e vai até o item mais a direita.
                if (less(numeros[j], numeros[menor])) menor = j; //se o item j for menor que o item menor, menor recebe j.
            }
            exch(numeros[l], numeros[menor]); //troca o valor de l p/ menor após ser verificado qual o menor.
            selection_sort(numeros, l+1, r); //chama a função novamente, mas com l+1, ou seja, o próximo item a esquerda.
            } 
}