//Lógica 2, transformar a imagem em preto e branco e aplicar a máscara.

#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
    
    using namespace cv; // namespace para não precisar ficar repetindo 

    Mat image = imread("images/luz.jpg"); // Carregar a imagem

    if (image.empty()) { // Verificar se a imagem foi carregada corretamente ou se o caminho está errado
        printf("Erro ao carregar a imagem!\n"); // Usando fprintf para erro
        return -1;
    }

    Mat peb; // converter a imagem para cinza
    cvtColor(image, peb, COLOR_BGR2GRAY);

    int minimo = 200; // Tons próximos ao branco
    int maximo = 255; // Branco puro

    Mat mascara;
    inRange(peb, Scalar(minimo), Scalar(maximo), mascara);

    // Aplicar a máscara à imagem original
    Mat resultado;
    bitwise_and(peb, peb, resultado, mascara);


    imshow("Img Og", image); // mostrar a imagem original

    imshow("Img com raio destacado", resultado); // mostrar a imagem cinza

    waitKey(0); // esperar até que uma tecla seja pressionada

    destroyAllWindows(); // Fechar todas as janelas criadas com o imshow

    return 0;
}