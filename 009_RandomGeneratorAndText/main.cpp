#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#define W 1000
#define H W
#define WN "RandomGeneratorAndText"
#define NUMBER 10

Scalar randomColor(RNG &rng);
int Drawing_Random_Lines(Mat image, RNG rng);
int Drawing_Random_Rectangles(Mat image, RNG rng);
int Drawing_Random_Ellipses(Mat image, RNG rng);
int Drawing_Random_Polylines(Mat image, RNG rng);
int Drawing_Random_Filled_Polygons(Mat image, RNG rng);
int Drawing_Random_Circles(Mat image, RNG rng);
int Displaying_Random_Text(Mat image, RNG rng);
int Displaying_Big_End(Mat image, RNG rng);

int main() {
    RNG rng(0xFFFFFFFF);
    Mat image = Mat::zeros(W, H, CV_8UC3);
    imshow(WN, image);
    waitKey(0);

    Drawing_Random_Lines(image, rng);
    Drawing_Random_Rectangles(image, rng);
    Drawing_Random_Ellipses(image, rng);
    Drawing_Random_Polylines(image, rng);
    Drawing_Random_Filled_Polygons(image, rng);
    Drawing_Random_Circles(image, rng);
    Displaying_Random_Text(image, rng);
    Displaying_Big_End(image, rng);

    return 0;
}

int Drawing_Random_Lines(Mat image, RNG rng) {
    int lineType = 8;
    Point pt1, pt2;

    for (int i = 0; i < NUMBER; i++) {
        pt1.x = rng.uniform(0, W);
        pt1.y = rng.uniform(0, H);
        pt2.x = rng.uniform(0, W);
        pt2.y = rng.uniform(0, H);

        line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), lineType);
    }
    imshow(WN, image);
    waitKey(0);
    return 0;
}

int Drawing_Random_Rectangles(Mat image, RNG rng) {
    int lineType = 8;
    Point pt1, pt2;

    for (int i = 0; i < NUMBER; i++) {
        pt1.x = rng.uniform(0, W);
        pt1.y = rng.uniform(0, H);
        pt2.x = rng.uniform(0, W);
        pt2.y = rng.uniform(0, H);

        rectangle(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), lineType);
    }
    imshow(WN, image);
    waitKey(0);
    return 0;
}

int Drawing_Random_Polylines(Mat image, RNG rng) {
    int lineType = 8;
    Point pt1, pt2;

    int s = 2 * NUMBER;
    Point pts[s];
    for (int i = 0; i < NUMBER; i++) {
        pt1.x = rng.uniform(0, W);
        pt1.y = rng.uniform(0, H);
        pts[2 * i] = pt1;
        pts[2 * i + 1] = pt2;
    }
    Point * ppt[1] = {pts};
    polylines(image, ppt, &s, 1, false, randomColor(rng), rng.uniform(1, 10), lineType);
    imshow(WN, image);
    waitKey(0);
    return 0;
}

int Drawing_Random_Filled_Polygons(Mat image, RNG rng) {
    int lineType = 8;
    Point pt1, pt2;

    int s = 2 * NUMBER;
    Point pts[s];
    for (int i = 0; i < NUMBER; i++) {
        pt1.x = rng.uniform(0, W);
        pt1.y = rng.uniform(0, H);
        pts[2 * i] = pt1;
        pts[2 * i + 1] = pt2;
    }
    const Point * ppt[1] = {pts};
    fillPoly(image, ppt, &s, 1, randomColor(rng), rng.uniform(1, 10), lineType);
    imshow(WN, image);
    waitKey(0);
    return 0;
}

int Drawing_Random_Ellipses(Mat image, RNG rng) {
    int lineType = 8;
    Point pt1, pt2;

    for (int i = 0; i < NUMBER; i++) {
        pt1.x = rng.uniform(0, W);
        pt1.y = rng.uniform(0, H);
        pt2.x = rng.uniform(0, W);
        pt2.y = rng.uniform(0, H);

        ellipse(image, pt1, pt2, 0, 0, 360, randomColor(rng), rng.uniform(1, 10), lineType);
        imshow(WN, image);
    }
    waitKey(0);
    return 0;
}

int Drawing_Random_Circles(Mat image, RNG rng) {
    int lineType = 8;
    Point pt1, pt2;

    for (int i = 0; i < NUMBER; i++) {
        pt1.x = rng.uniform(0, W);
        pt1.y = rng.uniform(0, H);
        pt2.x = rng.uniform(0, W);
        pt2.y = rng.uniform(0, H);

        circle(image, pt1, (pt2.x + pt2.y) / 2, randomColor(rng), rng.uniform(1, 10), lineType);
    }
    imshow(WN, image);
    waitKey(0);
    return 0;
}

int Displaying_Random_Text(Mat image, RNG rng) {
    int lineType = 8;

    for (int i = 1; i < NUMBER; i++) {
        Point org;
        org.x = rng.uniform(0, W);
        org.y = rng.uniform(0, H);

        putText(image, "Testing text rendering", org, rng.uniform(0, 8),
                rng.uniform(0, 100) * 0.05 + 0.1, randomColor(rng), rng.uniform(1, 10), lineType);
    }
    imshow(WN, image);
    waitKey(0);

    return 0;
}

int Displaying_Big_End(Mat image, RNG rng) {
    Size textsize = getTextSize("OpenCV forever!", 0, 3, 5, 0);
    Point org((W - textsize.width) / 2, (H - textsize.height) / 2);
    int lineType = 8;

    Mat image2;

    for (int i = 0; i < 255; i += 2) {
        image2 = image - Scalar::all(i);
        putText(image2, "OpenCV forever!", org, 0, 3,
                Scalar(i, i, 255), 5, lineType);
        imshow(WN, image2);
        waitKey(10);
    }
    waitKey(0);

    return 0;
}

Scalar randomColor(RNG &rng) {
    int icolor = (unsigned) rng;
    return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}