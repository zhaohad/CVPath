//
// Created by zhaohad on 2022/12/7.
//

#ifndef INC_012_HOWTOUSETHEOPENCVPARALLEL_PARALLELCONVOLUTION_H
#define INC_012_HOWTOUSETHEOPENCVPARALLEL_PARALLELCONVOLUTION_H

#include <opencv2/core.hpp>

using namespace cv;

class ParallelConvolution : public ParallelLoopBody {
private:
    Mat mSrc;
    Mat &mDst;
    Mat mKernel;
    int mSz;
public:
    ParallelConvolution(Mat src, Mat &dst, Mat kernel);
    virtual void operator()(const Range &range) const CV_OVERRIDE;
};


#endif //INC_012_HOWTOUSETHEOPENCVPARALLEL_PARALLELCONVOLUTION_H
