#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

#define WN1 "Standard Hough Lines Demo"
#define WN2 "Probobilistic Hough Lines Demo"

Mat src, edges;
Mat src_gray;

Mat standard_hough, probabilistic_hough;

int s_trackbar = 150;
int p_trackbar = 150;

void Standard_Hough(int, void *);
void Probabilistic_Hough(int, void *);

int main() {
    const char * fpath = "../../images/building.jpg";
    src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_RGB2GRAY);
    Canny(src_gray, edges, 50, 200, 3);

    char thresh_label[50];
    snprintf(thresh_label, sizeof(thresh_label), "Thres: %d + input", 50);

    namedWindow(WN1);
    createTrackbar(thresh_label, WN1, &s_trackbar, 150, Standard_Hough);

    namedWindow(WN2);
    createTrackbar(thresh_label, WN2, &p_trackbar, 150, Probabilistic_Hough);

    Standard_Hough(0, NULL);
    Probabilistic_Hough(0, NULL);
    waitKey();
    return 0;
}

void Standard_Hough(int, void *) {
    vector<Vec2f> s_lines;
    cvtColor(edges, standard_hough, COLOR_GRAY2BGR);

    HoughLines(edges, s_lines, 1, CV_PI / 180, 50 + s_trackbar, 0, 0);

    for (size_t i = 0; i < s_lines.size();  ++i) {
        float r = s_lines[i][0];
        float t = s_lines[i][1];

        double cos_t = cos(t), sin_t = sin(t);
        double x0 = r*cos_t, y0 = r * sin_t;
        double alpha = 1000;

        Point pt1(cvRound(x0 + alpha*(-sin_t)), cvRound(y0 + alpha*cos_t));
        Point pt2(cvRound(x0 - alpha*(-sin_t)), cvRound(y0 - alpha*cos_t));
        line(standard_hough, pt1, pt2, Scalar(255,0,0), 3, LINE_AA);
    }
    imshow(WN1, standard_hough);
}

void Probabilistic_Hough(int, void *) {
    vector<Vec4i> p_lines;
    cvtColor(edges, probabilistic_hough, COLOR_GRAY2BGR);

    HoughLinesP(edges, p_lines, 1, CV_PI / 180, 50 + p_trackbar, 30, 10);
    for (size_t i = 0; i < p_lines.size(); ++i) {
        Vec4i l = p_lines[i];
        line(probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
    }
    imshow(WN2, probabilistic_hough);
}