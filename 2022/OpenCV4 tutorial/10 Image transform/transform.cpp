#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{
    Mat src = imread("merge_split.jpg"), dst;
    // todo 变换前的在src四个点
    std::vector<Point2f> before{Point2f(18, 221),Point2f(270, 0),Point2f(428, 98),Point2f(176, 336)};

    // todo 需要变换到dst图上的对应四个点位置
    std::vector<Point2f> after(3);// 初始化vector的大小为3
    after[0] = Point2f(0, 0);// 赋值方式1： 与数组类似（不太安全）
    after.at(1) = Point2f(300, 0);// 赋值方式2： 用at函数，越界会报错
    *(after.begin()+2) = Point2f(300, 200);// 赋值方式3： 用迭代器（既不安全，又不方便）
    after.emplace_back(Point2f(0, 200));// 第四个点已经超出vector的大小，使用emplace_back或push_back在最后增加一个元素，以增加容器的大小，增加后[3]为Point2f(0, 200)

    /* 
       //? 如何用for循环输出vector里面的内容
       // 方式1：类似于数组
       for (int i = 0; i < after.size(); i++)
       {
           std::cout<< after[i]<<std::endl;
       }
       // 方式2：for-auto :
       for (auto i : after)
       {
           std::cout<< i<<std::endl;
       }
       // 方式3：用迭代器
       for (auto i = after.begin(); i != after.end(); i++)
       {
           std::cout<<*i<<std::endl;
       } 
    */

    Mat transMat = getPerspectiveTransform(before, after);// todo 求解变换矩阵
    warpPerspective(src, dst, transMat, Size(300, 200));// todo 应用变换得到图片300x200大小

    imshow("after wrapping", dst);
    waitKey();

}
