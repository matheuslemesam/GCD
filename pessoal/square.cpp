#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int main() {
    // Carregar imagem, converter para escala de cinza, aplicar blur e afiar a imagem
    Mat image = imread("1.png");
    Mat gray, blur, sharpen;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    medianBlur(gray, blur, 5);
    Mat sharpen_kernel = (Mat_<float>(3,3) << -1,-1,-1, -1,9,-1, -1,-1,-1);
    filter2D(blur, sharpen, -1, sharpen_kernel);

    // Aplicar threshold e morfologia close
    Mat thresh, close;
    threshold(sharpen, thresh, 160, 255, THRESH_BINARY_INV);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    morphologyEx(thresh, close, MORPH_CLOSE, kernel, Point(-1,-1), 2);

    // Encontrar contornos e filtrar usando a área de threshold
    vector<vector<Point>> cnts;
    findContours(close, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int min_area = 100;
    int max_area = 1500;
    int image_number = 0;
    for (size_t i = 0; i < cnts.size(); i++) {
        double area = contourArea(cnts[i]);
        if (area > min_area && area < max_area) {
            Rect rect = boundingRect(cnts[i]);
            Mat ROI = image(rect);
            imwrite("ROI_" + to_string(image_number) + ".png", ROI);
            rectangle(image, rect, Scalar(36, 255, 12), 2);
            image_number++;
        }
    }

    imshow("sharpen", sharpen);
    imshow("close", close);
    imshow("thresh", thresh);
    imshow("image", image);
    waitKey(0);

    return 0;
}