//
// Created by zhaohad on 2022/12/7.
//

#include "ParallelConvolution.h"

ParallelConvolution::ParallelConvolution(Mat src, Mat &dst, Mat kernel) : mSrc(src), mDst(dst), mKernel(kernel) {
    mSz = mKernel.rows / 2;
}

void ParallelConvolution::operator()(const Range &range) const {
    for (int r = range.start; r < range.end; ++r) {
        int i = r / mSrc.cols;
        int j = r % mSrc.rows;

        double value = 0;
        for (int k = -mSz; k <= mSz; ++k) {
            const uchar * sptr = mSrc.ptr(i + mSz + k);
            for (int l = -mSz; l <= mSz; ++l) {
                value += sptr[j + l + mSz] * mKernel.ptr<double>(k + mSz)[l + mSz];
            }
        }
        mDst.ptr(i)[j] = saturate_cast<uchar>(value);
    }
}
