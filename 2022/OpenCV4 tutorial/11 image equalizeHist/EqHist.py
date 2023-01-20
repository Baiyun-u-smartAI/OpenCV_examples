import cv2 as cv


def main():

    src = cv.imread("dark.jfif", cv.IMREAD_COLOR)
    gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY) # 得到灰度图
    cv.imshow("gray origin", gray) # 显示灰度图
    dst = cv.equalizeHist(gray) # 应用直方图均衡化
    cv.imshow("eq", dst) # 显示
    cv.waitKey()


if __name__ == '__main__':
    main()