#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    
    struct Userdata
    {
        Mat img;
    } src{.img=imread("Robert_Delaunay,_1913,_Premier_Disque.jpg")}; // 每次滑杆都要运算的数据

    int ksize =1;
    namedWindow("MedianBlur"); // 创建窗口
    createTrackbar("ksize", "MedianBlur", &ksize, 101, [](int ksize, void* userdata)->void{
        const auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        if ( ksize%2==1 ) //! medianBlur算法要求ksize是奇数
        {
            medianBlur(ud.img, dst, ksize); // 执行中值滤波
            imshow("MedianBlur", dst);
        }
        else
        {
            std::cerr << "ksize must be odd, but current ksize is " << ksize << std::endl;
        }  
    }, &src); // 创建滑杆，ksize最大值预设为101

    waitKey();
	return 0;
}