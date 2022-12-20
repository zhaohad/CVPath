#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;
using namespace cv;

Mat src;
Mat dst;
int morph_type;
int morph_shape;
int morph_size;

#define WIN_NAME "Morphology Transformations Demo"

void Morphology_Operations(int, void *);

int main() {
    const char * fpath = "../baboon.jpg";
    src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    namedWindow(WIN_NAME, WINDOW_AUTOSIZE);
    createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", WIN_NAME, &morph_type, 4, Morphology_Operations);
    createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", WIN_NAME, &morph_shape, 2, Morphology_Operations);
    createTrackbar("Kernel size:\n 2n +1", WIN_NAME, &morph_size, 21, Morphology_Operations);

    Morphology_Operations(0, NULL);

    waitKey();
    return 0;
}

void Morphology_Operations(int, void *) {
    MorphTypes type = MORPH_OPEN;
    switch (morph_type) {
        case 0:
            type = MORPH_OPEN;
            break;
        case 1:
            type = MORPH_CLOSE;
            break;
        case 2:
            type = MORPH_GRADIENT;
            break;
        case 3:
            type = MORPH_TOPHAT;
            break;
        case 4:
            type = MORPH_BLACKHAT;
            break;
    }
    MorphShapes shape = MORPH_RECT;
    switch (morph_shape) {
        case 0:
            shape = MORPH_RECT;
            break;
        case 1:
            shape = MORPH_CROSS;
            break;
        case 2:
            shape = MORPH_ELLIPSE;
            break;
    }

    Mat kernel = getStructuringElement(shape, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

    morphologyEx(src, dst, type, kernel);
    imshow(WIN_NAME, dst);
}