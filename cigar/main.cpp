#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    string path;
    cout << "Enter file path: ";
    cin >> path;
    Mat image = imread(path);

    if (image.empty()) {
        cout << "Image not found" << endl;
        return -1;
    }

    vector < vector < Point >> contours;
    Mat gray_image, binary_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    threshold(gray_image, binary_image, 127, 255, THRESH_BINARY);
    findContours(binary_image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (const auto& cnt : contours) {
        double area = contourArea(cnt);
        Rect rect = boundingRect(cnt);
        double aspectRatio = static_cast <double> (rect.width) / rect.height;

        // Условие поиска фигуры
        if (area > 1000 && aspectRatio > 0.8 && aspectRatio < 1.2) {
            rectangle(image, rect, Scalar(0, 255, 0), 2);
        }
    }

    imshow("Result", image);
    cout << "Enter ESC to exit";
    int esc = waitKey(0);
    imwrite("result.jpg", image);

    return 0;
}