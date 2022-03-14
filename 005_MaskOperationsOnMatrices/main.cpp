#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void operation(Mat & R, Mat & I);
void maskOperation(Mat & R, Mat & I);

int main() {
    cout << cv::getVersionString() << endl;
    std::cout << "Hello, World!" << std::endl;
    string img_path = "../bvimg10.jpg";
    Mat img = imread(img_path);

    if (img.empty()) {
        cout << "Could not read the image: " << img_path << endl;
        return 1;
    }

    imshow("原始图", img);
    waitKey(0);
    destroyWindow("原始图");

    // Mat tmpImg(img.rows, img.cols, CV_8UC3);
    // Mat tmpImg = img.clone();
    Mat tmpImg;
    operation(tmpImg, img);
    imshow("operation", tmpImg);
    waitKey(0);
    destroyWindow("operation");

    Mat tmpImgMask;
    maskOperation(tmpImgMask, img);
    imshow("maskOperation", tmpImgMask);
    waitKey(0);
    destroyWindow("maskOperation");
    return 0;
}

void operation(Mat & R, Mat & I) {
    R.create(I.size(), I.type());

    CV_Assert(I.depth() == CV_8U);
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols;

    for (int i = 1; i < nRows - 1; ++i) {
        uchar * pRow = I.ptr<uchar>(i - 1);
        uchar * cRow = I.ptr<uchar>(i);
        uchar * nRow = I.ptr<uchar>(i + 1);
        uchar * cR = R.ptr<uchar>(i);
        for (int j = channels; j < channels * (nCols - 1); ++j) {
            cR[j] = saturate_cast<uchar>(5 * cRow[j] - pRow[j] - nRow[j] - cRow[j - channels] - cRow[j + channels]);
        }
    }
    R.row(0).setTo(Scalar(0));
    R.row(nRows - 1).setTo(Scalar(0));
    R.col(0).setTo(Scalar(0));
    R.col(nCols - 1).setTo(Scalar(0));
}

void maskOperation(Mat & R, Mat & I) {
    R.create(I.rows, I.cols, I.type());
    Mat mask = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(I, R, I.depth(), mask);
}