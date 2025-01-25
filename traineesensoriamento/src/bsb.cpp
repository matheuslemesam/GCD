//detectar área urbana em uma foto

/*
Aplicar:

Gabor Filter para texturas de neve, grama etc

Detectar formatos circulares, retangulares e quadrados para  campos de futebol e jardim

*/

#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

int main (){
    
    using namespace cv;
    using namespace std;

    Mat bsb = imread("../images/brasilia.jpg", IMREAD_GRAYSCALE);

    if (bsb.empty()) { 
        printf("Erro ao carregar a imagem!\n"); 
        return -1;
    }

    int minimo = 110; 
    int maximo = 255; 

    Mat mascara;
    inRange(bsb, Scalar(minimo), Scalar(maximo), mascara);

    Mat mascaplicada;
    bitwise_and(bsb, bsb, mascaplicada, mascara);

    Mat gaborKernel = getGaborKernel(Size(21, 21), 5, CV_PI/4, 10, 0.5, 0, CV_32F);
    Mat imggabor;
    filter2D(bsb, imggabor, CV_8UC3, gaborKernel);

    Mat resultado;
    bitwise_and(mascaplicada, imggabor, resultado);

    Mat bsbbi;
    threshold(bsb, bsbbi, 110, 255, THRESH_BINARY);

    vector<vector<Point>> contornos; 

    findContours(bsbbi, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); 

    if (contornos.empty()) {
        printf("Nenhum contorno detectado!\n");
        return -1;
    }

    double areatotalpx = bsbbi.total();
    
    double areas[contornos.size()];
    double areatot = 0.0;
    int n = contornos.size();

    for(size_t i = 0; i < contornos.size(); i++) {
        areas[i] = contourArea(contornos[i]);
        areatot += areas[i];
    }

    double porcentagemAreaUrbana = (areatot / areatotalpx) * 100.0;

    printf("A área urbana na imagem é: %.2f%%\n", porcentagemAreaUrbana);

    imshow("Img Processada", resultado); 

    waitKey(0); 

    destroyAllWindows(); 

    return 0;
}