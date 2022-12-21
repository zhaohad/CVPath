#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * fpath = "../lena.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }
    imshow("src", src);

    int top = 0.05 * src.rows;
    int bottom = top;
    int left = 0.05 * src.cols;
    int right = left;
    Mat dst;
    BorderTypes borderType = BORDER_CONSTANT;
    Scalar v(0, 0, 255);
    while (1) {
        copyMakeBorder(src, dst, top, bottom, left, right, borderType, v);
        imshow("dst", dst);
        char k = waitKey(0);
        if (k == 27 || k == 'q') {
            break;
        } else {
            switch (borderType) {
                case BORDER_CONSTANT:
                    borderType = BORDER_REPLICATE;
                    break;
                case BORDER_REPLICATE:
                    borderType = BORDER_REFLECT;
                    break;
                case BORDER_REFLECT:
                    borderType = BORDER_WRAP;
                    break;
                case BORDER_WRAP:
                    borderType = BORDER_CONSTANT;
                    break;
            }
        }
    }
    return 0;
}