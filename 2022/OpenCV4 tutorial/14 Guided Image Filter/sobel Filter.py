import cv2 as cv
import numpy as np


def main():
    src = cv.imread("Robert_Delaunay,_1913,_Premier_Disque.jpg")
    # todo 使用filter2D进行导向滤波
    kernel = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], dtype=np.float32)
    tmp = np.array(src, dtype=np.float32) # 因为涉及负数要转换类型
    tmp = cv.filter2D(tmp, -1, kernel)
    tmp = np.abs(tmp)# 滤波后求绝对值
    dst = np.array(tmp, dtype=np.uint8)# 输出前转换为CV_8UC3->dst
    cv.imshow("dx(filter2D)", dst)

    # todo 使用Sobel进行导向滤波
    dst = cv.Sobel(src, -1, 1, 0, ksize=3)# 第4~5个变量分别为dx, dy；dx和dy为求导次数
    cv.imshow("dx(Sobel)", dst)
    dst = cv.Sobel(src, -1, 0, 1, ksize=3)  # 第4~5个变量分别为dx, dy；dx和dy为求导次数
    cv.imshow("dy(Sobel)", dst)

    cv.waitKey()

if __name__ == '__main__':
    main()