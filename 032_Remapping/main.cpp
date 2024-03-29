#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

#define WN "Remap demo"

void update_map(int &ind, Mat &map_x, Mat &map_y);

int main() {
    const char * fpath = "../../images/lena.jpg";
    Mat src = imread(fpath, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot open " << fpath << endl;
        return -1;
    }
    Mat dst(src.size(), src.type());
    Mat map_x(src.size(), CV_32FC1);
    Mat map_y(src.size(), CV_32FC1);

    imshow("src", src);

    namedWindow(WN, WINDOW_AUTOSIZE);

    int ind = 0;
    while (1) {
        update_map(ind, map_x, map_y);
        remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

        imshow(WN, dst);
        char c = waitKey(1000);
        if (c == 27) {
            break;
        }
    }
    cout << "mapx(0, 0): " << map_x.at<float>(0, 0) << " mapy(0, 0): " << map_y.at<float>(0, 0) << endl;
    cout << "src(0, 0): " << src.at<int>(0, 0) << " dst(0, 0): " << dst.at<int>(0, 0) << endl;
    return 0;
}

void update_map(int &ind, Mat &map_x, Mat &map_y) {
    for (int i = 0; i < map_x.rows; ++i) {
        for (int j = 0; j < map_x.cols; ++j) {
            switch (ind) {
                case 0:
                    if (j > map_x.cols * 0.25 && j < map_x.cols * 0.75 && i > map_x.rows * 0.25 && i < map_x.rows * 0.75) {
                        map_x.at<float>(i, j) = 2 * (j - map_x.cols * 0.25f) + 0.5f;
                        map_y.at<float>(i, j) = 2 * (i - map_x.rows * 0.25f) + 0.5f;
                    } else {
                        map_x.at<float>(i, j) = 0;
                        map_y.at<float>(i, j) = 0;
                    }
                    break;
                case 1:
                    map_x.at<float>(i, j) = j;
                    map_y.at<float>(i, j) = map_x.rows - i;
                    break;
                case 2:
                    map_x.at<float>(i, j) = map_x.cols - j;
                    map_y.at<float>(i, j) = i;
                    break;
                case 3:
                    map_x.at<float>(i, j) = map_x.cols - j;
                    map_y.at<float>(i, j) = map_x.rows - i;
                    break;
                default:
                    break;
            }
        }
    }
    ind = (ind + 1) % 4;
}