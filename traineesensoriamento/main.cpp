#include <vector>
#include <fstream> 
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){

    // inicializa a cam
    VideoCapture cap(0, CAP_V4L2); // 0, ID da câmera padrão
    cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CAP_PROP_FPS, 30);
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));

    // debug cam
    if (!cap.isOpened()){
        for (int i = 0; i < 3; i++){
            VideoCapture cap(0);
        }

    }

    // tirar foto
    Mat frame;
    cap >> frame;

    // debug foto
    if (frame.empty()){
        while (true) {
            Mat frame;
            cap >> frame;
        }
    }

    // img para escala de cinza
    Mat framepeb;
    cvtColor(frame, framepeb, COLOR_BGR2GRAY);

    // escalar p/ máscara
    int minimo = 110; 
    int maximo = 255; 

    // criar máscara
    Mat mascara;
    inRange(framepeb, Scalar(minimo), Scalar(maximo), mascara);

    // aplicar a máscara
    Mat mascaplicada;
    bitwise_and(framepeb, framepeb, mascaplicada, mascara);

    vector<double> orientations = {0, CV_PI / 4, CV_PI / 2, 3 * CV_PI / 4};
    for (double theta : orientations){
        Mat gaborKernel = getGaborKernel(Size(31, 31), 8.0, theta, 10.0, 0.5, 0, CV_32F);
        Mat imggabor;
        filter2D(framepeb, imggabor, CV_8UC3, gaborKernel);
    }

    // juntar masc e gabor
    Mat resultado;
    bitwise_and(mascaplicada, imggabor, resultado);

    // binarizar a imagem
    Mat framebi;
    threshold(framepeb, framebi, 110, 255, THRESH_BINARY);

    // matriz de pontos de contorno
    vector<vector<Point>> contornos; 

    // encontrar contornos
    findContours(framebi, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); 

    // debug contornos
    if (contornos.empty()) {
        while (true) {
            findContours(framebi, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        }
    }

    // área total da imagem em pixels
    double areatotalpx = framebi.total();
    
    // calcular a área urbana na img
    double areas[contornos.size()];
    double areatot = 0.0;
    int n = contornos.size();

    for(size_t i = 0; i < contornos.size(); i++) {
        areas[i] = contourArea(contornos[i]);
        areatot += areas[i];

        // verifica se a área é menor que 10.800 metros quadrados
        if (areas[i] <= 10800) {
            // aproximar o contorno para verificar a forma
            vector<Point> approx;
            approxPolyDP(contornos[i], approx, arcLength(contornos[i], true) * 0.02, true);

            // verificar se é um retângulo ou quadrado
            if (approx.size() == 4) {
                double area = contourArea(approx);
                Rect boundingRect = cv::boundingRect(approx);
                double aspectRatio = (double)boundingRect.width / boundingRect.height;

                // verificar se está cercado por área urbana
                if (aspectRatio >= 0.8 && aspectRatio <= 1.2) {
                    // entra na est. de área urbana
                    areatot += area;
                }
            }
            // verificar se é um círculo
            else if (approx.size() > 4) {
                double area = contourArea(approx);
                double perimeter = arcLength(approx, true);
                double circularity = 4 * CV_PI * (area / (perimeter * perimeter));

                // verificar se está cercado por área urbana
                if (circularity > 0.7) {
                    // entra na estatística de área urbana
                    areatot += area;
                }
            }
        }
    }

    // calcular a porcentagem de área urbana
    double porcentagemAreaUrbana = (areatot / areatotalpx) * 100.0;

    // serializar os dados em um arquivo bin
    ofstream arquivoBinario("../dados/dados.bin", ios::out | ios::binary);

    // escrever a porcentagem da área urbana
    arquivoBinario.write(reinterpret_cast<char*>(&porcentagemAreaUrbana), sizeof(porcentagemAreaUrbana));

    // escrever a área urbana em pixels quadrados
    arquivoBinario.write(reinterpret_cast<char*>(&areatot), sizeof(areatot));

    // fechar o arquivo binário
    arquivoBinario.close();

    // salvar a imagem p testes
    const char* imagePath = "captured_image.jpg";
    imwrite(imagePath, resultado);

    // espera fechar a janela
    waitKey(0); 

    // fecha a janela da ft
    destroyAllWindows(); 

    return 0;
}