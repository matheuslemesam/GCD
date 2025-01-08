/*
quest: ordenação simples
https://moj.naquadah.com.br/contests/gcd_trainee_cdmoj2/moj-problems_ordenasimples.html

criar uma função que ordene um vetor de inteiros em ordem crescente. Utilize o algoritmo de ordenação por inserção ou seleção ou bolha.

Estudos para o código:
    Materiais:
    https://www.youtube.com/watch?v=ZjzAZdcgc0k&list=PLzZut2slkqyyUnJfIf6Izjkr6HTmsplBG

    Ordenação:
        Oque vamos ordenar? Arquivos de itens, vetores, listas. Dentro desses arquivos teremos os itens que queremos ordenar (chaves).
            Ex: em uma lista de alunos, queremos ordenar por nome, matrícula, nota, etc.

        Objetivo? Rearranjar as chaves de forma que fiquem em conformidade com a ordem estabelecida.
        O arquivo cabe na memória? Sim, então podemos usar algoritmos de ordenação interna. Se não, usamos algoritmos de ordenação externa.

        Vetores ou listas encadeadas? Vetores são mais fáceis de implementar, mas listas encadeadas são mais flexíveis. Muda a complexidade dos algoritmos de acordo com o tipo de dado.

        typedef int item; // item é a variável do tipo inteiro
        #define key(A) // se for um int retornará A, se for um struct retornará A.chave.
        #define less(A, B) // se A é menor que B (Key(A)<Key(B)), retornará 1, senão 0.
        #define exch(A, B) // troca os valores de A e B. Item temporário(t) = A; A = B; B = t;
        #define cmpxch(A, B) // troca os valores de A e B, se B for menor que A. if(less(B, A)) exch(A, B);

        Algoritmos de Ordenação estáveis: itens com chaves idênticas não mudam de posição.
            Ex: Ordenar por nota decrescente
                    Ex base:                Se estável:             Se instável(ordem aleatória):
                    Bruno 90                Bruno 90                Nina 90
                    Rose 105                Nina 90                 Bruno 90
                    Nina 90                 Rose 105                Rose 105

            Vantagens do estável? Preservação da ordem relativa, Aplicações específicas, Facilita ordenações múltiplas, Previsibilidade.

            Vantages do instável? Mais eficiente, Menos complexo, Menos memória, Mais rápido.

        Minhas considerações: Para numeros com intervalos maiores como 0 a 100, a ordenação instável é melhor já que a probabilidade de terem números repetidos é menor e ela é mais eficiente.













*/