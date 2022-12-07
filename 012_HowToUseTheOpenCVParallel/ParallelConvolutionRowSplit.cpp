//
// Created by zhaohad on 2022/12/7.
//

#include "ParallelConvolutionRowSplit.h"

ParallelConvolutionRowSplit::ParallelConvolutionRowSplit(Mat src, Mat &dst, Mat kernel) : mSrc(src), mDst(dst), mKernel(kernel) {
    mSz = mKernel.rows / 2;
}

// ParallelConvolutionRowSplit::ParallelConvolutionRowSplit() {}

void ParallelConvolutionRowSplit::operator()(const Range &range) const {
    int cols = mDst.cols;
    for (int i = range.start; i < range.end; ++i) {
        for (int j = 0; j < cols; ++j) {
            double value = 0;
            for (int k = -mSz; k <= mSz; ++k) {
                for (int l = -mSz; l <= mSz; ++l) {
                    value += mKernel.ptr<double>(k + mSz)[l + mSz] * mSrc.ptr(i + mSz + k)[j + l + mSz];

                }
            }
            mDst.ptr(i)[j] = saturate_cast<uchar>(value);
        }
    }
}
