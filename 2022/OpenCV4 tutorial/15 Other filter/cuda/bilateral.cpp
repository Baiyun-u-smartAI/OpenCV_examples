// opencv_cuda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
using namespace cv;
int main()
{

    Mat src_host = cv::imread("./radical-art-of-young-people-2000x940.jpg", IMREAD_GRAYSCALE);
    cv::cuda::GpuMat dst, src;
    cv::TickMeter m;
    m.start();
    src.upload(src_host); // 将内存数据上传到GPU Cache
    cv::cuda::bilateralFilter(src, dst, 60, 120, 100); // 进行双边滤波
    Mat dst_host, dst_host2;
    dst.download(dst_host);// 将GPU Cache数据下载到内存
    m.stop();
    std::cout << m.getTimeMilli() << std::endl;
    m.reset();
    m.start();
    cv::bilateralFilter(src_host, dst_host2, 60, 120, 100);
    m.stop();
    std::cout << m.getTimeMilli() << std::endl;




}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
