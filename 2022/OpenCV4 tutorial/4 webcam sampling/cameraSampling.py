# -*- coding: utf-8 -*-


import cv2

from datetime import datetime

def main():

    cap = cv2.VideoCapture("http://192.168.42.129:8080/video") # 打开默认的摄像头

    if cap is None or not cap.isOpened():
        print("Warning: open camera fail")
        return None

    while True:

        # 读取一帧图片
        ret, frame = cap.read()

        if frame is None:
            print("{0}:Failed to read current frame".format(datetime.now().strftime('%H:%M:%S.%f')))
            continue


        cv2.imshow("camera 0 ", frame)
        # 大约延时25ms后读取下一帧，按下ESC结束
        if (cv2.waitKey(25) == 27): break





if __name__ == '__main__':
    main()