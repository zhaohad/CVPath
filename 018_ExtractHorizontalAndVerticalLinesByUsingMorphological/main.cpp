#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void show_wait_destroy(const char * wn, Mat img);

int main() {
    // Load Image
    const char * fpath = "../notes.png";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }
    imshow("src", src);

    // Grayscale
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }
    show_wait_destroy("gray", gray);

    // Grayscale to Binary image
    Mat bw;
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    show_wait_destroy("binary", bw);

    //
    Mat horizontal = bw.clone();
    int horizontal_size = horizontal.cols / 30;
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    show_wait_destroy("horizontal", horizontal);

    //
    Mat vertical = bw.clone();
    int vertical_size = vertical.rows / 30;
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
    show_wait_destroy("vertical", vertical);

    bitwise_not(vertical, vertical);
    show_wait_destroy("vertical", vertical);

    //
    Mat edges;
    adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
    show_wait_destroy("edges", edges);

    Mat kernel = Mat::ones(2, 2, CV_8UC1);
    dilate(edges, edges, kernel);
    show_wait_destroy("dilate", edges);

    Mat smooth;
    vertical.copyTo(smooth);
    blur(smooth, smooth, Size(2, 2));
    show_wait_destroy("smooth", smooth);
    Mat final;
    smooth.copyTo(final, edges);
    show_wait_destroy("final", final);

    return 0;
}

void show_wait_destroy(const char * wn, Mat img) {
    imshow(wn, img);
    moveWindow(wn, 500, 0);
    waitKey();
    // destroyWindow(wn);
}