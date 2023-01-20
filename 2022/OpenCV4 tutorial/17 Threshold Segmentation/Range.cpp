#include <opencv2/opencv.hpp>

using namespace cv;

struct Userdata{
    Mat src;
    Scalar lowerb, upperb;
};
enum onChangedMode{
    b_low, b_up, g_low, g_up, r_low, r_up, action
};

template <onChangedMode N>
class Fuctor{
public:
    // 回调函数执行的公共部分
    static void onChanged( void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        static Mat tmp;
        Mat dst;
        inRange(ud.src, ud.lowerb, ud.upperb, tmp);


        bitwise_and(ud.src, ud.src, dst, tmp);// 与原图做mask运算，掩膜为tmp
        imshow("1", dst);
    }

};

template <>
class Fuctor<onChangedMode::b_low>{
public:
    // 拖动b_low执行的回调函数
    static void onChanged( int pos, void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        ud.lowerb.val[0] = pos; // 改变lowerb里面的第1个分量值
        Fuctor<onChangedMode::action>::onChanged(userdata);
    }
};

template <>
class Fuctor<onChangedMode::g_low>{
public:
    // 拖动g_low执行的回调函数
    static void onChanged( int pos, void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        ud.lowerb.val[1] = pos; // 改变lowerb里面的第2个分量值
        Fuctor<onChangedMode::action>::onChanged(userdata);
    }
};

template <>
class Fuctor<onChangedMode::r_low>{
public:
    // 拖动r_low执行的回调函数
    static void onChanged( int pos, void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        ud.lowerb.val[2] = pos; // 改变lowerb里面的第3个分量值
        Fuctor<onChangedMode::action>::onChanged(userdata);
    }
};

template <>
class Fuctor<onChangedMode::b_up>{
public:
    static void onChanged( int pos, void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        ud.upperb.val[0] = pos;
        Fuctor<onChangedMode::action>::onChanged(userdata);
    }
};

template <>
class Fuctor<onChangedMode::g_up>{
public:
    static void onChanged( int pos, void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        ud.upperb.val[1] = pos;
        Fuctor<onChangedMode::action>::onChanged(userdata);
    }
};

template <>
class Fuctor<onChangedMode::r_up>{
public:
    static void onChanged( int pos, void* userdata) {
        static Userdata& ud = *(Userdata *) userdata;
        ud.upperb.val[2] = pos;
        Fuctor<onChangedMode::action>::onChanged(userdata);
    }
};

int main()
{
    Mat in = imread("./merge_split.jpg");
    Userdata ud{.src = in, .lowerb = Scalar(0, 0, 0), .upperb = Scalar (255, 255, 255)};

    namedWindow("1");

    createTrackbar("b_low", "1", nullptr, 255, Fuctor<onChangedMode::b_low>::onChanged, &ud);

    createTrackbar("g_low", "1", nullptr, 255, Fuctor<onChangedMode::g_low>::onChanged, &ud);

    createTrackbar("r_low", "1", nullptr, 255, Fuctor<onChangedMode::r_low>::onChanged, &ud);

    createTrackbar("b_up", "1", nullptr, 255, Fuctor<onChangedMode::b_up>::onChanged, &ud);

    createTrackbar("g_up", "1", nullptr, 255, Fuctor<onChangedMode::g_up>::onChanged, &ud);

    createTrackbar("r_up", "1", nullptr, 255, Fuctor<onChangedMode::r_up>::onChanged, &ud);

    setTrackbarPos("b_low", "1", 0);
    setTrackbarPos("g_low", "1", 0);
    setTrackbarPos("r_low", "1", 0);

    setTrackbarPos("b_up", "1", 255);
    setTrackbarPos("g_up", "1", 255);
    setTrackbarPos("r_up", "1", 255);

    waitKey();
    return 0;
}