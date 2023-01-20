#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    Mat src = imread("Robert_Delaunay,_1913,_Premier_Disque.jpg"), tmp, dst;
    

    // todo 使用filter2D进行Laplace滤波
    src.convertTo(tmp, CV_16SC3); // 因为涉及负数要转换类型
    Mat kernel = (Mat_<float>(3, 3, CV_32FC1) << 0, 1, 0,  
                                                 1, -4, 1, 
                                                 0, 1, 0);
    filter2D(tmp, tmp, tmp.depth(), kernel);
    tmp = std::move(cv::abs(tmp)); // 滤波后求绝对值
    tmp.convertTo(dst, CV_8UC3); // 输出前转换为CV_8UC3->dst
    imshow("Laplace(filter2D)", dst);
    
    // todo 使用Laplacian函数
    Laplacian(src, dst, src.depth(), 3); // 第4个变量为滤波核大小
    imshow("Laplacian", dst);



    waitKey();
    return 0;
}