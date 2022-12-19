#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;

int const max_elem = 2;
int const max_kernel_size = 21;

Mat src;
Mat erosion_dst;
Mat dilation_dst;

void Erosion(int pos, void *);
void Dilation(int pos, void *);

int main() {
    const char * fpath = "../lena.jpg";
    src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open lena.jpg" << endl;
        return -1;
    }
    imshow("SRC", src);
    waitKey();

    namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
    namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
    moveWindow("Dilation Demo", src.cols, 0);

    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo", &erosion_elem, max_elem, Erosion);
    createTrackbar("Kernel size:\n 2n +1", "Erosion Demo", &erosion_size, max_kernel_size, Erosion);

    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo", &dilation_elem, max_elem, Dilation);
    createTrackbar("Kernel size:\n 2n +1", "Dilation Demo", &dilation_size, max_kernel_size, Dilation);

    Erosion(0, 0);
    Dilation(0, 0);

    waitKey();

    return 0;
}

void Erosion(int pos, void *) {
    int erosion_type = 0;
    if (erosion_elem == 0) {
        erosion_type = MORPH_RECT;
    } else if (erosion_elem == 1) {
        erosion_type = MORPH_CROSS;
    } else if (erosion_elem == 2) {
        erosion_type = MORPH_ELLIPSE;
    }

    Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
    erode(src, erosion_dst, element);
    imshow("Erosion Demo", erosion_dst);
}

void Dilation(int, void *) {
    int dilation_type = 0;
    if (dilation_elem == 0) {
        dilation_type = MORPH_RECT;
    } else if (dilation_elem == 1) {
        dilation_type = MORPH_CROSS;
    } else if (dilation_elem == 2) {
        dilation_type = MORPH_ELLIPSE;
    }

    Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
    dilate(src, dilation_dst, element);
    imshow("Dilation Demo", dilation_dst);
}