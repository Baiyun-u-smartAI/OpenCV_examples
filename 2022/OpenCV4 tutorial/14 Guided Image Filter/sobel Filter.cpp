#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    Mat src = imread("Robert_Delaunay,_1913,_Premier_Disque.jpg"), tmp, dst;
    

    // todo 使用filter2D进行导向滤波
    src.convertTo(tmp, CV_16SC3); // 因为涉及负数要转换类型
    Mat kernel = (Mat_<float>(3, 3, CV_32FC1) << -1, 0, 1,  
                                                 -2, 0, 2, 
                                                 -1, 0, 1);
    filter2D(tmp, tmp, tmp.depth(), kernel);
    tmp = std::move(cv::abs(tmp)); // 滤波后求绝对值
    tmp.convertTo(dst, CV_8UC3); // 输出前转换为CV_8UC3->dst
    imshow("dx(filter2D)", dst);
    
    // todo 使用Sobel进行导向滤波
    Sobel(src, dst, src.depth(), 1, 0, 3); // 第4~5个变量分别为int dx, int dy；dx和dy为求导次数，第6为滤波核大小
    imshow("dx(Sobel)", dst);

    Sobel(src, dst, src.depth(), 0, 1, 3); // 第4~5个变量分别为int dx, int dy；dx和dy为求导次数，第6为滤波核大小
    imshow("dy(Sobel)", dst);




    waitKey();
    return 0;
}