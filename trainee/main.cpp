#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

int main (void) {

    using namespace cv;

    // Inicializa a câmera
    VideoCapture cap(0); // 0 é o ID da câmera padrão

    // Verifica se a câmera foi inicializada com sucesso
    if (!cap.isOpened()) {
        printf("Erro ao abrir a câmera\n");
        return -1;
    }

    vector<Mat> imagens; // Vetor dinâmico para armazenar as imagens capturadas
    int numImagens = 10; // Número de imagens a serem capturadas

    // for para capturar as imagens
    for (int i = 0; i < numImagens; ++i) {
        Mat frame;
        cap >> frame;

    // Verifica se a imagem foi capturada com sucesso
    if (frame.empty()) {
        printf("Erro ao capturar a imagem\n");
        return -1;
    }


    imagens.push_back(frame); // Adiciona a imagem capturada ao vetor

    }

    return 0;

}