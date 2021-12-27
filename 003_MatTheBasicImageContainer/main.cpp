#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat m8uc3(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "m8uc3:" << endl;
    cout << m8uc3 << endl;

    Mat m8uc4(2, 2, CV_8UC4, Scalar(0, 0, 255, 0));
    cout << "m8uc4:" << endl;
    cout << m8uc4 << endl;

    Mat m8uc2(2, 2, CV_8UC3, Scalar(0, 0, 255));
    m8uc2.create(4, 4, CV_8UC(2));
    cout << "m8uc2:" << endl;
    cout << m8uc2 << endl;

    int sz[3] = {2, 2, 2};
    Mat L(3, sz, CV_8UC(1), Scalar::all(1));
    cout << "L: " << endl;
    // cout << L << endl;

    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E: " << endl;
    cout << E << endl;

    Mat O = Mat::ones(4, 4, CV_32F);
    cout << "O: " << endl;
    cout << O << endl;

    Mat Z = Mat::zeros(4, 4, CV_8UC1);
    cout << "Z: " << endl;
    cout << Z << endl;

    Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C: " << endl;
    cout << C << endl;
    C = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
    cout << "C: " << endl;
    cout << C << endl;

    Mat RowClone = C.row(1).clone();
    cout << "RowClone: " << endl;
    cout << RowClone << endl;

    Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255));
    cout << "R: " << endl;
    cout << R << endl;
    cout << "R (format:FMT_PYTHON): " << endl;
    cout << format(R, Formatter::FMT_PYTHON) << endl;
    cout << "R (format:FMT_CSV): " << endl;
    cout << format(R, Formatter::FMT_CSV) << endl;
    cout << "R (format:FMT_NUMPY): " << endl;
    cout << format(R, Formatter::FMT_NUMPY) << endl;
    cout << "R (format:FMT_C): " << endl;
    cout << format(R, Formatter::FMT_C) << endl;
    cout << "R (format:FMT_MATLAB): " << endl;
    cout << format(R, Formatter::FMT_MATLAB) << endl;

    Point2f P(5, 1);
    cout << "P: " << endl;
    cout << P << endl;

    Point3f  P3f(2, 6, 7);
    cout << "P3f: " << endl;
    cout << P3f << endl;

    vector<float> v;
    v.push_back((float) CV_PI);
    v.push_back(2);
    v.push_back(3.01f);
    cout << "Vector of floats via Mat: " << endl;
    cout << Mat(v) << endl;

    vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i) {
        vPoints[i] = Point2f((float) (i * 5), (float) (i * 7));
    }
    cout << "A vector of 2D points:" << endl;
    cout << vPoints << endl;
    return 0;
}
