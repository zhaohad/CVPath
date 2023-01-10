#include "iostream"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

Mat src_gray;
int thresh = 100;
RNG rng(12345);

void thresh_callback(int, void *);

int main() {
    const char * fpath = "../../images/opencv-logo.png";
    Mat src = imread(fpath);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    cvtColor(src,src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    const char * source_window = "Source";
    namedWindow(source_window);
    imshow(source_window, src);

    createTrackbar("Canny thresh: ", source_window, &thresh, 255, thresh_callback);
    thresh_callback(0, NULL);

    waitKey();
    return 0;
}

void thresh_callback(int, void *) {
    Mat canny_out;
    Canny(src_gray, canny_out, thresh, thresh * 2);

    vector<vector<Point>> contours;
    findContours(canny_out, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> centers(contours.size());
    vector<float> radius(contours.size());

    for (size_t i = 0; i < contours.size(); ++i) {
        approxPolyDP(contours[i], contours_poly[i], 3, true);
        boundRect[i] = boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
    }

    Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);

    for(size_t i = 0; i < contours.size(); ++i) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours_poly, (int) i, color);
        rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
        circle(drawing, centers[i], (int) radius[i], color, 2);
    }

    imshow("Contours", drawing);
}