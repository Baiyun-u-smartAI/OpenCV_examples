#include <opencv2/opencv.hpp>

using namespace cv;

/**
 * @brief Jpegcompress是JPEG编码函数
 * 
 * @param src 输入的Mat变量
 * @param dest 编码后的Mat变量
 * @param quality JPEG编码中质量 可选0~100（越高损失数据越少），默认95
 */
void Jpegcompress(const cv::Mat& src, cv::Mat& dest, int quality)
{
    std::vector<uchar> buff; // 缓存图像数据区域

    std::vector<int> params; // params存放JPEG编码参数  
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(quality);

    //将图像压缩编码到缓冲流区域
    cv::imencode(".jpg", src, buff, params);

    //将压缩后的缓冲流内容解码为Mat，进行后续的处理
    dest = cv::imdecode(buff, -1);
}



int main(void)
{
    struct Userdata
    {
        Mat img;
    } src{.img=imread("aaa.jpg")}; // 每次滑杆都要运算的数据

    //创建窗口
    namedWindow("after compression");

    int quality = 100;

 
    createTrackbar("quality","after compression",&quality,100,[](int quality, void* userdata)->void{
        const auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        Jpegcompress(ud.img, dst, quality);
        imshow("after compression", dst);
        
    }, &src);//创建滑杆

    waitKey();

}
