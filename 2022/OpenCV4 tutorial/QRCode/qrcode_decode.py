import sys
import matplotlib.pyplot as plt
import cv2 as cv
import numpy as np


def main(inputImage):
    qrDecoder = cv.QRCodeDetector()

    # Detect and decode the qrcode
    (data, bbox, rectifiedImage) = qrDecoder.detectAndDecode(inputImage)
    if len(data) > 0:
        print("Decoded Data : {}".format(data))
        # display(inputImage, bbox)
        rectifiedImage = np.uint8(rectifiedImage)
        dst = np.zeros( ( np.array(rectifiedImage).shape[0], np.array(rectifiedImage).shape[1], 3))
        for i in range(0,3):
            dst[:, :, i] = rectifiedImage
        plt.imshow(dst.astype(np.uint8))
        plt.show()
    else:
        print("QR Code not detected")
        cv.imshow("Results", inputImage)
        cv.waitKey()
        cv.destroyAllWindows()



if __name__ == '__main__':
    if len(sys.argv) > 1:
        inputImage = cv.imread(sys.argv[1])
    else:
        inputImage = cv.imread("encode_data.jpg")
    main(inputImage)
