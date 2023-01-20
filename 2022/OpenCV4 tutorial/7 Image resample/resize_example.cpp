#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{
    Mat src = imread("merge_split.jpg"), dst;
    /* resize 常用模式
            INTER_NEAREST 近邻插值
            INTER_LINEAR 线性插值
            INTER_CUBIC 三次插值
            INTER_AREA 
            INTER_LANCZOS4 三角插值
            INTER_LINEAR_EXACT
            INTER_NEAREST_EXACT
    */
    // 第三个参数为Size()的时候，后面跟的两个浮点数代表图片的宽放缩倍数、高放缩倍数
    resize(src, dst, Size(), 3., 2., INTER_NEAREST);
    imshow("INTER_NEAREST", dst);
    resize(src, dst, Size(), 3., 2., INTER_LINEAR);
    imshow("default", dst);
    waitKey();
    // 输出改变尺寸后的图片(Mat变量)
    imwrite("new_size.png", dst);
}
