#include "iostream"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

Mat src_gray;
int thresh = 100;
RNG rng(12345);

void thresh_callback(int, void *);

int main() {
    const char * fpath = "../../images/xianjiankuiyu_s.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    const char * source_window = "Source";
    namedWindow(source_window);
    imshow(source_window, src);
    createTrackbar("Canny Thresh:", source_window, &thresh, 255, thresh_callback);
    thresh_callback(0, NULL);

    waitKey();
    return 0;
}

void thresh_callback(int, void *) {
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    imshow("Canny_output", canny_output);
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); ++i) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int) i, color, 2, LINE_8, hierarchy, 0);
    }
    imshow("Contours", drawing);
}