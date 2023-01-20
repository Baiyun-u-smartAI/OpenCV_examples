#include <opencv2/gapi.hpp>
#include <opencv2/gapi/core.hpp>
#include <opencv2/opencv.hpp>
void normal()
{
    cv::Mat srcImage = cv::imread("./Nanda-Gurung,-BA-(Hons)-Fine-Art,-UCA-Canterbury_154-0618_P_6.webp");
    cv::Mat dstImage, grad_x, grad_y;


    double t1 = (double)cv::getTickCount();

    Sobel(srcImage, grad_x, CV_32F, 1, 0, 3); // dx

    Sobel(srcImage, grad_y, CV_32F, 0, 1, 3); // dy

    cv::Mat tmp, tmp1, tmp2;
    multiply(grad_x, grad_x, tmp1);// tmp1：grad_x的平方
    multiply(grad_y, grad_y, tmp2);// tmp2：grad_y的平方
    cv::sqrt(tmp1 + tmp2, tmp); // 计算梯度值

    tmp.convertTo(dstImage, CV_8U);

    double t2 = ((double)cv::getTickCount() - t1) / cv::getTickFrequency() * 1000;
    std::cout << "Run (default): " << t2 << " ms\n";

}

void gapi_test()
{
    cv::Mat srcImage = cv::imread("./Nanda-Gurung,-BA-(Hons)-Fine-Art,-UCA-Canterbury_154-0618_P_6.webp");
    cv::Mat dstImage;

    //G-API只追踪管线的操作以及如何连接的。G-API的数据对象（cv::GMat）是用以连接各种操作的。
    //cv::GMat in则是一个为空的GMat信号，用于告知计算的开始。
    //然后实例化cv::GComputation这个对象。此对象把输入/输出(input/output)数据当做参数（在本例中依次是in和out这两个cv::GMat对象），
    //并基于in和out的中的数据流来重建调用图。

    cv::GMat in, grad_x, grad_y;
    grad_x = cv::gapi::Sobel(in, CV_32F, 1, 0, 3);

    grad_y = cv::gapi::Sobel(in, CV_32F, 0, 1, 3);

    cv::GMat mag = cv::gapi::sqrt(cv::gapi::mul(grad_x, grad_x) + cv::gapi::mul(grad_y, grad_y));
    cv::GMat out = cv::gapi::convertTo(mag, CV_8U);

    cv::GComputation ac(in, out);

    double t1 = (double)cv::getTickCount();
    ac.apply(srcImage, dstImage);

    double t2 = ((double)cv::getTickCount() - t1) / cv::getTickFrequency() * 1000;
    std::cout << "Run(gapi): " << t2 << " ms\n";


}

int main()
{
    normal();
    gapi_test();
    return 0;
}