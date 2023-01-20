#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{
    // 读图
    Mat src = imread("aaa.jpg", IMREAD_COLOR);
    
    // 读取(317,455)的数据
    Vec3b p = src.at<Vec3b>(Point2i(317,455));
    //! 注意，at函数如果越界会闪退，(程序返回1)
    std::cout<<p<<std::endl;
    // todo 另一种方式读取(317,455)的数据，相当于读455行，317列的数据
    p = src.at<Vec3b>(455,317);
    
    std::cout<<p<<std::endl;
    // 读(317,455)的R通道数据
    uchar r = src.at<Vec3b>(455,317)[2];
    std::cout<<static_cast<int>(r)<<std::endl;
    
    return 0;

}
