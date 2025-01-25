//Lógica 3, aplicar máscara inversa (bitwise_not) na cor preta usando como base o código 2.

/*


*/

#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
    
    using namespace cv; // namespace para não precisar ficar repetindo 

    //Mat image = imread("images/luz.jpg"); // Carregar a imagem
    Mat image = imread("images/raio.png");

    if (image.empty()) { // Verificar se a imagem foi carregada corretamente ou se o caminho está errado
        printf("Erro ao carregar a imagem!\n"); // Usando fprintf para erro
        return -1;
    }

    Mat peb; // converter a imagem para cinza
    cvtColor(image, peb, COLOR_BGR2GRAY); //cvt color converte a imagem para diferentes espaços de cor. Neste caso, de BGR para cinza.

    int minimo = 240; // Tons próximos ao branco
    int maximo = 255; // Branco puro

    Mat mascara; 
    inRange(peb, Scalar(minimo), Scalar(maximo), mascara); //Transforma a imagem em binária, onde os valores que estão entre minimo e maximo são transformados em branco e o restante em preto.

    Mat mascarainversa;
    bitwise_not(mascara, mascarainversa); // Inverter a máscara, transformando o branco em preto e o preto em branco.

    // Aplicar a máscara à imagem original
    Mat resultado;
    bitwise_and(peb, peb, resultado, mascara); // Aplica a máscara invertida à imagem original, resultando em uma imagem onde apenas os pixels fora do intervalo de cores especificado são mantidos.

    imshow("Img Og", image); // mostrar a imagem original

    imshow("Img com raio destacado", resultado); // mostrar a imagem cinza

    waitKey(0); // esperar até que uma tecla seja pressionada

    destroyAllWindows(); // Fechar todas as janelas criadas com o imshow

    return 0;
}