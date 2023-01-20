import cv2 as cv


def main():

    src = cv.imread("merge_split.jpg")

    """
        resize 常用模式：
            INTER_NEAREST 近邻插值
            INTER_LINEAR 线性插值
            INTER_CUBIC 三次插值
            INTER_AREA 
            INTER_LANCZOS4 三角插值
            INTER_LINEAR_EXACT
            INTER_NEAREST_EXACT
    """
    # 第2个参数为None的时候，第4(fx)、5(fy)个参数的两个浮点数，分别代表图片的宽放缩倍数、高放缩倍数
    dst = cv.resize(src, None, None, 3., 2., cv.INTER_NEAREST)
    cv.imshow("INTER_NEAREST", dst)
    dst = cv.resize(src, None, fx=3., fy=2., interpolation=cv.INTER_LINEAR)
    cv.imshow("INTER_LINEAR", dst)
    cv.waitKey()


if __name__ == '__main__':
    main()