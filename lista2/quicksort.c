#include <stdio.h>

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

void quicksort(int vetor[], int l, int r){
    int j;
    if(r <= l){
        return;
    }
    j = separa(vetor, l, r);
    quicksort(vetor, l, j-1);
    quicksort(vetor, j+1, r);
}

int main(){




    return 0;
}