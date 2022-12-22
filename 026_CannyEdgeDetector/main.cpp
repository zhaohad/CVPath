#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#define WN "Edge Map"

Mat src;
Mat src_gray;
Mat dst;
Mat detected_edges;

int lowThreshold = 0;

void CannyThreshold(int, void *);

int main() {
    const char * fpath = "../../images/bvimg20.jpg";
    src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow(WN, WINDOW_AUTOSIZE);

    createTrackbar("Min Threshold", WN, &lowThreshold, 100, CannyThreshold);

    CannyThreshold(0, 0);

    waitKey();
    return 0;
}

void CannyThreshold(int, void *) {
    blur(src_gray, detected_edges, Size(3, 3));

    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3, 3);

    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);

    imshow(WN, dst);
}