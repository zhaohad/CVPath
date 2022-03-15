#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

void changeBaC(Mat & src, Mat & result, float a, float b);
void convert(Mat & src, Mat & result, float a, float b);

int main() {
    string imgpath = "../bvimg10.jpg";
    Mat img = imread(imgpath);
    imshow("原图", img);

    Mat tmp;
    changeBaC(img, tmp, 1, 100);
    imshow("changeBaC", tmp);
    waitKey(0);

    Mat tmp1;
    convert(img, tmp1, 1, 100);
    imshow("convert", tmp1);
    int key = 1;
    // ↑ 82
    // ↓ 84
    // ← 81
    // → 83
    // ESC 27
    destroyAllWindows();
    Mat r;
    double a = 1;
    double b = 0;
    while (key != 27) {
        switch (key) {
            case 82:
                a += 0.1;
                break;
            case 84:
                a -= 0.1;
                break;
            case 81:
                b += 1;
                break;
            case 83:
                b -= 1;
                break;
        }
        convert(img, r, a, b);
        imshow("img", r);
        key = waitKey(0);
    }
    return 0;
}

void changeBaC(Mat & src, Mat & result, float a, float b) {
    result.create(src.size(), src.type());

    CV_Assert(src.depth() == CV_8U);

    int channels = src.channels();
    int nRows = src.rows;
    int nClos = src.cols;
    for (int i = 0; i < nRows; ++i) {
        uchar * sRow = src.ptr<uchar>(i);
        uchar * rRow = result.ptr<uchar>(i);
        for (int j = 0; j < nClos * channels; ++j) {
            rRow[j] = saturate_cast<uchar>(sRow[j] * a + b);
        }
    }
}

void convert(Mat & src, Mat & result, float a, float b) {
    result.create(src.size(), src.type());

    CV_Assert(src.depth() == CV_8U);

    src.convertTo(result, -1, a, b);
}
