#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{
    // 读图
    Mat src = imread("aaa.jpg", IMREAD_GRAYSCALE);
    
    // 读取(317,455)的数据
    uchar p = src.at<uchar>(Point2i(317,455));
    //! 注意，at函数如果越界会闪退，(程序返回1)
    std::cout<<static_cast<int>(p)<<std::endl;
    // todo 另一种方式读取(317,455)的数据，相当于读455行，317列的数据
    p = src.at<uchar>(455,317);
    
    std::cout<<static_cast<int>(p)<<std::endl;

    
    return 0;

}
