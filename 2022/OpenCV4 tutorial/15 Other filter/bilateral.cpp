#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    
    struct Userdata
    {
        Mat img;
        int d;
        double sigmaColor;
        double sigmaSpace;
    } src{.img = imread("Robert_Delaunay,_1913,_Premier_Disque.jpg"),
          .d = 1,
          .sigmaColor = 2.,
          .sigmaSpace = .5}; // 每次滑杆都要运算的数据


    namedWindow("bilateral"); // 创建窗口
    createTrackbar("d", "bilateral", &src.d, 30, [](int d, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        ud.d = d+20; //! d从20开始到50
        bilateralFilter(ud.img, dst, ud.d, ud.sigmaColor, ud.sigmaSpace); // todo 双边滤波
        imshow("bilateral", dst);
    }, &src); // 创建滑杆，d最大值预设为30

    createTrackbar("sigmaColor(2x)", "bilateral", nullptr, 30, [](int s_C2, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        ud.sigmaColor = (s_C2+20)*2; //! sigmaColor从40开始到100
        bilateralFilter(ud.img, dst, ud.d, ud.sigmaColor, ud.sigmaSpace); // todo 双边滤波
        imshow("bilateral", dst);
    }, &src); // 创建滑杆，sigmaColor最大值预设为60
    setTrackbarPos("sigmaColor(2x)", "bilateral", 1);// 设置sigmaColor(2x)初始位置1

    createTrackbar("sigmaSpace(1/2)", "bilateral", nullptr, 30, [](int s_S_half, void* userdata)->void{
            auto &ud = *static_cast<Userdata*>(userdata);
            static Mat dst;
            ud.sigmaSpace = (s_S_half+20)/2.; //! sigmaSpace从10开始到25
            bilateralFilter(ud.img, dst, ud.d, ud.sigmaColor, ud.sigmaSpace);// todo 双边滤波
            imshow("bilateral", dst);
            // std::cout<< ud.d << "," << ud.sigmaColor << "," << ud.sigmaSpace << std::endl;
    }, &src); // 创建滑杆，sigmaSpace最大值预设为25
    setTrackbarPos("sigmaSpace(1/2)", "bilateral", 1);// 设置sigmaSpace(1/2)初始位置1


    waitKey();
	return 0;
}