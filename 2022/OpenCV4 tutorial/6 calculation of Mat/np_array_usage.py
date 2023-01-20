import cv2 as cv
import numpy as np

def main():
    a = np.array([[[255,155,0],[0, 155, 0]]],dtype=np.int16)
    (rows, cols, ch) = np.shape(a)
    # 一般python不可以直接对图像进行运算，除非转换成更高精度的类型，然后进行截断处理，然后再恢复uint8类型
    a[:, :, 0] += 255 # B通道+255，会出现>255
    a[:, :, 1] -= 255 # G通道-255，会出现<0
    print(a)
    a = np.maximum(a, np.zeros((rows, cols, ch), dtype=np.int16)) # 负数变成0
    a = np.minimum(a, np.ones((rows, cols, ch), dtype=np.int16)*255) # 超过255变成255
    print(a)
    # a = np.array(a, dtype=np.uint8) # 类型转换
    # image = cv.imread("aaa.jpg")
    # ROI = image[50:304, 228:490, :] # 截取 x:[228,490] y:[50,304]的区域，注意ROI和image没有联系
    # image[50:304, 228:490, :] = ROI/2 # 降低亮度
    # cv.imshow("aaa.jpg", image) # 显示整图
    # cv.waitKey()
    # cv.destroyAllWindows()

if __name__ == '__main__':
    main()