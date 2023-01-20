import cv2 as cv
import numpy as np
import sys

def main():
    src = cv.imread("CantonTower.png")
    gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)


    params = {
        'thresh': 200, 'blockSize': 2, 'border_t': cv.BORDER_DEFAULT}

    cv.namedWindow("Source image")
    cv.namedWindow("Corners detected")
    cv.imshow("Source image", src)
    def Threshold_onChange(_thresh):
        if int(params['border_t']) == 3 or int(params['border_t']) == 5:
            print("border type cannot be BorderTypes.Wrap(3) or BorderTypes.Transparent(5)", file=sys.stderr)
            return None
        params['thresh'] = _thresh
        dst = cv.cornerHarris(gray, params['blockSize'], 3, .04, borderType=params['border_t'])
        dst_norm = np.empty(dst.shape, dtype=np.float32)
        cv.normalize(dst, dst_norm, 0, 255, cv.NORM_MINMAX, dtype=cv.CV_32FC1)
        dst_norm_scaled = cv.convertScaleAbs(dst_norm)
        dst_norm_scaled = cv.cvtColor(dst_norm_scaled, cv.COLOR_GRAY2BGR)
        dst_norm_scaled = np.asarray(dst_norm_scaled, dtype=np.uint8)
        (rows, cols) = dst_norm.shape
        for i in range(rows):
            for j in range(cols):
                if dst_norm[i][j] > params['thresh']:
                    cv.circle(dst_norm_scaled, [j, i], 5, [0, 0, 255], 2, cv.LINE_AA)
        cv.imshow("Corners detected", dst_norm_scaled)


    cv.createTrackbar("Threshold: ", "Source image", params['thresh'], 255, Threshold_onChange)

    def border_onChange(b_t):
        if b_t == 3 or b_t == 5:
            print("border type cannot be BorderTypes.Wrap(3) or BorderTypes.Transparent(5)", file=sys.stderr)
            return None
        elif b_t == 6:
            params['border_t'] = cv.BORDER_ISOLATED
        else:
            params['border_t'] = b_t
        dst = cv.cornerHarris(gray, params['blockSize'], 3, .04, borderType=params['border_t'])
        dst_norm = np.empty(dst.shape, dtype=np.float32)
        cv.normalize(dst, dst_norm, 0, 255, cv.NORM_MINMAX, dtype=cv.CV_32FC1)
        dst_norm_scaled = cv.convertScaleAbs(dst_norm)
        dst_norm_scaled = cv.cvtColor(dst_norm_scaled, cv.COLOR_GRAY2BGR)
        dst_norm_scaled = np.asarray(dst_norm_scaled, dtype=np.uint8)
        (rows, cols) = dst_norm.shape
        for i in range(rows):
            for j in range(cols):
                if dst_norm[i][j] > params['thresh']:
                    cv.circle(dst_norm_scaled, [j, i], 5, [0, 0, 255], 2, cv.LINE_AA)
        cv.imshow("Corners detected", dst_norm_scaled)

    cv.createTrackbar("border: ", "Source image", params['border_t'], 6, border_onChange)

    def blockSize_onChanged(block_s):
        if int(params['border_t']) == 3 or int(params['border_t']) == 5:
            print("border type cannot be BorderTypes.Wrap(3) or BorderTypes.Transparent(5)", file=sys.stderr)
            return None
        params['blockSize'] = block_s
        dst = cv.cornerHarris(gray, params['blockSize'], 3, .04, borderType=params['border_t'])
        dst_norm = np.empty(dst.shape, dtype=np.float32)
        cv.normalize(dst, dst_norm, 0, 255, cv.NORM_MINMAX, dtype=cv.CV_32FC1)
        dst_norm_scaled = cv.convertScaleAbs(dst_norm)
        dst_norm_scaled = cv.cvtColor(dst_norm_scaled, cv.COLOR_GRAY2BGR)
        dst_norm_scaled = np.asarray(dst_norm_scaled, dtype=np.uint8)
        (rows, cols) = dst_norm.shape
        for i in range(rows):
            for j in range(cols):
                if dst_norm[i][j] > params['thresh']:
                    cv.circle(dst_norm_scaled, [j, i], 5, [0, 0, 255], 2, cv.LINE_AA)
        cv.imshow("Corners detected", dst_norm_scaled)
    cv.createTrackbar("blockSize: ", "Source image", params['blockSize'], 12, blockSize_onChanged)
    cv.waitKey()


if __name__ == '__main__':
    main()
