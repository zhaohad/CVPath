#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main() {
    Mat src = (Mat_<uchar>(8, 8) <<
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 255, 255, 255, 0, 0, 0, 255,
            0, 255, 255, 255, 0, 0, 0, 0,
            0, 255, 255, 255, 0, 255, 0, 0,
            0, 0, 255, 0, 0, 0, 0, 0,
            0, 0, 255, 0, 0, 255, 255, 0,
            0, 255, 0, 255, 0, 0, 255, 0,
            0, 255, 255, 255, 0, 0, 0, 0);

    Mat kernel = (Mat_<int>(3, 3) <<
            0, 1, 0,
            1, -1, 1,
            0, 1, 0);

    Mat dst;
    morphologyEx(src, dst, MORPH_HITMISS, kernel);

    const int rate = 50;
    kernel = (kernel + 1) * 127;
    kernel.convertTo(kernel, CV_8U);

    resize(kernel, kernel, Size(), rate, rate, INTER_NEAREST);
    imshow("kernel", kernel);
    moveWindow("kernel", 0, 0);

    resize(src, src, Size(), rate, rate, INTER_NEAREST);
    imshow("src", src);
    moveWindow("src", 0, 200);

    resize(dst, dst, Size(), rate, rate, INTER_NEAREST);
    imshow("dst", dst);
    moveWindow("dst", 500, 200);

    waitKey(0);
    return 0;
}