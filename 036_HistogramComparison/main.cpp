#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main() {
    const char * f1 = "../../images/Histogram_Comparison_Source_0.jpg";
    const char * f2 = "../../images/Histogram_Comparison_Source_1.jpg";
    const char * f3 = "../../images/Histogram_Comparison_Source_2.jpg";

    Mat src_base = imread(f1);
    Mat src_test1 = imread(f2);
    Mat src_test2 = imread(f3);
    if (src_base.empty() || src_test1.empty() || src_test2.empty()) {
        cout << "Cannot open " << f1 << " or " << f2 << " or " << f3 << endl;
        return -1;
    }

    Mat hsv_base, hsv_test1, hsv_test2;
    cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
    cvtColor(src_test1, hsv_test1, COLOR_BGR2HSV);
    cvtColor(src_test2, hsv_test2, COLOR_BGR2HSV);

    Mat hsv_half_down = hsv_base(Range(hsv_base.rows / 2, hsv_base.rows), Range(0, hsv_base.cols));

    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = {h_bins, s_bins};

    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};;

    const float * ranges[] = {h_ranges, s_ranges};

    int channels[] = {0, 1};;

    Mat hist_base;
    Mat hist_half_down;
    Mat hist_test1;
    Mat hist_test2;

    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false);
    normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
    normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());

    for (int compare_method = 0; compare_method < 4; ++compare_method) {
        double base_base = compareHist(hist_base, hist_base, compare_method);
        double base_half = compareHist(hist_base, hist_half_down, compare_method);
        double base_test1 = compareHist(hist_base, hist_test1, compare_method);
        double base_test2 = compareHist(hist_base, hist_test2, compare_method);

        cout << "Method " << compare_method << " Perfect, Base-Half, Base-Test(1), Base-Test(2) : "
             <<  base_base << " / " << base_half << " / " << base_test1 << " / " << base_test2 << endl;
    }
    return 0;
}