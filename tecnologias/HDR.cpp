#include <opencv2/opencv.hpp>
#include <opencv2/photo.hpp>
#include <cstdio>

using namespace cv;

int main() {
    // Carregar a imagem
    Mat imagem = imread("images/arducam.jpg", IMREAD_COLOR);
    if (imagem.empty()) {
        printf("Erro ao carregar a imagem!\n");
        return -1;
    }

    // Converter a imagem para HDR
    Mat hdr;
    detailEnhance(imagem, hdr, 12, 0.15);

    // Salvar a imagem HDR
    imwrite("arducamHDR.jpg", hdr);

    // Mostrar a imagem original e a HDR
    imshow("Imagem Original", imagem);
    imshow("Imagem HDR", hdr);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
