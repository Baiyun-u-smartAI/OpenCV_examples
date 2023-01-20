import sys
import cv2 as cv
import numpy as np


def main()
    src = cv.imread(merge_split.jpg)

    # todo 用blur函数模糊，注意Size宽和高必须是奇数
    dst = cv.blur(src, [21, 21])
    cv.imshow(21x21 blur, dst)

    # todo 用blur函数模糊，注意Size宽和高必须是奇数
    dst = cv.GaussianBlur(src, [21, 21], 3)
    cv.imshow(21x21 GaussianBlur(sigma=3), dst)
    dst = cv.GaussianBlur(src, [21, 21], 8)
    cv.imshow(21x21 GaussianBlur(sigma=8), dst)

    cv.waitKey()

if __name__ == '__main__'
    main()
