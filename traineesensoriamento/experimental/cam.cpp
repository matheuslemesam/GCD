#include <stdio.h>
#include <unistd.h>
#include <raspicam/raspicam.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main () {
    
    // inicializa a cam
    VideoCapture cap(0, CAP_V4L2); // 0, ID padrão da cam
    cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CAP_PROP_FPS, 30);
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));

    // debug cam
    if (!cap.isOpened()){
        raspicam::RaspiCam Camera;
        for (int i = 0; i < 3; i++){
            Camera.release(); // libera a cam
            sleep(3); // espera 3 segundos
            if (Camera.open()) {
                cap.open(0, cv::CAP_V4L2); // tenta abrir a cam
                if (cap.isOpened()) {
                    break; // se a cam abrir, sai do loop
                }
            }
        }
    }

    // tirar foto
    Mat frame;
    cap >> frame;

    // salvar a imagem p testes
    const char* imagePath = "captured_image.jpg";
    imwrite(imagePath, resultado);

    return 0;
}