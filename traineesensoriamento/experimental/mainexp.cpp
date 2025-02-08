#include <vector>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace raspicam;
using namespace VideoWriter;
using namespace Mat;
using namespace ios;
using namespace ofstream;
using namespace vector;

int main() {

    for (int i = 0; i < 3; i++){
        // inicializa a câmera
        VideoCapture cap(0, CAP_V4L2);
        cap.set(CAP_PROP_FRAME_WIDTH, 1920);
        cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
        cap.set(CAP_PROP_FPS, 30);
        cap.set(CAP_PROP_FOURCC, fourcc('M', 'J', 'P', 'G'));
        if (cap.isOpened()){
            break; // se a cam abrir, sai do loop
        }
        else if (!cap.isOpened && i == 2){
            Camera.release();
            sleep(3);
            VideoCapture cap(0, CAP_V4L2);
            cap.set(CAP_PROP_FRAME_WIDTH, 1920);
            cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
            cap.set(CAP_PROP_FPS, 30);
            cap.set(CAP_PROP_FOURCC, fourcc('M', 'J', 'P', 'G'));
        }
    }

    // tira foto
    Mat frame;
    cap >> frame;

    if (frame.empty()) {
        for (int i = 0; i < 3; i++){
            Mat frame;
            cap >> frame;
            if (!frame.empty()) {
                break;
            }
        }
    }

    // converte para escala de cinza
    Mat framepeb;
    cvtColor(frame, framepeb, COLOR_BGR2GRAY);

    // pré-processa
    equalizeHist(framepeb, framepeb); // equalizar histograma
    GaussianBlur(framepeb, framepeb, Size(5, 5), 0); // suavizar

    // aplica o Gabor Kernel em múltiplas orientações
    <double> orientations = {0, CV_PI / 4, CV_PI / 2, 3 * CV_PI / 4};
    Mat resultadoFinal = zeros(framepeb.size(), CV_8UC1);

    for (double theta : orientations){
        Mat gaborKernel = getGaborKernel(Size(31, 31), 8.0, theta, 10.0, 0.5, 0, CV_32F);
        Mat imggabor;
        filter2D(framepeb, imggabor, CV_8UC3, gaborKernel);
        bitwise_or(resultadoFinal, imggabor, resultadoFinal); // combina os resultados
    }

    // binariza a imagem
    Mat framebi;
    threshold(resultadoFinal, framebi, 110, 255, THRESH_BINARY);

    // encontra contornos
    <<Point>> contornos;
    findContours(framebi, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // calcula a área urbana
    double areatotalpx = framebi.total();
    double areatot = 0.0;

    for (size_t i = 0; i < contornos.size(); i++){
        double area = contourArea(contornos[i]);
        if (area <= 10800){
            <Point> approx;
            approxPolyDP(contornos[i], approx, arcLength(contornos[i], true) * 0.02, true);

            if (approx.size() == 4){ // retângulo ou quadrado
                Rect boundingRect = boundingRect(approx);
                double aspectRatio = (double)boundingRect.width / boundingRect.height;
                if (aspectRatio >= 0.8 && aspectRatio <= 1.2){
                    areatot += area;
                }
            } 
            else if (approx.size() > 4){ // círculo
                double perimeter = arcLength(approx, true);
                double circularity = 4 * CV_PI * (area / (perimeter * perimeter));
                if (circularity > 0.7){
                    areatot += area;
                }
            }
        }
    }

    // calcula a porcentagem de área urbana
    double porcentagemAreaUrbana = (areatot / areatotalpx) * 100.0;

    // salva os resultados em bin
    arquivoBinario("dados/dados.bin", out | binary);
    arquivoBinario.write(reinterpret_cast<char*>(&porcentagemAreaUrbana), sizeof(porcentagemAreaUrbana));
    arquivoBinario.write(reinterpret_cast<char*>(&areatot), sizeof(areatot));
    arquivoBinario.close();

    // salva as imagens para teste
    imwrite("captured_image.jpg", resultadoFinal);
    imwrite("normal_image.jpg", frame);

    waitKey(0);
    destroyAllWindows();

    return 0;
}