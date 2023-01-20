#include <opencv2/opencv.hpp>

using namespace cv;
struct Userdata{
    Mat img, dst; // 滑杆内部处理的图片
    int ksize, sigmaX; // 滑杆的参数
};

enum Mode{
    ksize, sigmaX, action
};

template <Mode N>
class GaussBlur{
public:
    static void onChanged(int pos_ksize, int pos_sigmaX, void* userdata)
    {
        static Userdata& ud = *(Userdata*)userdata;
        if (pos_ksize % 2)
            ud.ksize = pos_ksize;
        ud.sigmaX = pos_sigmaX;
        GaussianBlur(ud.img, ud.dst, Size(ud.ksize, ud.ksize), ud.sigmaX);
        imshow("img", ud.dst);
    }
};

template <>
class GaussBlur<::ksize>{

public:
    static void onChanged(int pos, void* userdata)
    {
        static Userdata& ud = *(Userdata*)userdata;
        GaussBlur<::action>::onChanged(pos, ud.sigmaX, userdata);
    }
};
template <>
class GaussBlur<::sigmaX>{

public:
    static void onChanged(int pos, void* userdata)
    {
        static Userdata& ud = *(Userdata*)userdata;
        GaussBlur<::action>::onChanged(ud.ksize, pos, userdata);
    }
};
int main() {
    Mat img = imread("./aaa.jpg"), dst;
    int ks;

//    Userdata ud{.img = img, .dst = dst};
    Userdata ud;
    ud.img = img;
    ud.dst = dst;
    ud.sigmaX = 1;
    namedWindow("img");
    createTrackbar("size", "img", nullptr, 20,
                   GaussBlur<::ksize>::onChanged,
    (void*)&ud );
    createTrackbar("sigmaX", "img", nullptr, 20,
                   GaussBlur<::sigmaX>::onChanged,
    (void *) &ud);
    setTrackbarPos("size", "img", 1);

    waitKey();
    return 0;
}
