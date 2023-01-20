import cv2 as cv
import numpy as np


def main():
    src = cv.imread("Robert_Delaunay,_1913,_Premier_Disque.jpg")
    # todo Sobel求dx和dy
    tmp = cv.Sobel(src, -1, 1, 0, 3) # tmp: dx
    cv.imshow("dx", tmp)
    grad_x = np.array(tmp, dtype=np.float32) # 转化为float32类型，np.sqrt要求格式为float
    tmp = cv.Sobel(src, -1, 0, 1, 3)  # tmp: dy
    cv.imshow("dy", tmp)
    grad_y = np.array(tmp, dtype=np.float32)  # 转化为float32类型，np.sqrt要求格式为float

    # todo 计算梯度值
    tmp = np.sqrt(grad_x ** 2 + grad_y ** 2)
    dst = np.array(tmp, dtype=np.uint8)
    cv.imshow("Grad", dst)

    cv.waitKey()

if __name__ == '__main__':
    main()
