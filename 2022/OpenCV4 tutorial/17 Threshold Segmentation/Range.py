import cv2 as cv
import numpy as np
def simple_threshold():
    src = cv.imread("merge_split.jpg")
    dst = cv.cvtColor(src, cv.COLOR_BGR2HSV)
    mask = cv.inRange(dst, np.array([28, 100, 100]), np.array([40, 255, 255]))
    cv.imshow("mask", mask)

    for i in range(0, 3):
        dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)

    dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
    cv.imshow("yellow", dst)
    cv.waitKey()
def main():
    src = cv.imread("merge_split.jpg")
    hsv = cv.cvtColor(src, cv.COLOR_BGR2HSV)
    para4Th = {'hL': 0, 'hU': 255, 'sL': 0, 'sU': 255, 'vL': 0, 'vU': 255}
    cv.namedWindow("inRange")
    def hLow_onChange(pos):
        # 克隆图像
        dst = np.zeros(hsv.shape, dtype=np.uint8)
        np.copyto(dst, hsv)

        para4Th['hL'] = pos
        mask = cv.inRange(dst, np.array([para4Th['hL'], para4Th['sL'], para4Th['vL']]), np.array([para4Th['hU'], para4Th['sU'], para4Th['vU']]))
        for i in range(0, 3):
            dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)
        dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
        cv.imshow("inRange", dst)

    def hUp_onChange(pos):
        # 克隆图像
        dst = np.zeros(hsv.shape, dtype=np.uint8)
        np.copyto(dst, hsv)

        para4Th['hU'] = pos
        mask = cv.inRange(dst, np.array([para4Th['hL'], para4Th['sL'], para4Th['vL']]), np.array([para4Th['hU'], para4Th['sU'], para4Th['vU']]))
        for i in range(0, 3):
            dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)
        dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
        cv.imshow("inRange", dst)

    def sLow_onChange(pos):
        # 克隆图像
        dst = np.zeros(hsv.shape, dtype=np.uint8)
        np.copyto(dst, hsv)

        para4Th['sL'] = pos
        mask = cv.inRange(dst, np.array([para4Th['hL'], para4Th['sL'], para4Th['vL']]), np.array([para4Th['hU'], para4Th['sU'], para4Th['vU']]))
        for i in range(0, 3):
            dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)
        dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
        cv.imshow("inRange", dst)

    def sUp_onChange(pos):
        # 克隆图像
        dst = np.zeros(hsv.shape, dtype=np.uint8)
        np.copyto(dst, hsv)

        para4Th['sU'] = pos
        mask = cv.inRange(dst, np.array([para4Th['hL'], para4Th['sL'], para4Th['vL']]), np.array([para4Th['hU'], para4Th['sU'], para4Th['vU']]))
        for i in range(0, 3):
            dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)
        dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
        cv.imshow("inRange", dst)

    def vLow_onChange(pos):
        # 克隆图像
        dst = np.zeros(hsv.shape, dtype=np.uint8)
        np.copyto(dst, hsv)

        para4Th['vL'] = pos
        mask = cv.inRange(dst, np.array([para4Th['hL'], para4Th['sL'], para4Th['vL']]), np.array([para4Th['hU'], para4Th['sU'], para4Th['vU']]))
        for i in range(0, 3):
            dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)
        dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
        cv.imshow("inRange", dst)

    def vUp_onChange(pos):
        # 克隆图像
        dst = np.zeros(hsv.shape, dtype=np.uint8)
        np.copyto(dst, hsv)

        para4Th['vU'] = pos
        mask = cv.inRange(dst, np.array([para4Th['hL'], para4Th['sL'], para4Th['vL']]), np.array([para4Th['hU'], para4Th['sU'], para4Th['vU']]))
        for i in range(0, 3):
            dst[:, :, i] = cv.bitwise_and(src[:, :, i], mask)
        dst = cv.addWeighted(src, 0.2, dst, 0.8, 0)
        cv.imshow("inRange", dst)
    cv.createTrackbar("hL", "inRange", 0, 255, hLow_onChange)  # 创建滑杆
    cv.createTrackbar("sL", "inRange", 0, 255, sLow_onChange)  # 创建滑杆
    cv.createTrackbar("vL", "inRange", 0, 255, vLow_onChange)  # 创建滑杆
    cv.createTrackbar("hU", "inRange", 255, 255, hUp_onChange)  # 创建滑杆
    cv.createTrackbar("sU", "inRange", 255, 255, sUp_onChange)  # 创建滑杆
    cv.createTrackbar("vU", "inRange", 255, 255, vUp_onChange)  # 创建滑杆



    cv.waitKey()

if __name__ == '__main__':
    main()
