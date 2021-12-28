#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#define DIVIDE_WIDTH 100
uchar g_table[256];
Mat g_tableMat(1, 256, CV_8U);

void InitTable();
void ScanImageAndReduceC(Mat& I);
void ScanImageAndReduceIterator(Mat& I);
void ScanImageAndReduceRandomAccess(Mat& I);
void ScanImageAndReducePtr(Mat& I);
void ScanImageAndReduceLUT(Mat& I, Mat& R);
void ScanImageAndBlur(Mat& I);

int main() {
    string img_path = "../bvimg19_1.jpg";
    Mat img = imread(img_path);
    if (img.empty()) {
        cout << "Could not read the image: " << img_path << endl;
        return 1;
    }

    imshow("原始图", img);
    waitKey(0);

    InitTable();

    Mat tmpImg = img.clone();
    double t = getTickCount();
    ScanImageAndReduceC(tmpImg);
    t = (getTickCount() - t) / getTickFrequency();
    cout << "getTickFrequency: " << getTickFrequency() << " ScanImageAndReduceC t: " << t << endl;

    tmpImg = img.clone();
    t = getTickCount();
    ScanImageAndReduceIterator(tmpImg);
    t = (getTickCount() - t) / getTickFrequency();
    cout << "getTickFrequency: " << getTickFrequency() << " ScanImageAndReduceIterator t: " << t << endl;

    tmpImg = img.clone();
    t = getTickCount();
    ScanImageAndReduceRandomAccess(tmpImg);
    t = (getTickCount() - t) / getTickFrequency();
    cout << "getTickFrequency: " << getTickFrequency() << " ScanImageAndReduceRandomAccess t: " << t << endl;

    tmpImg = img.clone();
    t = getTickCount();
    ScanImageAndReducePtr(tmpImg);
    t = (getTickCount() - t) / getTickFrequency();
    cout << "getTickFrequency: " << getTickFrequency() << " ScanImageAndReducePtr t: " << t << endl;

    tmpImg = img.clone();
    t = getTickCount();
    ScanImageAndReduceLUT(img, tmpImg);
    t = (getTickCount() - t) / getTickFrequency();
    cout << "getTickFrequency: " << getTickFrequency() << " ScanImageAndReduceLUT t: " << t << endl;

    tmpImg = img.clone();
    ScanImageAndBlur(tmpImg);
    imshow("ScanImageAndReduce", tmpImg);
    waitKey(0);
    return 0;
}

void InitTable() {
    uchar* p = g_tableMat.data;
    for (int i = 0; i < 256; ++i) {
        p[i] = g_table[i] = (uchar) ((i / DIVIDE_WIDTH) * DIVIDE_WIDTH);
    }
}

void ScanImageAndReduceC(Mat& I) {
    CV_Assert(I.depth() == CV_8U);
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    for (int i = 0; i < nRows; ++i) {
        uchar* p = I.ptr<uchar>(i);
        for (int j = 0; j < nCols; ++j) {
            p[j] = g_table[p[j]];
        }
    }
}

void ScanImageAndReduceIterator(Mat& I) {
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();
    switch (channels) {
        case 1: {
            for (MatIterator_<uchar> it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it) {
                *it = g_table[*it];
            }
            break;
        }
        case 3: {
            for (MatIterator_<Vec3b> it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
                (*it)[0] = g_table[(*it)[0]];
                (*it)[1] = g_table[(*it)[1]];
                (*it)[2] = g_table[(*it)[2]];
            }
            break;
        }
    }
}

void ScanImageAndReduceRandomAccess(Mat& I) {
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();
    switch (channels) {
        case 1: {
            for (int i = 0; i < I.rows; ++i) {
                for (int j = 0; j < I.cols; ++j) {
                    I.at<uchar>(i, j) = g_table[I.at<uchar>(i, j)];
                }
            }
            break;
        }
        case 3: {
            Mat_<Vec3b> _I = I;
            for (int i = 0; i < I.rows; ++i) {
                for (int j = 0; j < I.cols; ++j) {
                    _I.at<Vec3b>(i, j)[0] = g_table[_I.at<Vec3b>(i, j)[0]];
                    _I.at<Vec3b>(i, j)[1] = g_table[_I.at<Vec3b>(i, j)[1]];
                    _I.at<Vec3b>(i, j)[2] = g_table[_I.at<Vec3b>(i, j)[2]];
                }
            }
            I = _I;
            break;
        }
    }
}

void ScanImageAndReducePtr(Mat& I) {
    uchar* p = I.data;
    int64 count = I.cols * I.rows * I.channels();
    for (int i = 0; i < count; ++i) {
        *p++ = g_table[*p];
    }
}

void ScanImageAndReduceLUT(Mat& I, Mat& R) {
    LUT(I, g_tableMat, R);
}

void ScanImageAndBlur(Mat& I) {
    CV_Assert(I.depth() == CV_8U);
    int channel = I.channels();

    CV_Assert(channel == 3);

    int rows = I.rows;
    int cols = I.cols;

    Mat_<Vec3b> J = I;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Vec3b* up = i <= 0 ? nullptr : &J(i - 1, j);
            Vec3b* down = i >= rows - 1 ? nullptr : &J(i + 1, j);
            Vec3b* left = j <= 0 ? nullptr : &J(i, j - 1);
            Vec3b* right = j > cols - 1 ? nullptr : &J(i, j + 1);
            Vec3i z(0, 0, 0);
            if (up != nullptr) {
                z[0] += (*up)[0];
                z[1] += (*up)[1];
                z[2] += (*up)[2];
            }
            if (down != nullptr) {
                z[0] += (*down)[0];
                z[1] += (*down)[1];
                z[2] += (*down)[2];
            }
            if (left != nullptr) {
                z[0] += (*left)[0];
                z[1] += (*left)[1];
                z[2] += (*left)[2];
            }
            if (right != nullptr) {
                z[0] += (*right)[0];
                z[1] += (*right)[1];
                z[2] += (*right)[2];
            }
            z[0] += J(i, j)[0];
            z[1] += J(i, j)[1];
            z[2] += J(i, j)[2];
            J(i, j)[0] = z[0] / 5;
            J(i, j)[1] = z[1] / 5;
            J(i, j)[2] = z[2] / 5;
        }
    }
    I = J;
}