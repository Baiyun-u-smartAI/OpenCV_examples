import cv2 as cv

def main():
    src = cv.imread("binary-icon-30.bmp", cv.IMREAD_GRAYSCALE)
    class Params:
        morph_elem = 0
        morph_size = 0
        morph_operator = 0
    def Operator_onChange(Operator):
        Params.morph_operator = Operator

        element = cv.getStructuringElement(Params.morph_elem, [2 * Params.morph_size + 1, 2 * Params.morph_size + 1], [Params.morph_size, Params.morph_size])
        dst = cv.morphologyEx(src, Params.morph_operator, element)
        cv.imshow("Morphology Transformations Demo", dst)

    cv.namedWindow("Morphology Transformations Demo") # Create window
    cv.createTrackbar("Operator", "Morphology Transformations Demo", Params.morph_operator, 7, Operator_onChange)

    def Element_onChange(elem_T):

        Params.morph_elem = elem_T
        element = cv.getStructuringElement(Params.morph_elem, [2 * Params.morph_size + 1, 2 * Params.morph_size + 1], [Params.morph_size, Params.morph_size])
        dst = cv.morphologyEx(src, Params.morph_operator, element)
        cv.imshow("Morphology Transformations Demo", dst)

    cv.createTrackbar("Element", "Morphology Transformations Demo", Params.morph_elem, 2, Element_onChange)

    def ksize_onChange(morph_s):

        Params.morph_size = morph_s
        element = cv.getStructuringElement(Params.morph_elem, [2 * Params.morph_size + 1, 2 * Params.morph_size + 1], [Params.morph_size, Params.morph_size])
        dst = cv.morphologyEx(src, Params.morph_operator, element)
        cv.imshow("Morphology Transformations Demo", dst)

    cv.createTrackbar("Kernel size:(2n+1)", "Morphology Transformations Demo", Params.morph_size, 21, ksize_onChange)

    cv.waitKey()


if __name__ == '__main__':
    main()
