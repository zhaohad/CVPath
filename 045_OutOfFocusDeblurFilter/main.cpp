#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
 * 不知道为啥，没搞定
 * */

using namespace cv;
using namespace std;

void calcPSF(Mat & outputImg, Size filterSize, int R);
void calcWnrFilter(const Mat & input_h_PSF, Mat & output_G, double nsr);
void fftshift(const Mat & inputImg, Mat & outputImg);
void filter2DFreq(const Mat & inputImg, Mat & outputImg, const Mat & H);

int main() {
    const char * fpath = "../../images/text_defocus.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }

    int R = 53;
    int snr = 5200;
    Mat imgOut;
    Rect roi = Rect(0, 0, src.cols & -2, src.rows & -2);

    Mat Hw, h;
    calcPSF(h, roi.size(), R);
    calcWnrFilter(h, Hw, 1.0 / double (snr));

    filter2DFreq(src(roi), imgOut, Hw);
    // imgOut.convertTo(imgOut, CV_8U);
    // normalize(imgOut, imgOut, 0, 255, NORM_MINMAX);

    imshow("src", src);
    // imshow("result.jpg", imgOut);
    waitKey(0);
    return 0;
}

void calcPSF(Mat & outputImg, Size filterSize, int R) {
    Mat h(filterSize, CV_32F, Scalar(0));
    Point point(filterSize.width / 2, filterSize.height / 2);
    circle(h, point, R, 255, -1, 8);
    Scalar summa = sum(h);
    outputImg = h / summa[0];
    cout << summa;
}

void calcWnrFilter(const Mat & input_h_PSF, Mat & output_G, double nsr) {
    Mat h_PSF_shifted;
    fftshift(input_h_PSF, h_PSF_shifted);
    Mat planes[2] = {Mat_<float>(h_PSF_shifted.clone()), Mat::zeros(h_PSF_shifted.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);
    split(complexI, planes);
}

void fftshift(const Mat & inputImg, Mat & outputImg) {
    outputImg = inputImg.clone();
    int cx = outputImg.cols / 2;
    int cy = outputImg.rows / 2;
    Mat q0(outputImg, Rect(0, 0, cx, cy));
    Mat q1(outputImg, Rect(cx, 0, cx, cy));
    Mat q2(outputImg, Rect(0, cy, cx, cy));
    Mat q3(outputImg, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void filter2DFreq(const Mat & inputImg, Mat & outputImg, const Mat & H) {
    Mat planes[2] = {Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F)};
    //Mat complexI;
    //merge(planes, 2, complexI);
    //dft(complexI, complexI, DFT_SCALE);

    /*Mat planesH[2] = {Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F)};
    Mat complexH;
    merge(planesH, 2, complexH);
    Mat complexIH;
    mulSpectrums(complexI, complexH, complexIH, 0);

    idft(complexIH, complexIH);
    split(complexIH, planes);
    outputImg = planes[0];*/
}