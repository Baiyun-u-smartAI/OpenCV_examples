import cv2 as cv
import numpy as np

def main():
    src = cv.imread("binary-icon-30.bmp", cv.IMREAD_GRAYSCALE)
    (retval, labels, stats, centroids) = cv.connectedComponentsWithStats(src)

    bg = np.ones(labels.shape, dtype=np.uint8) * 255
    (rows, cols) = bg.shape
    (r, c) = stats.shape
    for i in range(0, rows):
        for j in range(0, cols):
            if labels[i][j] == 0:
                bg[i][j] = 0
    bg = cv.cvtColor(bg, cv.COLOR_GRAY2BGR)


    _labels = np.array(labels, dtype=np.uint8)
    dst = cv.applyColorMap(_labels ** 2, cv.COLORMAP_HSV)
    dst = cv.bitwise_and(dst, bg)

    for i in range(1, r):
        (x, y, w, h) = (stats[i][0], stats[i][1],stats[i][2],stats[i][3])
        cv.rectangle(dst, [x, y, w, h], [255, 255, 255], 2) # 线宽2

    cv.imshow("", dst)
    cv.waitKey()

if __name__ == '__main__':
    main()
