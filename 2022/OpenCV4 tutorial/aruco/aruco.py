import cv2 as cv
from matplotlib import pyplot as plt
i = 0
isLoop = True
# event listener
def press(event):
    global  isLoop
    if event.key == 'q':
        print('exit...')
        isLoop = False
    fig.canvas.draw()

# fig, ax = plt.subplots()
# fig.canvas.mpl_connect('key_press_event', press)
# imgplot = ax.imshow(frame)

if __name__ == "__main__":
    cap = cv.VideoCapture("http://192.168.3.141:8080/video")
    fig, ax = plt.subplots()
    fig.canvas.mpl_connect('key_press_event', press)
    plt.ion()  # 开启动态绘图
    while isLoop:
        ret, frame = cap.read()
        arucoDict = cv.aruco.Dictionary_get(cv.aruco.DICT_4X4_50)
        arucoParams = cv.aruco.DetectorParameters_create()
        (corners, ids, rejected) = cv.aruco.detectMarkers(frame,
                                                           arucoDict, parameters=arucoParams)
        # verify *at least* one ArUco marker was detected
        if len(corners) > 0:
            # flatten the ArUco IDs list
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
                cv.line(frame, topLeft, topRight, (0, 255, 0), 5)
                cv.line(frame, topRight, bottomRight, (0, 255, 0), 5)
                cv.line(frame, bottomRight, bottomLeft, (0, 255, 0), 5)
                cv.line(frame, bottomLeft, topLeft, (0, 255, 0), 5)
                # compute and draw the center (x, y)-coordinates of the
                # ArUco marker
                cX = int((topLeft[0] + bottomRight[0]) / 2.0)
                cY = int((topLeft[1] + bottomRight[1]) / 2.0)
                cv.circle(frame, (cX, cY), 4, (0, 0, 255), -1)
                # draw the ArUco marker ID on the frame
                cv.putText(frame, str(markerID),
                            (topLeft[0], topLeft[1] - 15),
                            cv.FONT_HERSHEY_SIMPLEX,
                            2, (255, 0, 0), 5)
                # print(f'get id:{str(markerID)}')
            # show the output frame

            # cv.imshow("-----", frame)
            # if cv.waitKey(30) == 27:
            #     break
            ax.cla()
            # frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB) #frame[:, :, [2, 1, 0]]
            ax.imshow(frame)
            plt.pause(1/80)
            plt.show()  # 显示图片



    # plt.ioff()  # 关闭动态绘图
    plt.show()  # 显示图片