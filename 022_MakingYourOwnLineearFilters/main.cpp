#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * fpath = "../bvimg10.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    imshow("SRC", src);

    Point anchor = Point(-1, -1);
    int ddepth = -1;
    int ind = 0;
    int kernel_size;
    Mat kernel;
    Mat dst;
    for (;;) {
        kernel_size = 3 + 2 * (ind % 5);
        kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (kernel_size * kernel_size);

        filter2D(src, dst, ddepth, kernel, anchor, 0, BORDER_DEFAULT);
        imshow("dst", dst);

        char c = waitKey(500);
        if (c == 27 || c == 'q') {
            break;
        }
        ++ind;
    }
    return 0;
}