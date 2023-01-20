import cv2 as cv

def main():
    src = cv.imread("Robert_Delaunay,_1913,_Premier_Disque.jpg")
    cv.namedWindow("bilateral")  # 创建窗口
    para4Bi = {'d': 1, 'sigmaColor': 2, 'sigmaSpace': 0.5}

    def d_onChange(pos):
        para4Bi['d'] = pos+20# fixme d从20开始到50
        dst = cv.bilateralFilter(src, para4Bi['d'], para4Bi['sigmaColor'], para4Bi['sigmaSpace'])# todo 双边滤波
        cv.imshow("bilateral", dst)

    def sigmaColor_2x_onChange(pos):
        para4Bi['sigmaColor'] = (pos+20) * 2# fixme  sigmaColor从40开始到100
        dst = cv.bilateralFilter(src, para4Bi['d'], para4Bi['sigmaColor'], para4Bi['sigmaSpace'])# todo 双边滤波
        cv.imshow("bilateral", dst)

    def sigmaSpace_half_onChange(pos):
        para4Bi['sigmaSpace'] = (pos+20) / 2.# fixme  sigmaColor从40开始到100
        dst = cv.bilateralFilter(src, para4Bi['d'], para4Bi['sigmaColor'], para4Bi['sigmaSpace'])# todo 双边滤波
        cv.imshow("bilateral", dst)

    cv.createTrackbar("d", "bilateral", 1, 30, d_onChange)# 创建滑杆，d最大值预设为30，初始值为1
    cv.createTrackbar("sigmaColor(2x)", "bilateral", 1, 30, sigmaColor_2x_onChange)# 创建滑杆，sigmaColor(2x)最大值预设为30，初始值为1
    cv.createTrackbar("sigmaSpace(1/2)", "bilateral", 1, 30, sigmaSpace_half_onChange)# 创建滑杆，sigmaSpace(1/2)最大值预设为30，初始值为1
    cv.waitKey()

if __name__ == '__main__':
    main()
