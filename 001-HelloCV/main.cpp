#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main() {
    cv::Mat mat(400,300,CV_8UC3, cv::Scalar(255,215,0));
    std::cout << "hello opencv\n";
    imshow("image",mat);
    cv::waitKey();
    return 0;
}