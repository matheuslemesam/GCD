#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

int main (){
    
    using namespace cv;
    using namespace std;

    Mat bsb = imread("images/brasilia.jpg", IMREAD_GRAYSCALE);

    if (bsb.empty()) {
        printf("Erro ao carregar a imagem!\n");
        return -1;
    }

    int minimo = 110; 
    int maximo = 255; 

    Mat mascara;
    inRange(bsb, Scalar(minimo), Scalar(maximo), mascara);

    Mat resultado;
    bitwise_and(bsb, bsb, resultado, mascara);

    Mat bsbbi;
    threshold(bsb, bsbbi, 110, 255, THRESH_BINARY);

    vector<vector<Point>> contornos; 

    findContours(bsbbi, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); 

    if (contornos.empty()) {
        printf("Nenhum contorno detectado!\n");
        return -1;
    }

    double areatotalpx = bsbbi.total(); 

    double x[contornos.size()];
    double y[contornos.size()];
    double areas[contornos.size()];
    double areatot = 0.0;
    int n = contornos.size();

    for(size_t i=0; i<contornos.size(); i++) {

        areas[i] = contourArea(contornos[i]); 

        areatot += areas[i];

        Moments m = moments(contornos[i]);

        if (m.m00 != 0){ 
        x[i] = m.m10 / m.m00; 
        y[i] = m.m01 / m.m00; 
        }

        else{ 
        x[i] = 0;
        y[i] = 0;
        }
    
    }  

    double porcentagemAreaUrbana = (areatot / areatotalpx) * 100.0;

    printf("A área urbana na imagem é: %.2f\n", porcentagemAreaUrbana);

    imshow("Img Processada", resultado);

    waitKey(0); 

    destroyAllWindows();

    return 0;
}