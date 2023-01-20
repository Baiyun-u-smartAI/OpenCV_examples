import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

if __name__ == "__main__":
    # calib参数flag
    flag = cv.CALIB_FIX_PRINCIPAL_POINT | cv.CALIB_ZERO_TANGENT_DIST | cv.CALIB_FIX_ASPECT_RATIO # 标识符为固定光轴中心，一般不变焦就是固定；有切向畸变；焦距fx/fy比例固定
    view = cv.imread("IMG_20221028_210438_BURST011.jpg")
    imageHeight, imageWidth, _ = view.shape
    # 是否需要水平翻转图片
    if False:
        view = cv.flip(view, 0)

    """
        @patternSize: 是要获取的棋盘点的多少，这里是9x6个棋盘点
        @CornerPoints 找到9x6角点在图像中的坐标
    """
    ret, _CornerPoints = cv.findChessboardCorners(view, [9, 6])
    # print(imageHeight, imageWidth, CornerPoints)
    if not ret:
        raise Exception("find ChessBoard Pattern failed")
    viewGray = cv.cvtColor(view, cv.COLOR_BGR2GRAY)
    CornerPoints = cv.cornerSubPix(viewGray, _CornerPoints, [11, 11], [-1, -1], (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_COUNT, 30, 0.001)) # 在角点检测中精确化角点位置，CornerPoints是输入角点的初始坐标以及精准化后的坐标用于输出。
    org = view.copy() # 因为下面的函数会丢失原始图像数据，所以要备份
    view = cv.drawChessboardCorners(view, [9, 6], CornerPoints, ret) # 在view上绘制棋盘角点
    showView = cv.resize(view, None, fx=.6, fy=.6)
    showView = cv.cvtColor(showView, cv.COLOR_BGR2RGB)
    fig, ax = plt.subplots(1, 2) # 横向双视图
    ax[0].set_title('Chessboard Corners') # 第一个视图标题
    ax[0].imshow(showView) # 显示棋盘标定角点图

    squareSize = 5 # 每个棋盘各自边长squareSize

    # objectPoints和imagePoints里的数据结构是 [图1的世界坐标点集合, 图2的世界坐标点集合,...] [图1的对应图像坐标点集合, 图2的对应图像坐标点集合,...]
    objectPoints = []
    imagePoints = []
    imagePoints.append(CornerPoints)

    # objectPoints[0]制作对应的9*6的三维角点坐标集合，{[1 i 0]~[8 i 0]  i: 0~5} * squareSize
    objp = np.zeros((9 * 6, 3), np.float32)
    objp[:, :2] = np.mgrid[0:9, 0:6].T.reshape(-1, 2)
    objectPoints.append(objp*squareSize)



    newObjPoints = objectPoints[0]

    rms, cameraMatrix, distCoeffs, rvecs, tvecs, _ = cv.calibrateCameraRO(np.array(objectPoints), np.array(imagePoints), [imageWidth, imageHeight], -1, None, None, flags=flag | cv.CALIB_USE_LU,newObjPoints=newObjPoints)
    print(f'Re-projection error reported by calibrateCamera: {rms:.2f}')
    print(f'{cameraMatrix = }') # 摄像头内参
    print(f'{distCoeffs = }') # 摄像头畸变矩阵
    print(f'{rvecs = }') # 外参旋转向量

    rotationMatrix, _ = cv.Rodrigues(np.array(rvecs)) # 求解外参旋转矩阵
    print(f'{rotationMatrix = }')
    print(f'{tvecs = }') # 外参平移向量
    undistortView = cv.undistort(org, cameraMatrix, distCoeffs) # 矫正图像
    undistortView = cv.resize(undistortView, None, fx=.6, fy=.6)
    undistortView = cv.cvtColor(undistortView, cv.COLOR_BGR2RGB)
    ax[1].set_title('undistort')
    ax[1].imshow(undistortView) # 显示矫正后图像
    plt.show()
