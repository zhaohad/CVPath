#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * fpath = "../../images/sudoku.png";

    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }
    Mat dst;
    Canny(src, dst, 50, 200, 3);

    Mat cdst;
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    Mat cdstP = cdst.clone();
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0);
    cout << "HoughLines line size: " << lines.size() << endl;

    for (size_t i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }
    imshow("dst", dst);
    imshow("cdst", cdst);

    vector<Vec4i> linesP;
    HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10);
    cout << "HoughLinesP line size: " << linesP.size() << endl;
    for (size_t i = 0; i < linesP.size(); ++i) {
        Vec4i  l = linesP[i];
        line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 3, LINE_AA);
    }

    imshow("cdstP", cdstP);
    waitKey();
    return 0;
}