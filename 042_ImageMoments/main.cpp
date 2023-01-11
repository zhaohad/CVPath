#include "iostream"
#include "iomanip"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

Mat src_gray;
int thresh = 10;
RNG rng(12345);

void thresh_callback(int, void *);

int main() {
    const char * fpath = "../../images/xianjianyueqingshu_s.jpg";
    Mat src = imread(fpath);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    const char * source_window = "Source";
    namedWindow(source_window);
    imshow(source_window, src);

    createTrackbar("Canny thresh:", source_window, &thresh, 255, thresh_callback);
    thresh_callback(0, NULL);

    waitKey();
    return 0;
}

void thresh_callback(int, void *) {
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    vector<vector<Point>> contours;
    findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<Moments> mu(contours.size());
    for (size_t i = 0; i < contours.size(); ++i) {
        mu[i] = moments(contours[i]);
    }

    vector<Point2f> mc(contours.size());
    for (size_t i = 0; i < contours.size(); ++i) {
        mc[i] = Point2f(static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)), static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)));
        cout << "mc[" << i << "] = " << mc[i] << endl;
    }

    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); ++i) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int) i, color, 2);
        circle(drawing, mc[i], 4, color, -1);
    }

    imshow("Contours", drawing);

    cout << "\t Info: Area and Contour Lenght \n";
    for (size_t i = 0; i < contours.size(); ++i) {
        cout << "* Contour[" << i << "] - Area (M_00) = " << std::fixed << std::setprecision(2) << mu[i].m00
        << " - Area OpenCV: " << contourArea(contours[i]) << " - Length: " << arcLength(contours[i], true) << endl;
    }
}