import cv2 as cv
import numpy as np


def main():
    src = cv.imread("merge_split.jpg")
    # todo 变换前的在src四个点
    before = np.array([[18, 221], [270, 0], [428, 98], [176, 336]], dtype=np.float32)
    # todo 需要变换到dst图上的对应四个点位置
    after = np.array([[0, 0], [300, 0], [300, 200], [0, 200]], dtype=np.float32)
    
    transMat = cv.getPerspectiveTransform(before, after)  # step 求解变换矩阵
    dst = cv.warpPerspective(src, transMat, (300, 200))  # step 应用变换得到图片300x200大小
    cv.imshow("after wrapping", dst)
    cv.waitKey()


if __name__ == '__main__':
    main()
