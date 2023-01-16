#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * fpath = "../../images/xianjianyueqingshu.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    Mat dst;
    Mat abs_dst;
    Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

    convertScaleAbs(dst, abs_dst);

    imshow("dst", abs_dst);
    waitKey();
    return 0;
}