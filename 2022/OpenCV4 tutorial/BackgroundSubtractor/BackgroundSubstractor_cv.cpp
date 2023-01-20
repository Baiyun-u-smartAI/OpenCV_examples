#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/bgsegm.hpp>

using namespace cv;



int main() {
    VideoCapture cap("LIVE Nevskiy avenue St. Petersburg Russia, Gostiny Dvor. Невский пр. Санкт-Петербург, Гостиный двор 2022-11-09 20_18-h1wly909BYw.mp4");

    auto fgbg = bgsegm::createBackgroundSubtractorMOG();
    Mat frame, fgMask;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        else resize(frame, frame, Size(), .6, .6);
        fgbg->apply(frame, fgMask);
        imshow("mask", fgMask);
        if (waitKey(30) == 27) break;
    }
    cap.release();

    return 0;
}