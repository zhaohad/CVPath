#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

#define WN_SRC "SRC"
#define WN_HSV "hsv"
#define WN "Demo"

const int max_value_H = 360 / 2;
const int max_value = 255;
int low_H = 0;
int low_S = 0;
int low_V = 0;
int high_H = max_value_H;
int high_S = max_value;
int high_V = max_value;

void on_low_H_thresh_trackbar(int, void *);
void on_low_S_thresh_trackbar(int, void *);
void on_low_V_thresh_trackbar(int, void *);
void on_high_H_thresh_trackbar(int, void *);
void on_high_S_thresh_trackbar(int, void *);
void on_high_V_thresh_trackbar(int, void *);

int main() {
    const char * fpath = "../lena.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }
    imshow(WN_SRC, src);
    namedWindow(WN);

    createTrackbar("Low H", WN, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", WN, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", WN, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", WN, &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", WN, &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", WN, &high_V, max_value, on_high_V_thresh_trackbar);

    Mat hsv;
    Mat threshold;
    while (true) {
        cvtColor(src, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), threshold);

        imshow(WN_HSV, hsv);
        imshow(WN, threshold);

        char k = waitKey(30);
        if (k == 'q' || k == 27) {
            break;
        }
    }
    return 0;
}

void on_low_H_thresh_trackbar(int, void *) {
    low_H = min(high_H - 1, low_H);
    setTrackbarPos("Low H", WN, low_H);
}

void on_low_S_thresh_trackbar(int, void *) {
    low_S = min(high_S - 1, low_S);
    setTrackbarPos("Low S", WN, low_S);
}

void on_low_V_thresh_trackbar(int, void *) {
    low_V = min(high_V - 1, low_V);
    setTrackbarPos("Low V", WN, low_V);
}

void on_high_H_thresh_trackbar(int, void *) {
    high_H = max(high_H, low_H + 1);
    setTrackbarPos("High H", WN, high_H);
}

void on_high_S_thresh_trackbar(int, void *) {
    high_S = max(high_S, low_S + 1);
    setTrackbarPos("High S", WN, high_S);
}

void on_high_V_thresh_trackbar(int, void *) {
    high_V = max(high_V, low_V + 1);
    setTrackbarPos("High V", WN, high_V);
}