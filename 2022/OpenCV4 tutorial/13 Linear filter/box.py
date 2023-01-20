import cv2 as cv
import numpy as np


def main():
    src = cv.imread("merge_split.jpg")
    # todo 用filter2D做box filter
    # 直接赋值的方法定义线性滤波核kernel
    kernel = np.array([[1, 1, 1]*3], dtype=np.float32)
    kernel = kernel/np.sum(kernel) # 归一化
    dst = cv.filter2D(src, -1, kernel) # 线性滤波
    cv.imshow("3x3 Box(filter2D)", dst)


    # 用np.ones生成线性滤波核kernel
    kernel = np.ones([20, 20], dtype=np.float32)
    kernel = kernel / np.sum(kernel)  # 归一化
    dst = cv.filter2D(src, -1, kernel)  # 线性滤波
    cv.imshow("20x20 Box(filter2D)", dst)


    # todo 用boxFilter
    dst = cv.boxFilter(src, -1, [20, 20])
    cv.imshow("20x20 Box(boxFilter)", dst)
    cv.waitKey()
if __name__ == '__main__':
    main()