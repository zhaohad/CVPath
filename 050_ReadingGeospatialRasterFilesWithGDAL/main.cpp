#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// 没搞定

int main() {
    const char * fpath = "../N37W123.hgt";
    Mat src = imread(fpath, cv::IMREAD_LOAD_GDAL | cv::IMREAD_ANYDEPTH);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    imshow("src", src);
    waitKey(0);
    return 0;
}
