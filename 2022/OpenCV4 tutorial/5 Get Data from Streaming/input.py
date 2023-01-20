import cv2 as cv


def main():

    cap = cv.VideoCapture() #创建捕获对象

    # todo 读取UDP流
    cap.open("udp://127.0.0.1:34869", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: continue #防止数据头部的错误导致闪退
        cv.imshow("Beautiful blue 3d ball abstract background",frame)
        if (cv.waitKey(30) == 27) : break

    # todo 读取RTSP流
    cap.open("rtsp://192.168.3.4:8554/live/test", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: continue #防止数据头部的错误导致闪退
        cv.imshow("Beautiful blue 3d ball abstract background",frame)
        if (cv.waitKey(30) == 27) : break

    # todo 读取RTMP流
    cap.open("rtmp://192.168.3.4:1935/live/test", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: continue #防止数据头部的错误导致闪退
        cv.imshow("Beautiful blue 3d ball abstract background",frame)
        if (cv.waitKey(30) == 27) : break

    # todo 读取带用户名密码的流
    cap.open("rtmp://admin:a12345678@192.168.3.4:1935/live/test", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: continue #防止数据头部的错误导致闪退
        cv.imshow("Beautiful blue 3d ball abstract background",frame)
        if (cv.waitKey(30) == 27) : break

    # todo 读取HTTP链接视频
    cap.open("http://files.alex4ai.top/Lines%20Digital%20Abstract%20Background.mp4", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: break #视频结束后退出
        cv.imshow("Lines Digital Abstract Background", frame)
        if (cv.waitKey(30) == 27): break

    # todo 读取好看视频
    cap.open("https://vd2.bdstatic.com/mda-iidnk37i7rk8k4pi/sc/mda-ii"
             "dnk37i7rk8k4pi.mp4?v_from_s=hkapp-haokan-hna&auth_key=1"
             "659434840-0-0-1cae7af9f44f05fc3f4af78899f5c3ea&bcevod_c"
             "hannel=searchbox_feed&cd=0&pd=1&pt=3&logid=2240700530&v"
             "id=13434561325221408696&abtest=103525_2-103890_1&klogid"
             "=2240700530", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: break #视频结束后退出
        cv.imshow("GPU", frame)
        if (cv.waitKey(30) == 27): break

    # todo 读取本地视频
    cap.open("Lines Digital Abstract Background.mp4", cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False: break #视频结束后退出
        cv.imshow("Lines Digital Abstract Background", frame)
        if (cv.waitKey(30) == 27): break

    # todo 读取GIF图片
    GifPath = "13f94b50bd090b8f88811959cdb96cfb.gif"
    cap.open(GifPath, cv.CAP_FFMPEG)
    while True:
        (retval, frame) = cap.read()
        if retval is False:
            cap.release()
            cap.open(GifPath, cv.CAP_FFMPEG)
        else:
            cv.imshow("abstract GIF", frame)
        if (cv.waitKey(1) == 27) : break

    # todo 读取网络图片(不支持png，bmp)
    cap.open("https://img.aidotu.com/down/jpg/20200828/ac3e413a0d9425105f0e4097de68c5f4_114134_640_650.jpg", cv.CAP_FFMPEG)

    (retval, frame) = cap.read()
    if retval is False:
        cap.release()
    else:
        cv.imshow("smile", frame)
        cv.waitKey()


if __name__ == '__main__':
    main()