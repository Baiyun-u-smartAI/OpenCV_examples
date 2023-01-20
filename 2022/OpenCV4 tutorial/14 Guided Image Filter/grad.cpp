#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    Mat src = imread("Robert_Delaunay,_1913,_Premier_Disque.jpg"), tmp, grad_x, grad_y, dst;
    
    // Sobel求dx和dy
    Sobel(src, tmp, src.depth(), 1, 0, 3); // tmp:dx
    imshow("dx", tmp);
    tmp.convertTo(grad_x, CV_32FC3); // 转化为double类型，cv::sqrt要求格式为float/double

    

    Sobel(src, tmp, src.depth(), 0, 1, 3); // tmp:dy
    imshow("dy", tmp);
    tmp.convertTo(grad_y, CV_32FC3);// 转化为double类型，cv::sqrt要求格式为float/double

    

    Mat tmp1, tmp2;
    multiply(grad_x, grad_x, tmp1);// tmp1：grad_x的平方
    multiply(grad_y, grad_y, tmp2);// tmp2：grad_y的平方
    cv::sqrt(tmp1 + tmp2, tmp); // 计算梯度值

    tmp.convertTo(dst, CV_8UC3);
    imshow("Grad", dst);

    waitKey();
    return 0;
}