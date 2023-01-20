#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{
    // 读图
    Mat src = imread("merge_split.jpg", IMREAD_COLOR);
    // 定义存放三个通道的变量
    std::vector<Mat> bgr1(3);
    std::array<Mat,3> bgr2;
    Mat bgr3[3];

    split(src, bgr1); // 分离通道
    std::swap(bgr1[0], bgr1[1]);// 交换 B 和 G 通道
    Mat dst1;
    merge(bgr1, dst1);// 合并通道
    imshow("split1", dst1);

    split(src, bgr2);
    bgr2[0] = std::move(bgr2[2]);// R 通道覆盖 B 通道
    bgr2[2] = Mat::zeros(bgr2[0].size(), bgr2[0].type());// 清空 R 通道
    //? 1. 为什么需要赋值空矩阵 2. std::move可以删除吗？ 3. 改成bgr2[2] -= 255; 为什么会报错？
    Mat dst2;
    merge(std::begin(bgr2), 3, dst2);// 合并通道
    imshow("split2", dst2);

    split(src, bgr3);
    bgr3[2] = bgr3[0].clone(); // G 通道覆盖 R 通道, OpenCV =执行的是软拷贝
    bgr3[0] -= 255;// 清空 G 通道
    Mat dst3;
    merge(bgr3, 3, dst3);// 合并通道，不需要std::begin因为，数组名就是数据块的开头
    imshow("split3", dst3);

    waitKey();
    return 0;
}
