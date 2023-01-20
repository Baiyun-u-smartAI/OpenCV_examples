import cv2 as cv

def main():
    src = cv.imread("aaa.jpg")
    class Params:
        edgeThresh = 1
        edgeThreshScharr = 1

    gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
    # Create a window
    cv.namedWindow("Edge map : Canny default (Sobel gradient)", cv.WINDOW_AUTOSIZE)

    def edgeThresh_onChange(edgeTh):
        Params.edgeThresh = edgeTh
        blurImage = cv.blur(gray, [3, 3])
        # Run the edge detector on grayscale 得到的edge1是单通道图片
        edge1 = cv.Canny(blurImage, Params.edgeThresh, Params.edgeThresh * 3, 3)
        # cedge = np.zeros(src.shape, dtype=np.uint8)
        # edge1[:, :, None]就是给edge1拓展一个维度，便于运算； .astype(src.dtype)是保持数据的类型一致
        cedge = src * (edge1[:, :, None].astype(src.dtype))

        cv.imshow("Edge map : Canny default (Sobel gradient)", cedge)

    # create a toolbar
    cv.createTrackbar("Canny threshold default", "Edge map : Canny default (Sobel gradient)", Params.edgeThresh, 100,
                      edgeThresh_onChange)

    cv.namedWindow("Edge map : Canny with custom gradient (Scharr)", cv.WINDOW_AUTOSIZE)

    def edgeThScharr_onChange(edgeThScharr):
        Params.edgeThreshScharr = edgeThScharr
        blurImage = cv.blur(gray, [3, 3])
        dx = cv.Scharr(blurImage, -1, 1, 0)
        dy = cv.Scharr(blurImage, -1, 0, 1)
        edge2 = cv.Canny(blurImage, Params.edgeThreshScharr, Params.edgeThreshScharr * 3, 3)
        cedge = src * (edge2[:, :, None].astype(src.dtype))
        cv.imshow("Edge map : Canny with custom gradient (Scharr)", cedge)

    cv.createTrackbar("Canny threshold Scharr", "Edge map : Canny with custom gradient (Scharr)", Params.edgeThreshScharr, 400, edgeThScharr_onChange)

    cv.waitKey()


if __name__ == '__main__':
    main()
