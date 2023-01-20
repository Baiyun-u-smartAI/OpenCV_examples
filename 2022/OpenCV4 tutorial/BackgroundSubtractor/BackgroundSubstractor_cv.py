import numpy as np
import cv2 as cv


if __name__ == "__main__":
    cap = cv.VideoCapture('LIVE Nevskiy avenue St. Petersburg Russia, Gostiny Dvor. Невский пр. Санкт-Петербург, Гостиный двор 2022-11-09 20_18-h1wly909BYw.mp4')
    fgbg = cv.bgsegm.createBackgroundSubtractorMOG()
    while True:
        ret, frame = cap.read()
        frame = cv.resize(frame, None, None, fx=0.7, fy=0.7)
        fgmask = fgbg.apply(frame)
        cv.imshow('frame', fgmask)
        k = cv.waitKey(30) & 0xff
        if k == 27:
            break
    cap.release()
    cv.destroyAllWindows()