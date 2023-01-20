import cv2 as cv
import numpy as np


def just_test():
    # 显示一张100x100全黑的图，窗口标题为"the title"
    cv.imshow("the title", np.zeros((100, 100, 3), dtype=np.uint8))
    # 按任意键结束显示
    cv.waitKey()
    # 关闭窗口
    cv.destroyAllWindows()

if __name__ == '__main__':
    just_test()