#include <opencv2/opencv.hpp>
#include <cstdio>
#include <vector>
#include <sys/stat.h> // lib para verificar se a foto existe ou criar um novo (linux)
#include <unistd.h> // lib para apagar a foto após o tratamento de dados (linux)

using namespace cv;
using namespace std;

int main() {
    // inicializa a cam
    VideoCapture cap(0); // 0, ID da câmera padrão

    // debug cam
    if (!cap.isOpened()) {
        printf("Erro ao abrir a câmera\n");
        return -1;
    }

    // tirar foto
    Mat frame;
    cap >> frame;

    // debug foto
    if (frame.empty()) {
        printf("Erro ao capturar a imagem\n");
        return -1;
    }

    // armazena a img
    const char* imagePath = "captured_image.jpg";
    imwrite(imagePath, frame);

    // img para escala de cinza
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    // Aplicar a operação de limiarização (binarização)
    Mat binaria;
    threshold(gray, binaria, 128, 255, THRESH_BINARY);

    // Encontrar os contornos
    vector<vector<Point>> contornos;
    findContours(binaria, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Calcular a área total da imagem
    double areaTotal = binaria.total();

    // Calcular a área dos contornos
    double areaContornos = 0.0;
    for (size_t i = 0; i < contornos.size(); i++) {
        areaContornos += contourArea(contornos[i]);
    }

    // Calcular a porcentagem de área urbana
    double porcentagemAreaUrbana = (areaContornos / areaTotal) * 100.0;

    // Exibir a porcentagem de área urbana no terminal
    printf("A área urbana na imagem é: %.2f%%\n", porcentagemAreaUrbana);

    // Guardar os dados (por exemplo, em um arquivo de texto)
    FILE *file = fopen("area_urbana.txt", "a");
    if (file != NULL) {
        fprintf(file, "A área urbana na imagem é: %.2f%%\n", porcentagemAreaUrbana);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para escrita\n");
    }

    // Apagar a imagem
    if (remove(imagePath) != 0) {
        printf("Erro ao apagar a imagem\n");
    } else {
        printf("Imagem apagada com sucesso\n");
    }

    // Mostrar a imagem processada
    imshow("Img Processada", binaria);

    waitKey(0); // Esperar até que uma tecla seja pressionada

    destroyAllWindows(); // Fechar todas as janelas criadas com o imshow

    return 0;
}