#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// 概念有点复杂，要用偏导数，回头再看吧

int main() {
    const char * fpath = "../../images/xianjianyueqingshu_s.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    imshow("src", src);
    waitKey(0);
    return 0;
}
