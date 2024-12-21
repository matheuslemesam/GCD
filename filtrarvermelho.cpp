// g++ filtrarvermelho.cpp -o main.exe `pkg-config --cflags --libs opencv4`

#include <opencv2/opencv.hpp> // incluir OpenCV
#include <stdio.h> // incluir lib padrão

int main() {

    using namespace cv; // namespace para não precisar ficar repetindo cv::

    Mat espectro = imread("images/espectro.jpg"); // carregar a imagem do espectro visível
    if (espectro.empty()) { //condição para detectar se a imagem foi carregada/ se o caminho está
        printf("Erro ao carregar a imagem!\n"); 
        return -1;
    }

    // Converter a imagem para o espaço de cores HSV
    Mat vermelho;
    cvtColor(espectro, vermelho, COLOR_BGR2HSV);

    // Definir os limites da cor vermelha em HSV, no OpenCV: de 0 á 179
    Scalar menorvermelholaranja(0, 100, 100);   // Limite inferior para vermelho, angulo 0, saturação média e brilho médio
    Scalar maiorvermelholaranja(5, 255, 255);  // Limite superior para vermelho, angulo 10, saturaçao e brilho máx
    Scalar menorvermelhorosa(170, 100, 100); // Limite inferior para vermelho
    Scalar maiorvermelhorosa(179, 255, 255); // Limite superior para vermelho

    // Criar máscaras para as duas faixas de vermelho
    Mat mascara1, mascara2;
    inRange(vermelho, menorvermelholaranja, maiorvermelholaranja, mascara1);
    inRange(vermelho, menorvermelhorosa, maiorvermelhorosa, mascara2);

    // Combinar as duas máscaras
    Mat mascara = mascara1 | mascara2;

    // Aplicar a máscara à imagem original
    Mat resultado;
    bitwise_and(espectro, espectro, resultado, mascara);

    // Mostrar as imagens
    imshow("Imagem Original", espectro);
    imshow("Máscara", mascara);
    imshow("Resultado", resultado);

    waitKey(0);
    return 0;
}