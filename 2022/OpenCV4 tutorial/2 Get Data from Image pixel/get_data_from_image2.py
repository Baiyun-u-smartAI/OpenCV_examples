import cv2 as cv

def main():
    src = cv.imread("aaa.jpg",cv.IMREAD_GRAYSCALE)
    print(src[455][317])# 读取(317,455)的数据,相当于读455行，317列的数据
if __name__ == '__main__':
    main()