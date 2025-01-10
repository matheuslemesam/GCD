#include <stdio.h>

int buscabinaria (int numeros[], int qntdindex, int numeroprocurado);

void selection_sort(int numeros[], int l, int r);

#define less(A, B) ((A) < (B))

#define exch(A, B) { int t = A; A = B; B = t; }

int main (){

    int vetor[999];
    int n=0;
    int compararcom;

    for (n = 0; scanf("%d", &vetor[n]) != EOF; n++){}

    selection_sort(vetor, 0, n-1);
    
    scanf("%d", &compararcom);

    buscabinaria(vetor[n], n, compararcom);

    return 0;
}

int buscabinaria (int numeros[], int qntdindex, int numeroprocurado){
    int indexcentral;
    
    //definir o index central
    if (qntdindex%2==0){
        indexcentral = qntdindex/2;
    }
    else{
        indexcentral = (qntdindex-1)/2;
    }

    //for p/ iterativa

    if (numeroprocurado == numeros[indexcentral]){
        return indexcentral;
    }

    else if (numeroprocurado > numeros[indexcentral]){
        if (indexcentral%2==0){
            indexcentral = indexcentral + (indexcentral-1)/2;
        }
        else{
            indexcentral = indexcentral + indexcentral/2;
        }
    }
    else {
        if (indexcentral%2==0){
            indexcentral = (indexcentral-1)/2;
        }
        else{
            indexcentral/2;
        }
    }
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