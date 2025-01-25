#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int main() {

    // carregar imagem convertida para escala de cinza, aplicar blur e afiar a imagem
    Mat image = imread("images/square.png",  IMREAD_GRAYSCALE);

    // debug img
    if (image.empty()) { //condição para detectar se a imagem foi carregada/ se o caminho está
        printf("Erro ao carregar a imagem!\n"); 
        return -1;
    }

    // Aplicar blur e sharpen (suavizar e afiar a imagem)
    Mat blur, sharpen;
    medianBlur(image, blur, 5); //reduz ruído enquanto preserva bordas; kernel de tam 5
    Mat sharpen_kernel = (Mat_<float>(3,3) << -1,-1,-1, -1,9,-1, -1,-1,-1); //kernel para afiar
    filter2D(blur, sharpen, -1, sharpen_kernel);

    // Aplicar threshold e morfologia close
    Mat thresh, close;
    threshold(sharpen, thresh, 160, 255, THRESH_BINARY_INV);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    morphologyEx(thresh, close, MORPH_CLOSE, kernel, Point(-1,-1), 2);

    // encontrar contornos e filtrar usando a área de threshold
    vector<vector<Point>> cnts;
    findContours(close, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int min_area = 100;
    int max_area = 1500;
    int image_number = 0;
    for (size_t i = 0; i < cnts.size(); i++) {
        double area = contourArea(cnts[i]);
        if (area > min_area && area < max_area) {
            Rect rect = boundingRect(cnts[i]);
            Mat ROI = image(rect); //Rectangle On Image
            //imwrite("ROI_" + to_string(image_number) + ".png", ROI);
            rectangle(image, rect, Scalar(36, 255, 12), 2);
            image_number++;
        }
    }

    imshow("sharpen", sharpen);
    imshow("close", close); //imagem após aplicar morfologia, detecta contornos
    imshow("thresh", thresh);
    imshow("image", image);
    waitKey(0);

    return 0;
}