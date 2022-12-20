#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#define WN "Pyramids Demo"

int main() {
    const char * fpath = "../chicky_512.png";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    for (;;) {
        imshow(WN, src);
        char c = waitKey(0);
        if (c == 27) {
            break;
        } else if (c == 'i') {
            pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
            cout << "** Zoom In: Image X 2 \n";
        } else if (c == 'o') {
            pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
            cout << "** Zoom Out: Image / 2 \n";
        }
    }
    return 0;
}