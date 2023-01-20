#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    Mat src = imread("merge_split.jpg"), dst, kernel;

    // todo 用filter2D做box filter
    // 直接赋值的方法定义线性滤波核kernel
    kernel = (Mat_<float>(3, 3, CV_32FC1)<<1,1,1,\
    1,1,1,\
    1,1,1);
    kernel /= cv::sum(kernel)[0];// 归一化

    filter2D(src, dst, src.depth(), kernel); // 线性滤波
    imshow("3x3 Box(filter2D)", dst);


    // 用Mat::ones生成线性滤波核kernel
    kernel = Mat::ones(20, 20, CV_32FC1);
    kernel /= cv::sum(kernel)[0];// 归一化

    filter2D(src, dst, src.depth(), kernel); // 线性滤波
    imshow("20x20 Box(filter2D)", dst);


    // todo 用boxFilter， Size(20, 20)是滤波核大小
    boxFilter(src, dst, src.depth(), Size(20, 20)); // 方框滤波
    imshow("20x20 Box(boxFilter)", dst);

    waitKey();
    return 0;
}