#include <opencv2/opencv.hpp>
using namespace cv;


int main(int argc, char* argv[])
{
    Mat image = imread("binary-icon-30.bmp", IMREAD_GRAYSCALE);
    Mat labels, stats, centroids;
    // 连通域计算函数，要求输入的图片为二值图，第五个变量默认为8（八连通域）
    connectedComponentsWithStats(image, labels, stats, centroids);


    // todo 画矩形框
    Mat dst;
    Mat _labels, bg;
    labels.convertTo(_labels, CV_8UC1);
    bg =  _labels*255;
    cvtColor(bg, bg, COLOR_GRAY2BGR);
    
    applyColorMap(_labels*15, dst, COLORMAP_HSV);
    bitwise_and(dst, bg, dst);

#define GET_STATS(x) std::get<x>(para) = stats.at<int>(Point(x, i))
    
    
    for (int i = 1; i < stats.rows; i++)
    {
        static int x, y, w, h;
        auto para = std::make_tuple(std::ref(x), std::ref(y), std::ref(w), std::ref(h));
        GET_STATS(0);
        GET_STATS(1);
        GET_STATS(2);
        GET_STATS(3);
        Rect rect(x, y, w, h);
        rectangle(dst, rect, Scalar(255, 255, 255), 2);// 线宽2
    }
#undef GET_STATS  
    

    imshow("stats connectedComponents", dst);
    waitKey();
}