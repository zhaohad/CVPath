#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    // 慢，效果也不太好


    const char * fpath_src = "../../images/generalized_hough_image.jpg";
    const char * fpath_t = "../../images/generalized_hough_template.jpg";

    Mat image = imread(fpath_src, IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot open " << fpath_src << endl;
        return -1;
    }
    Mat templ = imread(fpath_t, IMREAD_GRAYSCALE);
    if (templ.empty()) {
        cout << "Cannot open " << fpath_t << endl;
        return -1;
    }

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    vector<Vec4f> positionBallard;
    vector<Vec4f> positionGuil;

    int w = templ.cols;
    int h = templ.rows;

    Ptr<GeneralizedHoughBallard> ballard = createGeneralizedHoughBallard();
    ballard->setMinDist(10);
    ballard->setLevels(360);
    ballard->setDp(2);
    ballard->setMaxBufferSize(1000);
    ballard->setVotesThreshold(40);

    ballard->setCannyLowThresh(30);
    ballard->setCannyHighThresh(110);
    ballard->setTemplate(templ);

    Ptr<GeneralizedHoughGuil> guil = createGeneralizedHoughGuil();
    guil->setMinDist(10);
    guil->setLevels(360);
    guil->setDp(3);
    guil->setMaxBufferSize(1000);

    guil->setMinAngle(0);
    guil->setMaxAngle(360);
    guil->setAngleStep(1);
    guil->setAngleThresh(1500);

    guil->setMinScale(0.5);
    guil->setMaxScale(2.0);
    guil->setScaleStep(0.05);
    guil->setScaleThresh(50);

    guil->setPosThresh(10);

    guil->setCannyLowThresh(30);
    guil->setCannyHighThresh(110);

    guil->setTemplate(templ);

    ballard->detect(grayImage, positionBallard);
    guil->detect(grayImage, positionGuil);

    for (vector<Vec4f>::iterator iter = positionBallard.begin(); iter != positionBallard.end(); ++iter) {
        RotatedRect  rRect = RotatedRect(Point2f((*iter)[0], (*iter)[1]), Size2f(w * (*iter)[2], h * (*iter)[2]), (*iter)[3]);
        Point2f  vertices[4];
        rRect.points(vertices);
        for (int i = 0; i < 4; ++i) {
            line(image, vertices[i], vertices[(i  + 1) % 4], Scalar(255, 0, 0), 2);
        }
    }

    for (vector<Vec4f>::iterator iter = positionGuil.begin(); iter != positionGuil.end(); ++iter) {
        RotatedRect rRect = RotatedRect(Point2f((*iter)[0], (*iter)[1]), Size2f(w * (*iter)[2], h * (*iter)[2]), (*iter)[3]);
        Point2f  vertices[4];
        rRect.points(vertices);
        for (int i = 0; i < 4; ++i) {
            line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
        }
    }

    imshow("image", image);
    imshow("templ", templ);
    waitKey();
    return 0;
}