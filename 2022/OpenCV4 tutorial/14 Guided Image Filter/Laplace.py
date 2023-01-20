import cv2 as cv
import numpy as np


def main():
    src = cv.imread("Robert_Delaunay,_1913,_Premier_Disque.jpg")
    # todo 使用filter2D进行Laplace滤波
    kernel = np.array([[0, 1, 0], [1, -4, 1], [0, 1, 0]], dtype=np.float32)
    tmp = np.array(src, dtype=np.float32) # 因为涉及负数要转换类型
    tmp = cv.filter2D(tmp, -1, kernel)
    tmp = np.abs(tmp)# 滤波后求绝对值
    dst = np.array(tmp, dtype=np.uint8)# 输出前转换为CV_8UC3->dst
    cv.imshow("Laplace(filter2D)", dst)

    # todo 使用Laplacian函数
    dst = cv.Laplacian(src, -1, ksize=3)
    cv.imshow("Laplacian", dst)
    cv.waitKey()

if __name__ == '__main__':
    main()
