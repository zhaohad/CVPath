#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#define STEP_CNT 25

int main() {
    string imgpath1 = "../bvimg10.jpg";
    string imgpath2 = "../bvimg20.jpg";

    Mat img1 = imread(imgpath1);
    Mat img2 = imread(imgpath2);

    namedWindow("img");
    imshow("img", img2);
    waitKey(0);

    double step = 1.0 / STEP_CNT;
    double alpha = 0;
    Mat img;
    for (int i = 0; i < STEP_CNT; ++i) {
        alpha += step;
        addWeighted(img1, alpha, img2, 1 - alpha, 0, img);
        imshow("img", img);
        waitKey(1);
    }
    waitKey(0);
    return 0;
}
