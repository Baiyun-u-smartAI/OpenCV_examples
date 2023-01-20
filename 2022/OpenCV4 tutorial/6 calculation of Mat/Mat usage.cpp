#include <opencv2/opencv.hpp>

using namespace cv;
int main(void)
{

    // 初始化方式1：直接用Mat_ 数据为{{1,2},{3,4}}
    Mat m1 = (Mat_<uchar>(2, 2, CV_8UC3) << 1, 2, 3, 4); 
    std::cout<< m1 << std::endl;


    // 初始化方式2 利用vector
    Mat m2;
    std::vector<uchar> v{1, 2, 3, 4, 5, 6,
                         7, 8, 9, 10, 11, 12};
    {
        Mat_<uchar> m_2(v);// 单通道数据
        m2 = m_2;
    }
    
    Mat m3 = m2.reshape(3, 2).clone();// reshape 改变通道的函数，传参为(通道数，行数)。这里会让数据变成两行，然后数据通道数为3。执行reshape函数后会返回Mat& 
    std::cout << m2 << std::endl; // 输出 [1, 2, 3, 4, 5, 6;
    //                     7, 8, 9, 10, 11, 12] 其中每三个值作为1组数据为一个点的值
    
    std::cout << m2.channels() << std::endl;
    std::cout << m3 << std::endl;
    std::cout << m3.channels() << std::endl;

    // Mat数据的拷贝：默认=拷贝，和构造拷贝都是软拷贝，虽然地址不同但是数据是关联的。
    Mat _m1 = m1;// 软拷贝, Mat _m1(m1); 也是一样的
    _m1 -= m1; // 改变_m4数据
    std::cout << m1 << std::endl; // 导致m1也发生了改变
    
    // todo 解决拷贝带来的关联问题
    //? 1. 将数据搬走 std::move
    Mat _m2(std::move(m1)); // Mat _m2(std::move(m1));和Mat _m2 = std::move(m1);相同
    std::cout << "after move operation: " << m1 << std::endl;
    //? 2. 将数据深度拷贝 被拷贝的变量.clone()
    m1 = (Mat_<uchar>(2,2,CV_8UC3) << 1, 2, 3, 4); 
    Mat _m3 = m1.clone();// 深度拷贝
    _m3 -= m1; // 改变_m3数据
    std::cout << "after clone operation: " << m1 << std::endl; 

    // 对图像的数据(uchar)运算
    m3.at<Vec3b>(0, 0)[0] ++;
    m3.at<Vec3b>(1, 1)[2] *=4;
    m3.at<Vec3b>(1, 0) -= Vec3b(7, 8, 9); 
    std::cout <<"single-point res: "<< m3 << std::endl;

    // 整体运算，只支持+-*/，对于uchar类型的Mat变量，运算得到负数->0，得到超出255->255
    m3 += Scalar(666, -1, -666);// 多通道Mat的+-运算
    std::cout <<"global +-calc res: "<< m3 << std::endl;
    m3 /=2;
    std::cout <<"global */calc res: "<< m3 << std::endl;
    m2 += 50;
    std::cout <<"ch1 calc res: "<< m2.reshape(1, std::vector<int>{4,3} ) << std::endl;

    // 相同大小的Mat变量可以做+-运算
    Mat m4 = (Mat_<float>(2, 2, CV_32FC3) << 1, 3, 3, 1); 
    Mat m5 = (Mat_<float>(2, 2, CV_32FC3) << 2, 0, 2, 0);
    std::cout << "m4+m5 = " << m4+m5 << std::endl;
    std::cout << "m4-m5 = " << m4-m5 << std::endl;

    
    // Mat 类型转换
    m3.convertTo(m3, CV_32FC3);// 32F 就是float类型
    m3 += Scalar(666, -1.5, -666);
    std::cout <<"global +-calc res(after covertion): "<< m3 << std::endl;
    return 0;
}
