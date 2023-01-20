#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
	Mat src = imread("dark.jfif");

	Mat gray, dst;
	cvtColor(src, gray, COLOR_BGR2GRAY);// 得到灰度图
	imshow("gray origin", gray);// 显示灰度图
	equalizeHist(gray, dst);// 应用直方图均衡化
	imshow("eq", dst);// 显示
   

	waitKey(0);
	return 0;
}