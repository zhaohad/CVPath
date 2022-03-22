#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;
    // string img_path = "../bvimg10.jpg";
    // string img_path = "../bvimg20.jpg";
    // string img_path = "../imageTextN.png";
    // string img_path = "../imageTextR.png";
    string img_path = "../lena.jpg";
    Mat I = imread(img_path, IMREAD_GRAYSCALE);
    imshow("原图", I);

    Mat padded;
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols);
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
    imshow("padded", padded);
    waitKey(0);

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    // printf("planes[1].type = %d, CV_32F = %d\n", planes[1].type(), CV_32F);
    Mat complexI;
    Mat normP0;
    normalize(planes[0], normP0, 0, 1, NORM_MINMAX);
    imshow("normP0", normP0);
    waitKey(0);
    merge(planes, 2, complexI);
    // printf("I.channels() = %d, planes[0].channels() = %d, planes[1].channels() = %d, complexI.channels() = %d\n", I.channels(), planes[0].channels(), planes[1].channels(), complexI.channels());
    // cout << "rows = " << padded.rows << ", cols = " << padded.cols << ", padded.size = " << padded.size << ", complexI.size = " << complexI.size << endl;

    dft(complexI, complexI);

    split(complexI, planes);

    Mat magI;
    magnitude(planes[0], planes[1], magI);
    printf("magI.type = %d\n", magI.type());

    magI += Scalar::all(1);
    log(magI, magI);

    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));
    Mat q1(magI, Rect(cx, 0, cx, cy));
    Mat q2(magI, Rect(0, cy, cx, cy));
    Mat q3(magI, Rect(cx, cy, cx, cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, NORM_MINMAX);

    imshow("magI", magI);
    waitKey(0);

    return 0;
}
