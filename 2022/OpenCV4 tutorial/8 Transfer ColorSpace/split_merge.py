import cv2 as cv
import numpy as np

def main():
    src = cv.imread("merge_split.jpg", cv.IMREAD_COLOR)
    (b, g, r) = cv.split(src) # 分离通道
    (b, g) = (g, b) # 交换 B 和 G 通道
    dst = cv.merge([b, g, r]) # 合并通道
    cv.imshow("split1",  dst)

    (b, g, r) = cv.split(src)  # 分离通道
    b = r # R 通道覆盖 B 通道
    (rows, cols) = np.shape(r)
    r = np.zeros((rows, cols), dtype=np.uint8) # 清空R通道
    dst = cv.merge([b, g, r])  # 合并通道
    cv.imshow("split2", dst)
    cv.waitKey()
if __name__ == '__main__':
    main()