#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * fpath = "../lena.jpg";
    Mat img = imread(fpath, IMREAD_COLOR);
    if (img.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    //  imshow("img", img);
    // waitKey();

    Mat src;
    Mat src_gray;
    int ksize = -1;
    double scale = 1;
    double delta = 0;
    while (1) {
        GaussianBlur(img, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

        cvtColor(src, src_gray, COLOR_BGR2GRAY);
        Mat grad;
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;
        Sobel(src_gray, grad_x, CV_16S, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
        Sobel(src_gray, grad_y, CV_16S, 0, 1, ksize, scale, delta, BORDER_DEFAULT);

        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);

        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
        imshow("grad_x", grad_x);
        imshow("grad_y", grad_y);
        imshow("abs_grad_x", abs_grad_x);
        imshow("abs_grad_y", abs_grad_y);

        imshow("grad", grad);

        char k = waitKey();
        if (k == 27 || k == 'q') {
            break;
        } else if (k == 'r' || k == 'R') {
            scale = 1;
            ksize = -1;
            delta = 0;
        } else if (k == 'k' || k == 'K') {
            ksize = ksize < 30 ? ksize + 2 : -1;
        } else if (k == 's' || k == 'S') {
            ++scale;
        } else if (k == 'd' || k == 'D') {
            ++delta;
        }
        cout << "ksize: " << ksize << ", scale: " << scale << ", delta: " << delta << endl;
    }
    return 0;
}