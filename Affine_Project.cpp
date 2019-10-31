//
// Created by Andersson on 2019/10/8.
//
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>
using namespace cv;

int run768(){
    // PerspectiveTransform�����Ҫԭʼͼ����ĸ���ͱ任����ĸ���
    Mat img=imread("Newspaper.jpeg");
    // �����������ĸ��������
    std::vector<Point2f> origin{Point2f(197,13),Point2f(599,124),Point2f(36,262),Point2f(481,441)};
    // �������ͼ����� destination����С����ΪԭͼƬ��С
    std::vector<Point2f> destination(4);
    destination[0]= Point2f(0, 0);
    destination[1]= Point2f(img.cols-1, 0);
    destination[2]= Point2f(0, img.rows-1);
    destination[3]= Point2f(img.cols-1, img.rows-1);
    // ��ⵥӦ�Ծ���
    Mat transform = getPerspectiveTransform(origin,destination);
    // �½��������ͼ��ľ���img_trans
    Mat img_trans = Mat::zeros(img.rows,img.cols,CV_8UC3);
    // Ӧ�õ�Ӧ�Ծ����ͼ�����ͶӰ�任
    warpPerspective(img,img_trans,transform,img.size());
    imshow("Unnamed",img_trans);
    waitKey(0);
    return 0;
}
int(*run_Affine_Project)()=run768;
