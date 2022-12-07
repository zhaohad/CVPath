#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "ParallelConvolution.h"
#include "ParallelConvolutionRowSplit.h"

using namespace cv;
using namespace std;

void conv_seq(Mat src, Mat &dst, Mat kernel);
void conv_parallel(Mat src, Mat &dst, Mat kernel);
void conv_parallel_row_split(Mat src, Mat &dst, Mat kernel);

int main() {
    printf("main.c\n");
	const char * fpath = "../lena.jpg";
	Mat src, dst, kernel;
	src = imread(fpath, IMREAD_GRAYSCALE);
	if (src.empty()) {
		cout << "Cannot open lena.jpg" << endl;
		return -1;
	}
	namedWindow("Input");
	namedWindow("Output1");
	namedWindow("Output2");
	namedWindow("Output3");
	imshow("Input", src);

	kernel = (Mat_<double>(3, 3) <<
	        1, 0, -1,
	        1, 0, -1,
	        1, 0, -1);
	/*kernel = (Mat_<double>(5, 5) <<
	        1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1);
	kernel /= 100;*/

    /*kernel = (Mat_<double>(3, 3) <<
            1, 1, 1,
            0, 0, 0,
            -1, -1, -1);*/

	double t = (double) getTickCount();

	conv_seq(src, dst, kernel);
	t = ((double) getTickCount() - t) / getTickFrequency();
	cout << "Sequential implementation: " << t << "s" << endl;
	imshow("Output1", dst);

	waitKey();

	t = (double) getTickCount();
	conv_parallel(src, dst, kernel);
	t = ((double)getTickCount() -t) / getTickFrequency();
	cout << "Parallel Implementation: " << t << "s" << endl;
	imshow("Output2", dst);
	waitKey();

    t = (double) getTickCount();
    conv_parallel_row_split(src, dst, kernel);
    t = ((double)getTickCount() -t) / getTickFrequency();
    cout << "Parallel Implementation(Row Split): " << t << "s" << endl;
    imshow("Output3", dst);
    waitKey();
	return 0;
}

void conv_seq(Mat src, Mat &dst, Mat kernel) {
    int rows = src.rows, cols = src.cols;
    dst = Mat(rows, cols, src.type());

    int sz = kernel.rows / 2;
    copyMakeBorder(src, src, sz, sz, sz,sz, BORDER_REPLICATE);

    for (int i = 0; i < rows; ++i) {
        uchar * dptr = dst.ptr(i);
        for (int j = 0; j < cols; ++j) {
            double value = 0;
            for (int k = -sz; k <= sz; ++k) {
                uchar * sptr = src.ptr(i + sz + k);
                for (int l = -sz; l <= sz; ++l) {
                    value += sptr[j + sz + l] * kernel.ptr<double>(sz + k)[sz + l];
                }
            }
            dptr[j] = saturate_cast<uchar>(value);
        }
    }
}

void conv_parallel(Mat src, Mat &dst, Mat kernel) {
    int rows = src.rows, cols = src.cols;

    dst = Mat(rows, cols, CV_8UC1, Scalar(0));

    int sz = kernel.rows / 2;

    copyMakeBorder(src, src, sz, sz, sz, sz, BORDER_REPLICATE);

    ParallelConvolution obj(src, dst, kernel);
    parallel_for_(Range(0, rows * cols), obj);
}

void conv_parallel_row_split(Mat src, Mat &dst, Mat kernel) {
    int rows = src.rows;
    int cols = src.cols;

    dst = Mat(rows, cols, CV_8UC1, Scalar(0));

    int sz = kernel.rows / 2;
    copyMakeBorder(src, src, sz, sz, sz, sz, BORDER_REPLICATE);

    ParallelConvolutionRowSplit obj(src, dst, kernel);
    parallel_for_(Range(0, rows), obj);
}