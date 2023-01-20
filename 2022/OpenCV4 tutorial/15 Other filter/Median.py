import sys
import cv2 as cv


def main():
    src = cv.imread("Robert_Delaunay,_1913,_Premier_Disque.jpg")
    cv.namedWindow("MedianBlur") # 创建窗口

    def ksize_onChange(pos):
        if pos % 2 == 1:# step medianBlur算法要求ksize是奇数
            dst = cv.medianBlur(src, pos)# 执行中值滤波
            cv.imshow("MedianBlur", dst)
        else:
            print("ksize must be odd, but current ksize is {0} ".format(pos), file=sys.stderr)

    cv.createTrackbar("ksize", "MedianBlur", 1, 101, ksize_onChange) # 创建滑杆，ksize最大值预设为101，初始值为1
    cv.waitKey()

if __name__ == '__main__':
    main()
