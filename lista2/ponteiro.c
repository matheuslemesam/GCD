#include <stdio.h>

void exch(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int main (){
    int a = 1;
    int b = 2;

    exch(&a, &b);

    printf("%d %d\n", a, b);

    return 0;
}