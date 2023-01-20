#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
    Mat src = imread("merge_split.jpg"), dst;

    // todo 用blur函数模糊，注意Size宽和高必须是奇数
    blur(src, dst, Size(21, 21));
    imshow("21x21 blur", dst);

    // todo 用GaussianBlur函数模糊，注意Size宽和高必须是奇数
    GaussianBlur(src, dst, Size(21, 21), 3);
    imshow("21x21 GaussianBlur(sigma=3)", dst);
    GaussianBlur(src, dst, Size(21, 21), 8);
    imshow("21x21 GaussianBlur(sigma=8)", dst);

    waitKey();
    return 0;
}