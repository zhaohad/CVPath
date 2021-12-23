#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main() {
    string image_path = samples::findFile("starry_night.jpg");
    cout << image_path << endl;
    // Mat img = imread(image_path);
    // Mat img = imread(image_path, IMREAD_COLOR);
    // Mat img = imread(image_path, IMREAD_UNCHANGED);
    Mat img = imread(image_path, IMREAD_GRAYSCALE);

    if (img.empty())
    {
        cout << "Could not read the image: " << image_path << endl;
        return 1;
    }

    imshow("Display window", img);

    int k = waitKey(0);
    if (k == 's')
    {
        imwrite("starry_night.png", img);
    }
    return 0;
}
