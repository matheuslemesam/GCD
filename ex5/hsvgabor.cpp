#include <opencv2/opencv.hpp>
#include <cstdio> // Substituição de iostream por stdio

// Função para aplicar Filtros de Gabor
void applyGaborFilters(const Mat& src, Mat& gaborResponse) {
    vector<Mat> gaborResponses;
    int kernelSize = 31; // Tamanho do kernel
    double sigma = 5.0;  // Desvio padrão do Gaussian
    double gamma = 0.5;  // Aspect Ratio
    double lambda = 10.0; // Comprimento de onda

    // Aplicar Gabor para 4 direções: 0, 45, 90 e 135 graus
    for (int i = 0; i < 4; ++i) {
        double theta = CV_PI * i / 4; // Ângulo
        Mat kernel = getGaborKernel(Size(kernelSize, kernelSize), sigma, theta, lambda, gamma, 0, CV_32F);
        Mat response;
        filter2D(src, response, CV_32F, kernel);
        gaborResponses.push_back(abs(response));
    }

    // Combinar as respostas
    gaborResponse = Mat::zeros(src.size(), CV_32F);
    for (const auto& response : gaborResponses) {
        gaborResponse += response;
    }

    // Normalizar para exibição
    normalize(gaborResponse, gaborResponse, 0, 255, NORM_MINMAX, CV_8U);
}

int main() {

    using namespace std, cv;

    // Carregar imagem
    Mat src = imread("images/plantacao.png");
    if (src.empty()) {
        fprintf(stderr, "Erro ao carregar a imagem!\n");
        return -1;
    }

    // Conversão para escala de cinza e HSV
    Mat gray, hsv;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    cvtColor(src, hsv, COLOR_BGR2HSV);

    // Segmentação em HSV para identificar áreas urbanas
    Mat urbanMask;
    inRange(hsv, Scalar(0, 0, 50), Scalar(180, 50, 255), urbanMask);

    // Aplicar Filtros de Gabor para análise de textura
    Mat gaborResponse;
    applyGaborFilters(gray, gaborResponse);

    // Combinar as máscaras (interseção)
    Mat combinedMask;
    bitwise_and(urbanMask, gaborResponse, combinedMask);

    // Exibir os resultados
    imshow("Imagem Original", src);
    imshow("Máscara HSV (Cor)", urbanMask);
    imshow("Resposta de Textura (Gabor)", gaborResponse);
    imshow("Máscara Combinada", combinedMask);

    waitKey(0);
    return 0;
}
