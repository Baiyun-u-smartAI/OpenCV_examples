import cv2 as cv
import numpy as np

def main():
    src = cv.imread("merge_split.jpg", cv.IMREAD_COLOR)
    (rows, cols, ch) = np.shape(src)
    hsv = cv.cvtColor(src, cv.COLOR_BGR2HSV)
    hsv = np.array(hsv, dtype=np.int16)
    hsv[:, :, 2] += 50 # 修改V通道的值

    hsv = np.maximum(hsv, np.zeros((rows, cols, ch), dtype=np.int16)) # 负数变成0
    hsv = np.minimum(hsv, np.ones((rows, cols, ch), dtype=np.int16)*255) # 超过255变成255
    hsv = np.array(hsv, dtype=np.uint8) # 类型转换
    hsv = cv.cvtColor(hsv, cv.COLOR_HSV2BGR)
    cv.imshow("+V", hsv)

    Lab = cv.cvtColor(src, cv.COLOR_BGR2Lab)
    Lab = np.array(Lab, dtype=np.int16)
    Lab[:, :, 2] -= 50  # 修改b通道的值

    Lab = np.maximum(Lab, np.zeros((rows, cols, ch), dtype=np.int16))  # 负数变成0
    Lab = np.minimum(Lab, np.ones((rows, cols, ch), dtype=np.int16) * 255)  # 超过255变成255
    Lab = np.array(Lab, dtype=np.uint8)  # 类型转换
    Lab = cv.cvtColor(Lab, cv.COLOR_Lab2BGR)
    cv.imshow("-b", Lab)


    cv.waitKey()

if __name__ == '__main__':
    main()