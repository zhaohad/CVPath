#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#define W 500

void drawEllipse( Mat img, int w, double angle);
void drawFilledCircle(Mat img, int w, Point center);
void drawPolygon(Mat img, int w, int cnt);
void drawLine(Mat img, Point start, Point end);

int main() {
    Mat atom(W, W, CV_8UC3);
    drawEllipse(atom, W, 90);
    drawEllipse(atom, W, 0);
    drawEllipse(atom, W, 45);
    drawEllipse(atom, W, -45);
    drawFilledCircle(atom, W, Point(W/2.0, W/2.0));
    imshow("atom", atom);

    Mat rook(W, W, CV_8UC3);
    /*for (int i = 1; i <= 20; ++i) {
        drawPolygon(rook, W, i);
        imshow("rook", rook);
        waitKey(0);
    }*/
    drawPolygon(rook, W, 20);
    rectangle(rook, Point(0, 7 * W / 8.0), Point(W, W), Scalar(0, 255, 255), -1, 8);
    drawLine(rook, Point(0, 15 * W / 16), Point(W, 15 * W / 16));
    drawLine(rook, Point(W / 4, 7 * W / 8), Point(W / 4, W));
    drawLine(rook, Point(W / 2, 7 * W / 8), Point(W / 2, W));
    drawLine(rook, Point(3 * W / 4, 7 * W / 8), Point(3 * W / 4, W));

    imshow("rook", rook);
    waitKey(0);
    return 0;
}

void drawEllipse( Mat img, int w, double angle ) {
    int thickness = 2;
    int lineType = 8;

    ellipse(img, Point(w/2.0, w/2.0), Size(w/4.0, w/16.0), angle, 0, 360, Scalar(255, 0, 0), thickness, lineType);
}

void drawFilledCircle(Mat img, int w, Point center) {
    int thickness = -1;
    int lineType = 8;

    circle(img, center, w/32.0, Scalar(0, 0, 255), thickness, lineType);
}

void drawPolygon(Mat img, int w, int cnt) {
    int lineType = 8;

    /** Create some points */
    Point rook_points[1][20];
    rook_points[0][0] = Point(w / 4.0, 7 * w / 8.0);
    rook_points[0][1] = Point(3 * w / 4.0, 7 * w / 8.0);
    rook_points[0][2] = Point(3 * w / 4.0, 13 * w / 16.0);
    rook_points[0][3] = Point(11 * w / 16.0, 13 * w / 16.0);
    rook_points[0][4] = Point(19 * w / 32.0, 3 * w / 8.0);
    rook_points[0][5] = Point(3 * w / 4.0, 3 * w / 8.0);
    rook_points[0][6] = Point(3 * w / 4.0, w / 8.0);
    rook_points[0][7] = Point(26 * w / 40.0, w / 8.0);
    rook_points[0][8] = Point(26 * w / 40.0, w / 4.0);
    rook_points[0][9] = Point(22 * w / 40.0, w / 4.0);
    rook_points[0][10] = Point(22 * w / 40.0, w / 8.0);
    rook_points[0][11] = Point(18 * w / 40.0, w / 8.0);
    rook_points[0][12] = Point(18 * w / 40.0, w / 4.0);
    rook_points[0][13] = Point(14 * w / 40.0, w / 4.0);
    rook_points[0][14] = Point(14 * w / 40.0, w / 8.0);
    rook_points[0][15] = Point(w / 4.0, w / 8.0);
    rook_points[0][16] = Point(w / 4.0, 3 * w / 8.0);
    rook_points[0][17] = Point(13 * w / 32.0, 3 * w / 8.0);
    rook_points[0][18] = Point(5 * w / 16.0, 13 * w / 16.0);
    rook_points[0][19] = Point(w / 4.0, 13 * w / 16.0);

    const Point * ppt[1] = {rook_points[0]};
    int npt[] = {cnt};

    fillPoly(img, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}

void drawLine(Mat img, Point start, Point end) {
    int thickness = 2;
    int lineType = 8;
    line(img, start, end, Scalar(0, 0, 0), thickness, lineType);
}