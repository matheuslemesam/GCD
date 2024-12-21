#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
    
    using namespace cv; // namespace para não precisar ficar repetindo 

    Mat image = imread("images/dex.jpg"); // Carregar a imagem

    if (image.empty()) { // Verificar se a imagem foi carregada corretamente ou se o caminho está errado
        fprintf(stderr, "Erro ao carregar a imagem!\n"); // Usando fprintf para erro
        return -1;
    }

    Mat grayImage; // converter a imagem para cinza
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    imshow("Img Og", image); // mostrar a imagem original

    imshow("Img cinza", grayImage); // mostrar a imagem cinza

    waitKey(0); // esperar até que uma tecla seja pressionada

    destroyAllWindows(); // Fechar todas as janelas criadas com o imshow

    return 0;
}