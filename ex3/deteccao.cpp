//Usei a lógica 3 pelo fato da imagem estar mais limpa.

// cd /mnt/c/users/mikel/onedrive/gcd/ex3                           meu caminho
//g++ deteccao.cpp centroide.o -o main.exe `pkg-config --cflags --libs opencv4`

#include <opencv2/opencv.hpp>
#include <stdio.h>
//#include "centroide.h"
#include <vector> //lib de vetores p/ poder usar bidimensional

//struct para definir os pontos do centroide
typedef struct {
    double x;
    double y;
} Centroide;

//protótipo da função
Centroide calcularcentroide(double *x, double *y, double *areas, int n);

//definição da função
Centroide calcularcentroide(double *x, double *y, double *areas, int n) {
    double somax = 0.0, somay = 0.0, areatot = 0.0;
    for (int i = 0; i < n; i++) {
        somax += x[i] * areas[i];
        somay += y[i] * areas[i];
        areatot += areas[i];
    }
    Centroide centroide = {0.0, 0.0};
    if (areatot != 0) {
        centroide.x = somax / areatot;
        centroide.y = somay / areatot;
    }
    return centroide;
}

int main() {
    
    using namespace cv; // namespace para não precisar ficar repetindo 
    using namespace std;

    Mat image = imread("images/luz.jpg"); // Carregar a imagem

    if (image.empty()) { // Verificar se a imagem foi carregada corretamente ou se o caminho está errado
        printf("Erro ao carregar a imagem!\n"); // Usando fprintf para erro
        return -1;
    }

    // Convertendo a imagem para escala de cinza
    Mat peb;
    cvtColor(image, peb, COLOR_BGR2GRAY);

    int minimo = 240; // Tons próximos ao branco
    int maximo = 255; // Branco puro

    Mat mascara;
    inRange(peb, Scalar(minimo), Scalar(maximo), mascara);

    Mat mascarainversa;
    bitwise_not(mascara, mascarainversa);

    // Aplicar a máscara à imagem original
    Mat resultado;
    bitwise_and(peb, peb, resultado, mascara);
    
    // Converter a imagem para binária para o valor do pixel ser apenas 255 p/ branco ou 0 p/ preto;
    Mat binaria;
    threshold(peb, binaria, 128, 255, THRESH_BINARY); //função; img de entrada; img de saída; valor que determina o ponto de separação entre os pixels altos e baixos, nesse caso todos os pixels acima de 128 serão brancos; valor que será atribuido a todos mais altos que o limiar; tipo de threshold.

    vector<vector<Point>> contornos; // vetor dentro de um vetor
    //vector<Vec4i>hierarquia; //armazenar infos sobre a hierarquia, não tem necessidade de usar com a RETR_EXTERNAL
    
    // detectar contornos da imagem binária.
    findContours(binaria, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //função; imagem binária; vetor de vetores que armazenará os contornos; modo de recuperação de contornos, os mais comuns são: RETR_EXTERNAL para contornos externos, RETR_LIST para todos sem hierarquia, RETR_TREE para todos com hierarquia; método de aproximação de contornos, mais comuns: CHAIN_APPROX_SIMPLE para armazenar os pontos extremos do contorno, CHAIN_APPROX_NONE para armazenar todos os pontos do contorno; offset, opcional, um ponto que pode ser adicionado a todos os pontos de um contorno.

    // Verificar se há contornos detectados
    if (contornos.empty()) {
        printf("Nenhum contorno detectado!\n");
        return -1;
    }

     // Declarar arrays para armazenar coordenadas x, y e áreas
    double x[contornos.size()];
    double y[contornos.size()];
    double areas[contornos.size()];
    double areatot = 0.0;
    int n = contornos.size();

    // Calcular a área do raio luminoso.
    for(size_t i=0; i<contornos.size(); i++)//size_t funcionará como módulo; contornos.size retorna o valor dos contornos encontrados
    {
    areas[i] = contourArea(contornos[i]); //calcula a área em cada ponto
    //contourArea, funciona com qualquer contorno; vetor de pontos que representam o contorno, obtidos geralmente com a função findContours; Parâmetro opcional o valor padrão é false, se true: calcula a área considerando a orientação de contorno.
    areatot += areas[i]; //armazena as áreas
    Moments m = moments(contornos[i]); //moments; utilizada para calcular momentos de uma imagem ou contorno; m00 = momento de ordem 0, representa a área do contorno; m10 = momento de ordem em relação ao eixo x, usado pra calcular a cord x; m01 = momento de ordem em relação ao eixo y, usado pra calcular a cord y;
    if (m.m00 != 0){ // verificar se a área do momento é dif de 0
        x[i] = m.m10 / m.m00; //cord x do centroide
        y[i] = m.m01 / m.m00; //cord y do centroide
    }
    else{ //caso a área do momento for 0
        x[i] = 0;
        y[i] = 0;
    }
    //printf("Área do contorno %zu: %.2f\n", i, area); // Imprime a área com duas casas decimais, %zu imprime size_t
    }

    //chamando a função calcular centroide
    Centroide centrodemassa = calcularcentroide(x, y, areas, n);

    printf("A área do raio é: %.2f\n", areatot);

    printf("As coordenadas do centróide são: (%.2f, %.2f)\n", centrodemassa.x, centrodemassa.y);

    imshow("Img Og", image); // mostrar a imagem original

    imshow("Img com raio destacado", resultado); // mostrar a imagem cinza

    waitKey(0); // esperar até que uma tecla seja pressionada

    destroyAllWindows(); // Fechar todas as janelas criadas com o imshow

    return 0;
}