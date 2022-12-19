#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/simd_intrinsics.hpp>

using namespace std;
using namespace cv;

void conv1d(Mat src, Mat &dst, Mat kernel);
void conv1dsimd(Mat src, Mat kernel, float * ans, int row = 0, int rowk = 0, int len = -1);
void convolute_simd(Mat src, Mat &dst, Mat kernel);

int main() {
    /**
     * There are some problems that I dont know
     */
    const char * fpath = "../lena.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open lena.jpg" << endl;
        return -1;
    }
    Mat dst;
    Mat kernel;
    kernel = (Mat_<double>(3, 3) <<
            1, 0, -1,
            1, 0, -1,
            1, 0, -1);
    imshow("src", src);
    waitKey();

    convolute_simd(src, dst, kernel);
    imshow("dst", dst);
    waitKey();
    return 0;
}

/*void conv1d(Mat src, Mat kernel, float * ans, int row, int rowk, int len = -1) {
    if (len == -1) {
        len = src.cols;
    }

    Mat src_32, kernel_32;
    src.convertTo(src_32, CV_32FC1, 1);

    int ksize = kernel.cols;
    int sz = kernel.cols / 2;
    copyMakeBorder(src_32, src_32, 0, 0, sz, sz, BORDER_REPLICATE);

    float * sptr = src_32.ptr<float>(row);
    float * kptr = kernel.ptr<float>(rowk);
    for (int k = 0; k < ksize; ++k) {
        for (int i = 0; i < len; ++i) {
            sptr
        }
    }
    for (int i = 0; i < cols; ++i) {
        float value = 0;
        for (int k = -sz; k <= sz; ++k) {
            value += src.ptr<uchar>(row)[i + k + sz] * kernel.ptr<float>(rowk)[k + sz];
        }

        *(ans + i) = value;
    }
}*/

void conv1dsimd(Mat src, Mat kernel, float * ans, int row, int rowk, int len) {
    if (len == -1) {
        len = src.cols;
    }
    Mat src_32;
    Mat kernel_32;

    const int alpha = 1;
    src.convertTo(src_32, CV_32FC1, alpha);

    int ksize = kernel.cols;
    int sz = kernel.cols / 2;
    copyMakeBorder(src_32, src_32, 0, 0, sz, sz, BORDER_REPLICATE);

    int step = v_float32().nlanes;
    float * sptr = src_32.ptr<float>(row);
    float * kptr = kernel.ptr<float>(rowk);
    for (int k = 0; k < ksize; ++k) {
        v_float32 kernel_wide = vx_setall_f32(kptr[k]);
        int i;
        for (i = 0; i + step < len; i += step) {
            v_float32 window = vx_load(sptr + i + k);
            v_float32 sum = vx_load(ans + i) + kernel_wide * window;
            v_store(ans + i, sum);
        }
        for (; i < len; ++i) {
            *(ans + i) += sptr[i + k] * kptr[k];
        }
    }
}

void convolute_simd(Mat src, Mat &dst, Mat kernel) {
    int rows = src.rows;
    int cols = src.cols;
    int ksize = kernel.rows;
    int sz = ksize / 2;
    dst = Mat(rows, cols, CV_32FC1);

    copyMakeBorder(src, src, sz, sz, 0, 0,BORDER_REPLICATE);

    int step = v_float32().nlanes;

    for (int i = 0; i < rows; ++i) {
        for (int k = 0; k < ksize; ++k) {
            float * ans = new float[cols];
            conv1dsimd(src, kernel, ans, i + k, k, cols);
            int j;
            for (j = 0; j + step < cols; j += step) {
                v_float32 sum = vx_load(&dst.ptr<float>(i)[j]) + vx_load(&ans[j]);
                v_store(&dst.ptr<float>(i)[j], sum);
            }
            for (; j < cols; ++j) {
                dst.ptr<float>(i)[j] += ans[j];
            }
            delete [] ans;
        }
    }

    const int alpha = 1;
    dst.convertTo(dst, CV_8UC1, alpha);
}

/*void convolute(Mat src, Mat &dst, Mat kernel) {
    int rows = src.rows;
    int cols = src.cols;
    int ksize = kernel.rows;
    int sz = ksize / 2;
    copyMakeBorder(src, src, sz, sz, 0, 0, BORDER_REPLICATE);

    float * ans = new float[cols];
    for (int i = 0; i < rows; ++i) {
        for (int k = 0; k < ksize; ++k) {
            conv1d(src, kernel, ans, i + k, k);
        }
    }
    delete [] ans;
}*/