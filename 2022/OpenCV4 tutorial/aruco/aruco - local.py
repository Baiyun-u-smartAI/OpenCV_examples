import cv2 as cv
from matplotlib import pyplot as plt

# event listener
def press(event):
    global isLoop
    if event.key == 'q': # 如果按下q就退出
        print('exit...')
        isLoop = False
    fig.canvas.draw()

# fig, ax = plt.subplots()
# fig.canvas.mpl_connect('key_press_event', press)
# imgplot = ax.imshow(frame)

if __name__ == "__main__":

    fig, ax = plt.subplots()
    fig.canvas.mpl_connect('key_press_event', press) # matplotlib获取键盘输入

    img = cv.imread("./aruco.jpg")
    arucoDict = cv.aruco.Dictionary_get(cv.aruco.DICT_5X5_50) # 当前是做ArUco的5x5模板检测
    arucoParams = cv.aruco.DetectorParameters_create() # 创建参数arucoParams
    (corners, ids, rejected) = cv.aruco.detectMarkers(img,
                                                      arucoDict, parameters=arucoParams)
    # verify *at least* one ArUco marker was detected
    if len(corners) > 0:
        # flatten the ArUco IDs list
        # frame2 = frame.copy()
        # cv.aruco.drawDetectedMarkers(frame2, corners, ids, (255, 0, 0))
        ids = ids.flatten()
        # loop over the detected ArUCo corners
        for (markerCorner, markerID) in zip(corners, ids):
            # extract the marker corners (which are always returned
            # in top-left, top-right, bottom-right, and bottom-left
            # order)
            corners = markerCorner.reshape((4, 2))
            (topLeft, topRight, bottomRight, bottomLeft) = corners
            # convert each of the (x, y)-coordinate pairs to integers
            topRight = (int(topRight[0]), int(topRight[1]))
            bottomRight = (int(bottomRight[0]), int(bottomRight[1]))
            bottomLeft = (int(bottomLeft[0]), int(bottomLeft[1]))
            topLeft = (int(topLeft[0]), int(topLeft[1]))
            # draw the bounding box of the ArUCo detection
            cv.line(img, topLeft, topRight, (0, 255, 0), 5)
            cv.line(img, topRight, bottomRight, (0, 255, 0), 5)
            cv.line(img, bottomRight, bottomLeft, (0, 255, 0), 5)
            cv.line(img, bottomLeft, topLeft, (0, 255, 0), 5)
            # compute and draw the center (x, y)-coordinates of the
            # ArUco marker
            cX = int((topLeft[0] + bottomRight[0]) / 2.0)
            cY = int((topLeft[1] + bottomRight[1]) / 2.0)
            cv.circle(img, (cX, cY), 4, (0, 0, 255), -1)
            # draw the ArUco marker ID on the frame
            cv.putText(img, str(markerID),
                       (topLeft[0], topLeft[1] - 15),
                       cv.FONT_HERSHEY_SIMPLEX,
                       2, (255, 0, 0), 5)
            print(f'get id:{str(markerID)}')

        img = cv.cvtColor(img, cv.COLOR_BGR2RGB)
        ax.imshow(img)

        plt.show()  # 显示图片




    # plt.ioff()  # 关闭动态绘图
    plt.show()  # 显示图片