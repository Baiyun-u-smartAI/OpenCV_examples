import sys
import cv2 as cv

if __name__ == "__main__":
    stitcher = cv.Stitcher_create(cv.STITCHER_PANORAMA)
    panos = []
    panos.append(cv.imread("1403636579763555584cam0.png"))
    panos.append(cv.imread("1403636579763555584cam1.png"))
    status, out = stitcher.stitch(panos)
    if status != cv.STITCHER_OK:
        print(f'Can\'t stitch images, error code = {status}')
        sys.exit(1)
    cv.imshow("out", out)
    cv.waitKey()
    cv.destroyAllWindows()