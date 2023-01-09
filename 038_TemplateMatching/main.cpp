#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

bool use_mask;
Mat img;
Mat templ;
Mat mask;
Mat result;

int match_method;

#define WN "Source Image"
#define RE "Result window"

void MatchingMethod(int, void *);

int main() {
    const char * fpath = "../../images/Template_Matching_Original_Image.jpg";
    const char * ftemp = "../../images/Template_Matching_Template_Image.jpg";
    /*const char * fpath = "../../images/lena_tmpl.jpg";
    const char * ftemp = "../../images/tmpl.png";
    use_mask = true;*/
    const char * fmask = "../../images/mask.png";

    img = imread(fpath, IMREAD_COLOR);
    templ = imread(ftemp, IMREAD_COLOR);
    mask = imread(fmask, IMREAD_COLOR);

    if (img.empty() || templ.empty() || use_mask && mask.empty()) {
        cout << "Cannot open " << fpath << " or " << ftemp << " or " << fmask << endl;
        return -1;
    }

    namedWindow(WN);
    namedWindow(RE);

    const char * trackbar_lable = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar(trackbar_lable, WN, &match_method, 5, MatchingMethod);

    MatchingMethod(0, NULL);

    if (use_mask) {
        imshow("mask", mask);
    }
    imshow("templ", templ);
    waitKey();
    return 0;
}

void MatchingMethod(int, void *) {
    TemplateMatchModes method;
    Mat img_display;
    Mat img_mask;
    img.copyTo(img_display);
    mask.copyTo(img_mask);

    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create(result_rows, result_cols, CV_32FC1);

    switch (match_method) {
        case 0:
            method = TM_SQDIFF;
            break;
        case 1:
            method = TM_SQDIFF_NORMED;
            break;
        case 2:
            method = TM_CCORR;
            break;
        case 3:
            method = TM_CCORR_NORMED;
            break;
        case 4:
            method = TM_CCOEFF;
            break;
        case 5:
            method = TM_CCOEFF_NORMED;
            break;
    }

    bool method_accepts_mask = (TM_SQDIFF == method || method == TM_CCORR_NORMED);
    if (use_mask && method_accepts_mask) {
        matchTemplate(img, templ, result, method, img_mask);
    } else {
        matchTemplate(img, templ, result, method);
    }

    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED) {
        matchLoc = minLoc;
    } else {
        matchLoc = maxLoc;
    }

    rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

    imshow(WN, img_display);
    imshow(RE, result);
}