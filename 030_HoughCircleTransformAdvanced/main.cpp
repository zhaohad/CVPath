#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#define WN "Hough Circle Detection Demo"
#define CANNY_TRACKBAR_NAME "Canny threshold"
#define ACCUMULATOR_TRACKBAR_NAME "Accumulator Threshold"

void HoughDetection(const Mat & src_gray, const Mat & src_display, int cannyThreshold, int accumulatorThreshold);

int main() {
    const char * fpath = "../../images/stuff.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

    int cannyThreshold = 100;
    int accumulatorThreshold = 50;

    namedWindow(WN);
    createTrackbar(CANNY_TRACKBAR_NAME, WN, &cannyThreshold, 255);
    createTrackbar(ACCUMULATOR_TRACKBAR_NAME, WN, &accumulatorThreshold, 200);

    char key = 0;
    while (key != 'q' && key != 'Q' && key != 27) {
        cannyThreshold = max(cannyThreshold, 1);
        accumulatorThreshold = max(accumulatorThreshold, 1);
        HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);
        key = waitKey(10);
    }
    imshow("src", src);
    waitKey();
    return 0;
}

void HoughDetection(const Mat & src_gray, const Mat & src_display, int cannyThreshold, int accumulatorThreshold) {
    vector<Vec3f> circles;
    HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows / 8, cannyThreshold, accumulatorThreshold, 0, 0);

    Mat display = src_display.clone();
    for (size_t i = 0; i < circles.size(); ++i) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(display, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        circle(display, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }

    imshow(WN, display);
}