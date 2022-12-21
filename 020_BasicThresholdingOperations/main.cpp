#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#define WN "Threshold Demo"

Mat src;
Mat src_gray;
Mat dst;
int threshold_type;
int threshold_value;

void ThresholdDemo(int, void *);

int main() {
    const char * fpath = "../chicky_512.png";
    src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }
    imshow("src", src);

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow(WN, WINDOW_AUTOSIZE);

    createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted", WN, &threshold_type, 4, ThresholdDemo);
    createTrackbar("Value", WN, &threshold_value, 255, ThresholdDemo);

    ThresholdDemo(0, NULL);
    waitKey();
    return 0;
}

void ThresholdDemo(int, void *) {
    ThresholdTypes type = THRESH_BINARY;
    int value = threshold_value;
    switch (threshold_type) {
        case 0:
            type = THRESH_BINARY;
            break;
        case 1:
            type = THRESH_BINARY_INV;
            break;
        case 2:
            type = THRESH_TRUNC;
            break;
        case 3:
            type = THRESH_TOZERO;
            break;
        case 4:
            type = THRESH_TOZERO_INV;
            break;
    }
    threshold(src_gray, dst, value, 255, type);
    imshow(WN, dst);
}