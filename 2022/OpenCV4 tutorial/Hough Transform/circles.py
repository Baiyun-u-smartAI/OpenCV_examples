import cv2 as cv
import numpy as np


def main():
    src = cv.imread("circles.jpg")
    class Params:
        minRadius = 0
        maxRadius = 100
    gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)

    (rows, cols) = gray.shape
    cv.namedWindow("circles", cv.WINDOW_AUTOSIZE)
    def minRadius_onChange(minR):
        Params.minRadius = minR
        circles = cv.HoughCircles(gray, cv.HOUGH_GRADIENT, 2, rows / 4, 200, 100, Params.minRadius * 4, Params.maxRadius * 4)
        img = np.zeros(src.shape, dtype=np.uint8)
        np.copyto(img, src)
        circles = np.uint16(np.around(circles))
        for item in circles[0, :]:
            cv.circle(img, (item[0], item[1]), 3, [0, 255, 0], -1, 8, 0)
            cv.circle(img, (item[0], item[1]), item[2], [255, 0, 0], 3, 8, 0)
        cv.imshow("circles", img)

    cv.createTrackbar("minRadius: ", "circles", Params.minRadius, 100, minRadius_onChange)

    def maxRadius_onChange(maxR):

        Params.maxRadius = maxR
        circles = cv.HoughCircles(gray, cv.HOUGH_GRADIENT, 2, rows / 4, param1=200, param2=100, minRadius=Params.minRadius * 4, maxRadius=Params.maxRadius * 4)
        img = np.zeros(src.shape, dtype=np.uint8)
        np.copyto(img, src)
        circles = np.uint16(np.around(circles))
        for item in circles[0, :]:
            cv.circle(img, (item[0], item[1]), 3, [0, 255, 0], -1, 8, 0)
            cv.circle(img, (item[0], item[1]), item[2], [255, 0, 0], 3, 8, 0)
        cv.imshow("circles", img)

    cv.createTrackbar("maxRadius: ", "circles", Params.maxRadius, 100, maxRadius_onChange)


    cv.waitKey()


if __name__ == '__main__':
    main()
