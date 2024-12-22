//Lógica 1, utilizar HSV para detectar o raio luminoso pela cor com base no seu intervalo de cores.

// g++ detectacao1.cpp -o main.exe `pkg-config --cflags --libs opencv4`

#include <opencv2/opencv.hpp> // incluir OpenCV
#include <stdio.h> // incluir lib padrão

int main() {

    using namespace cv; // namespace para não precisar ficar repetindo cv::

    Mat luz = imread("images/luz.jpg"); // carregar a imagem da luz visível
    if (luz.empty()) { //condição para detectar se a imagem foi carregada/ se o caminho está
        printf("Erro ao carregar a imagem!\n"); 
        return -1;
    }

    // Converter a imagem para o espaço de cores HSV
    Mat hsv;
    cvtColor(luz, hsv, COLOR_BGR2HSV);

    // Definir os limites da cor azul em HSV
    Scalar menorazul(126, 100, 100);   
    Scalar maiorazul(150, 255, 255);
    Scalar branco(0, 0, 240);
    Scalar branco2(179, 55, 255);
    Scalar roxo(151, 100, 100);
    Scalar roxo2(169, 255, 255);

    // Criar máscaras para as duas faixas de vermelho
    Mat mascara1, mascara2, mascara3;
    inRange(hsv, menorazul, maiorazul, mascara1);
    inRange(hsv, branco, branco2, mascara2);
    inRange(hsv, roxo, roxo2, mascara3);

    // Combinar as duas máscaras
    Mat mascara = mascara1 | mascara2 | mascara3;


    // Aplicar a máscara à imagem original
    Mat resultado;
    bitwise_and(luz, luz, resultado, mascara);

    // Mostrar as imagens
    imshow("Imagem Original", luz);
    //imshow("Máscara", mascara);
    imshow("Resultado", resultado);

    waitKey(0);
    return 0;
}
