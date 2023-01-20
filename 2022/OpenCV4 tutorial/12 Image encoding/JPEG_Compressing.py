import cv2 as cv


def Jpegcompress(src, quality):
    """

    :param src: 输入的图像
    :param quality: JPEG编码中质量 可选0~100（越高损失数据越少），默认95
    :return: dest: 编码后的图像
    """
    (retval, buf) = cv.imencode(".jpg", src, (cv.IMWRITE_JPEG_QUALITY, quality)) # 将图像压缩编码到缓冲流区域
    dest = cv.imdecode(buf, -1) # 将压缩后的缓冲流内容解码为图片，进行后续的处理

    return dest



def main():

    src = cv.imread("aaa.jpg", cv.IMREAD_COLOR)
    cv.namedWindow("after compression") # 创建窗口

    # unsafe
    def onChange(pos):
        dst = Jpegcompress(src, pos)
        cv.imshow("after compression", dst)

    cv.createTrackbar("quality", "after compression", 100, 100, onChange) # 创建滑杆
    cv.waitKey()

if __name__ == '__main__':
    main()