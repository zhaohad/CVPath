#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Mat result;

void calculateHistogram(Mat image, Mat * hist, int histSize);
void generateHistogram(const Mat * hist, int histSize, int cnt, Mat & outHistImg);
void getAccumulativeHist(Mat & hist, int w, int h, float out[256]) {
    Mat ratio_hist = hist / ((float) w * (float) h); // TODO test
    float ratio_sum = 0;
    for (int i = 0; i < 256; ++i) {
        ratio_sum += ratio_hist.at<float>(i);
        out[i] = ratio_sum;
    }
}

void histogramMatching(Mat & src, Mat * histSrc, Mat * histRef) {
    int w = src.cols;
    int h = src.rows;
    vector<Mat> bgr_planes;
    vector<Mat> out_planes;
    split(src, bgr_planes);
    for (int channel = 0; channel < 3; ++channel) {
        Mat img = bgr_planes.at(channel);
        float accumulative_histSrc[256];
        float accumulative_histRef[256];
        getAccumulativeHist(histSrc[channel], w, h, accumulative_histSrc);
        getAccumulativeHist(histRef[channel], w, h, accumulative_histRef);

        int map[256];
        for (int i = 0; i < 256; ++i) {
            float src_hist_bin = accumulative_histSrc[i];
            float min_diff_abs = 1000;
            int min_diff_abs_index = 0;
            for (int j = 0; j < 256; ++j) {
                float ref_hist_bin = accumulative_histRef[j];
                float diff_abs = abs(ref_hist_bin - src_hist_bin);
                if (diff_abs < min_diff_abs) {
                    min_diff_abs = diff_abs;
                    min_diff_abs_index = j;
                }
            }
            map[i] = min_diff_abs_index;
        }

        Mat mapped_img(img.rows, img.cols, img.type());
        for (int r = 0; r < h; ++r) {
            uchar * p = img.ptr<uchar>(r);
            uchar * outP = mapped_img.ptr<uchar>(r);
            for (int c = 0; c < w; ++c) {
                uchar color = p[c];
                uchar map_color = map[color];
                outP[c] = map_color;
            }
        }
        out_planes.push_back(mapped_img);
    }
    result.create(src.rows, src.cols, src.type());
    merge(out_planes, result);
}

int main() {
    const char * fpath = "../1_.png";
    const char * frefp = "../2_.png";
    const char * attem = "../a_.png";
    Mat src = imread(fpath, IMREAD_COLOR);
    Mat ref = imread(frefp, IMREAD_COLOR);
    Mat att = imread(attem, IMREAD_COLOR);
    if (src.empty() || ref.empty()) {
        cout << "Cannot open " << fpath << " or " << frefp << endl;
        return -1;
    }

    imshow("src", src);
    imshow("ref", ref);
    imshow("att", att);

    int histSize = 256;

    Mat histAttImg;
    Mat histAtt[3];
    calculateHistogram(att, histAtt, histSize);
    generateHistogram(histAtt, histSize, 3, histAttImg);
    imshow("histAttImg", histAttImg);


    Mat histSrcImg;
    Mat histRefImg;
    Mat histSrc[3];
    calculateHistogram(src, histSrc, histSize);
    generateHistogram(histSrc, histSize, 3, histSrcImg);

    Mat histRef[3];
    calculateHistogram(ref, histRef, histSize);
    generateHistogram(histRef, histSize, 3, histRefImg);

    imshow("histSrcImg", histSrcImg);
    imshow("histRefImg", histRefImg);

    histogramMatching(src, histSrc, histRef);
    imshow("result", result);

    Mat histResult[3];
    Mat histResultImg;
    calculateHistogram(result, histResult, histSize);
    generateHistogram(histResult, histSize, 3, histResultImg);
    imshow("histResultImg", histResultImg);

    waitKey(0);
    return 0;
}

void calculateHistogram(Mat image, Mat * hist, int histSize) {
    vector<Mat> bgr_planes;
    split(image, bgr_planes);

    float range[] = {0, 256};
    const float * histRange[] = {range};

    bool unifrom = true;
    bool accumulate = false;

    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), hist[0], 1, &histSize, histRange, unifrom, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), hist[1], 1, &histSize, histRange, unifrom, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), hist[2], 1, &histSize, histRange, unifrom, accumulate);
}

void generateHistogram(const Mat * hist, int histSize, int cnt, Mat & outHistImg) {
    int w = 512;
    int h = 400;
    int bin = cvRound((double) w / histSize);
    outHistImg.create(h, w, CV_8UC3);
    for (int i = 0; i < cnt; ++i) {
        Mat normal;
        normalize(hist[i], normal, 0, outHistImg.rows, NORM_MINMAX, -1, Mat());
        Scalar color;
        switch (i) {
            case 0:
                color = Scalar(255, 0, 0);
                break;
            case 1:
                color = Scalar(0, 255, 0);
                break;
            case 2:
                color = Scalar(0, 0, 255);
                break;
        }
        for (int j = 1; j < histSize; ++j) {
            line(outHistImg, Point(bin * (j - 1), h - cvRound(normal.at<float>(j - 1))), Point(bin * j, h - cvRound(normal.at<float>(j))), color);
        }
    }
}