import numpy as np
import cv2 as cv
import glob

def _draw(img, corners, imgpts):
    corner = np.array(corners[0].ravel()).astype(dtype=np.int16)

    img = cv.line(img, corner, np.array(imgpts[0].ravel()).astype(dtype=np.int16), (255,0,0), 5)
    img = cv.line(img, corner, np.array(imgpts[1].ravel()).astype(dtype=np.int16), (0,255,0), 5)
    img = cv.line(img, corner, np.array(imgpts[2].ravel()).astype(dtype=np.int16), (0,0,255), 5)
    return img

def draw(img, corners, imgpts):
    imgpts = np.int32(imgpts).reshape(-1,2)
    # draw ground floor in green
    img = cv.drawContours(img, [imgpts[:4]],-1,(0,255,0),-3)
    # draw pillars in blue color
    for i,j in zip(range(4),range(4,8)):
        img = cv.line(img, tuple(imgpts[i]), tuple(imgpts[j]),(255,0,0),3)
    # draw top layer in red color
    img = cv.drawContours(img, [imgpts[4:]],-1,(0,0,255),3)
    return img



if __name__ == "__main__":
    mtx = np.array([ [2.8125299882607928e+03, 0., 1.8235000000000000e+03], [0., 2.8125299882607928e+03, 1.3675000000000000e+03], [0., 0., 1. ]])
    dist = np.array([ 4.5645665323650574e-02, -9.4368813116504080e-02, 0., 0., 8.7550271042410616e-02 ])
    criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    objp = np.zeros((9 * 6, 3), np.float32)
    objp[:, :2] = np.mgrid[0:9, 0:6].T.reshape(-1, 2)
    print(objp)
    _axis = np.float32([[3, 0, 0], [0, 3, 0], [0, 0, -3]]).reshape(-1, 3)
    axis = np.float32([[0, 0, 0], [0, 3, 0], [3, 3, 0], [3, 0, 0],
                       [0, 0, -3], [0, 3, -3], [3, 3, -3], [3, 0, -3]])
    for fname in glob.glob(r'.\IMG_20221028*.jpg'):
        img = cv.imread(fname)
        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        ret, corners = cv.findChessboardCorners(gray, (9, 6), None)
        if ret == True:
            corners2 = cv.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)

            # Find the rotation and translation vectors.
            ret, rvecs, tvecs = cv.solvePnP(objp, corners2, mtx, dist)
            # project 3D points to image plane
            imgpts, jac = cv.projectPoints(axis, rvecs, tvecs, mtx, dist)

            img = draw(img, corners2, imgpts)
            img = cv.resize(img, None, fx=.3, fy=.3)
            cv.imshow('img', img)
            k = cv.waitKey(0) & 0xFF
            # if k == ord('s'):
            #     cv.imwrite(fname[:6] + '.png', img)
    cv.destroyAllWindows()