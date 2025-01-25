//detectar área urbana em uma foto

#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>


int main (){
    
    // Indicar o namespace que será utilizado
    using namespace cv;
    using namespace std;

    // carregar imagem já em escala de cinza
    //Mat snk = imread("images/snk.png", IMREAD_GRAYSCALE);
    //Mat gama = imread("images/gama.jpg", IMREAD_GRAYSCALE);
    //Mat bsb = imread("images/brasilia.jpg", IMREAD_GRAYSCALE);
    Mat plantacao = imread("images/plantacao.png", IMREAD_GRAYSCALE);

    if (plantacao.empty()) { // verificar se a imagem foi carregada corretamente ou se o caminho está errado
        printf("Erro ao carregar a imagem!\n"); // usando fprintf para erro
    }

    /*
    //parâmetros do Gabor Filter
        Size ksize(); // Tamanho do Gabor kernel. Quanto maior captura mais texturas porém são mais pesados.
        double sigma = ; //
        double theta ; //Grau do Gabor, CV_PI / 2 = 90º
        double lambda ; /
        double gamma ;
        double psi ; // 0
    
    Mat gaborKernel = getGarborKernel(ksize, sigma, theta, lambda, gamma, psi, CV_32F);
    */

    int minimo = 200; // tons próximos ao branco
    int maximo = 255; // branco puro

    // cria a máscara para a imagem.
    Mat mascara;
    inRange(plantacao, Scalar(minimo), Scalar(maximo), mascara);

    // aplicar a máscara à imagem original
    Mat resultado;
    bitwise_and(plantacao, plantacao, resultado, mascara);

    // converver para binária, os valores acima de 215 serão convertidos para 255 e o restante para 0.
    Mat /*snkbi, gamabi, bsbbi,*/ plantacaobi;
    //threshold(snk, snkbi, 215, 255, THRESH_BINARY);
    //threshold(gama, gamabi, 215, 255, THRESH_BINARY);
    //threshold(bsb, bsbbi, 215, 255, THRESH_BINARY);
    threshold(plantacao, plantacaobi, 200, 255, THRESH_BINARY);

    vector<vector<Point>> contornos; // vetor dentro de um vetor
    // vector<Vec4i>hierarquia; //armazenar infos sobre a hierarquia, não tem necessidade de usar com a RETR_EXTERNAL
    
    // detectar contornos da imagem binária.
    findContours(plantacaobi, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // função; imagem binária; vetor de vetores que armazenará os contornos; modo de recuperação de contornos, os mais comuns são: RETR_EXTERNAL para contornos externos, RETR_LIST para todos sem hierarquia, RETR_TREE para todos com hierarquia; método de aproximação de contornos, mais comuns: CHAIN_APPROX_SIMPLE para armazenar os pontos extremos do contorno, CHAIN_APPROX_NONE para armazenar todos os pontos do contorno; offset, opcional, um ponto que pode ser adicionado a todos os pontos de um contorno.

    // verificar se há contornos detectados, debugg
    if (contornos.empty()) {
        printf("Nenhum contorno detectado!\n");
        return -1;
    }

    double areatotalpx = plantacaobi.total(); // total de pixels da imagem

    // declarar arrays para armazenar coordenadas x, y e áreas
    double x[contornos.size()];
    double y[contornos.size()];
    double areas[contornos.size()];
    double areatot = 0.0;
    int n = contornos.size();

    // Calcular a área urb.
    for(size_t i=0; i<contornos.size(); i++) // size_t funcionará como módulo; contornos.size retorna o valor dos contornos encontrados
    {
        areas[i] = contourArea(contornos[i]); //calcula a área em cada ponto
        //contourArea, funciona com qualquer contorno; vetor de pontos que representam o contorno, obtidos geralmente com a função findContours; Parâmetro opcional o valor padrão é false, se true: calcula a área considerando a orientação de contorno.

        areatot += areas[i]; //armazena as áreas

        Moments m = moments(contornos[i]); //moments; utilizada para calcular momentos de uma imagem ou contorno; m00 = momento de ordem 0, representa a área do contorno; m10 = momento de ordem em relação ao eixo x, usado pra calcular a cord x; m01 = momento de ordem em relação ao eixo y, usado pra calcular a cord y;

        if (m.m00 != 0){ // verificar se a área do momento é dif de 0
        x[i] = m.m10 / m.m00; //cord x do centroide
        y[i] = m.m01 / m.m00; //cord y do centroide
        }

        else{ //caso a área do momento for 0
        x[i] = 0;
        y[i] = 0;
        }
    
    }  

    // calcular a porcentagem de área urbana, em relação à área total da imagem
    double porcentagemAreaUrbana = (areatot / areatotalpx) * 100.0;

    printf("A área urbana na imagem é: %.2f\n", porcentagemAreaUrbana);

    imshow("Img Processada", resultado); // mostrar a imagem cinza

    waitKey(0); // esperar até que uma tecla seja pressionada

    destroyAllWindows(); // fechar todas as janelas criadas com o imshow

    return 0;
}