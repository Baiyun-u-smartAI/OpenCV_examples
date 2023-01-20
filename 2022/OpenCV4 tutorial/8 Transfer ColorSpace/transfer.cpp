#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{
    // 读图
    Mat src = imread("merge_split.jpg", IMREAD_COLOR);
    Mat hsv;
    cvtColor(src,hsv,COLOR_BGR2HSV);// 将图片转化为HSV通道
    hsv = hsv + Scalar(0, 0, 50);// 修改V通道的值
    cvtColor(hsv,hsv,COLOR_HSV2BGR);// 将图像转为BGR通道
    imshow("+V", hsv);// imshow输出的Mat数据必须为BGR数据，否则会异常

    Mat Lab;
    cvtColor(src,Lab,COLOR_BGR2Lab);// 将图片转化为Lab通道
    Lab = Lab - Scalar(0, 0, 50);// 修改b通道的值
    cvtColor(Lab,Lab,COLOR_Lab2BGR);// 将图像转为BGR通道
    imshow("-b", Lab);

    waitKey();
    return 0;
}