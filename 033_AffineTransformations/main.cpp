#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * fpath = "../../images/lena.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    Point2f srcTri[3];
    srcTri[0] = Point2f(0.f, 0.f);
    srcTri[1] = Point2f(src.cols - 1.f, 0.f);
    srcTri[2] = Point2f(0.f, src.rows - 1.f);

    Point2f dstTri[3];
    dstTri[0] = Point2f(0.f, src.rows * 0.33f);
    dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
    dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);

    Mat warp_mat = getAffineTransform(srcTri, dstTri);
    Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());

    warpAffine(src, warp_dst, warp_mat, src.size());

    imshow("src", src);
    imshow("dst", warp_dst);

    Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
    double angle = -50;
    double scale = 1.2;

    Mat rot_mat = getRotationMatrix2D(center, angle, scale);

    Mat warp_rotate_dst;
    warpAffine(src, warp_rotate_dst, rot_mat, warp_dst.size());
    imshow("rot", warp_rotate_dst);
    waitKey();

    return 0;
}