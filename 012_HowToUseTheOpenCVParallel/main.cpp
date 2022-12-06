#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main() {
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
	waitKey();
	/*cv::Mat mat(400, 300, CV_8UC3, cv::Scalar(255, 215,  0));
	std::cout << "hello opencv\n";
	imshow("image", mat);
	cv::waitKey();*/
	return 0;
}