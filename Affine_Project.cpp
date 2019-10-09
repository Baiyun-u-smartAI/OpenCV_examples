//
// Created by Andersson on 2019/10/8.
//
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>
using namespace cv;

int run768(){
    // PerspectiveTransform求解需要原始图像的四个点和变换后的四个点
    Mat img=imread("Newspaper.jpeg");
    // 建立两个放四个点的容器
    std::vector<Point2f> origin{Point2f(197,13),Point2f(599,124),Point2f(36,262),Point2f(481,441)};
    std::vector<Point2f> destination(4);
    destination[0]= Point2f(0, 0);
    destination[1]= Point2f(img.cols-1, 0);
    destination[2]= Point2f(0, img.rows-1);
    destination[3]= Point2f(img.cols-1, img.rows-1);
    // 求解单应性矩阵
    Mat transform = getPerspectiveTransform(origin,destination);
    // 新建用于输出图像的矩阵img_trans
    Mat img_trans = Mat::zeros(img.rows,img.cols,CV_8UC3);
    // 应用单应性矩阵对图像进行投影变换
    warpPerspective(img,img_trans,transform,img.size());
    imshow("Unnamed",img_trans);
    waitKey(0);
    return 0;
}
int(*run_Affine_Project)()=run768;