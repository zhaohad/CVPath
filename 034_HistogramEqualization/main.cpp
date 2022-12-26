#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    const char * fpath = "../../images/lena.jpg";
    Mat src = imread(fpath, IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    Mat dst;
    equalizeHist(src, dst);
    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    return 0;
}