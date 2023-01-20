import cv2 as cv
import numpy as np


def main():
    src = cv.imread("circles.jpg", cv.IMREAD_GRAYSCALE)
    dst = cv.Canny(src,  50, 200, 3)
    cdst = cv.cvtColor(dst,  cv.COLOR_GRAY2BGR)
    cdstP = np.zeros(cdst.shape, dtype=np.uint8)
    np.copyto(cdstP, cdst)
    lines = cv.HoughLines(dst, 1, np.pi / 180, 150, 0, 0)
    for item in lines[:, 0, :]:
        rho = item[0]
        theta = item[1]
        a = np.cos(theta)
        b = np.sin(theta)
        x0, y0 = b * rho, a * rho
        pt1 = [int(np.round(x0 + 1000 * (-b))), int(np.round(y0 + 1000 * (a)))]
        pt2 = [int(np.round(x0 - 1000 * (-b))), int(np.round(y0 - 1000 * (a)))]
        cv.line(cdst, pt1, pt2, [0, 0, 255], 3, cv.LINE_AA)
    cv.imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst)


    params = {
        'threshold': 10,
        'minLineLength': 10,
        'maxLineGap': 2
    }
    cv.namedWindow("Detected Lines (in red) - Probabilistic Line Transform", cv.WINDOW_AUTOSIZE)

    def threshold_onChange(th):
        params['threshold'] = th
        # a modification of the Hough transform.
        lines = cv.HoughLinesP(dst, 1.0, np.pi / 180, params['threshold'] * 5, minLineLength=float(params['minLineLength'] * 5), maxLineGap=float(params['maxLineGap'] * 5))# runs the actual detection
        dstP = np.zeros(cdstP.shape, dtype=np.uint8)
        np.copyto(dstP, cdstP)

        for item in lines[:, 0, :]:
            pt1 = [int(np.round(item[0])), int(np.round(item[1]))]
            pt2 = [int(np.round(item[2])), int(np.round(item[3]))]
            cv.line(dstP, pt1, pt2, [0, 0, 255], 3, cv.LINE_AA)


        cv.imshow("Detected Lines (in red) - Probabilistic Line Transform", dstP)

    cv.createTrackbar("threshold:", "Detected Lines (in red) - Probabilistic Line Transform", params['threshold'], 30, threshold_onChange)

    def minLineLength_onChange(minL):
        params['minLineLength'] = minL
        # a modification of the Hough transform.
        lines = cv.HoughLinesP(dst, 1.0, np.pi / 180, params['threshold'] * 5, minLineLength=float(params['minLineLength'] * 5), maxLineGap=float(params['maxLineGap'] * 5))# runs the actual detection
        dstP = np.zeros(cdstP.shape, dtype=np.uint8)
        np.copyto(dstP, cdstP)

        for item in lines[:, 0, :]:
            pt1 = [int(np.round(item[0])), int(np.round(item[1]))]
            pt2 = [int(np.round(item[2])), int(np.round(item[3]))]
            cv.line(dstP, pt1, pt2, [0, 0, 255], 3, cv.LINE_AA)

        cv.imshow("Detected Lines (in red) - Probabilistic Line Transform", dstP)

    cv.createTrackbar("minLineLength:", "Detected Lines (in red) - Probabilistic Line Transform", params['minLineLength'], 30, minLineLength_onChange)

    def maxLineGap_onChange(maxL):
        params['maxLineGap'] = maxL
        # a modification of the Hough transform.
        lines = cv.HoughLinesP(dst, 1.0, np.pi / 180, params['threshold'] * 5, minLineLength=float(params['minLineLength'] * 5), maxLineGap=float(params['maxLineGap'] * 5))# runs the actual detection
        dstP = np.zeros(cdstP.shape, dtype=np.uint8)
        np.copyto(dstP, cdstP)

        for item in lines[:, 0, :]:
            pt1 = [int(np.round(item[0])), int(np.round(item[1]))]
            pt2 = [int(np.round(item[2])), int(np.round(item[3]))]
            cv.line(dstP, pt1, pt2, [0, 0, 255], 3, cv.LINE_AA)

        cv.imshow("Detected Lines (in red) - Probabilistic Line Transform", dstP)

    cv.createTrackbar("maxLineGap:", "Detected Lines (in red) - Probabilistic Line Transform",
                      params['maxLineGap'], 30, maxLineGap_onChange)

    cv.waitKey()


if __name__ == '__main__':
    main()
