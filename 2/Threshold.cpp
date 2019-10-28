#include "opencv2/opencv.hpp"
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

int run3901()
{
	namedWindow("orignal", WINDOW_AUTOSIZE);
	//namedWindow("threshold", WINDOW_AUTOSIZE);
	// 读取图像
	Mat src = imread("stuff.jpg", IMREAD_GRAYSCALE);
	imshow("orignal", src);

	waitKey(0);

	Mat dst;

	// 基本临界值运算
	threshold(src, dst, 0, 255, THRESH_BINARY);
	imshow("二进制阈值法", dst);

	//waitKey(0);

	// Thresholding with maxval set to 128
	threshold(src, dst, 0, 128, THRESH_BINARY);
	imshow("二进制阈值法", dst);

	//waitKey(0);

	// 临界值设为 127
	threshold(src, dst, 127, 255, THRESH_BINARY);
	imshow("二进制阈值法", dst);

	waitKey(0);

	// 使用 THRESH_BINARY_INV 临界值
	threshold(src, dst, 127, 255, THRESH_BINARY_INV);
	imshow("反向二进制阈值法", dst);

	waitKey(0);

	// 使用 THRESH_TRUNC 临界值
	threshold(src, dst, 127, 255, THRESH_TRUNC);
	imshow("截断阈值法", dst);

	waitKey(0);

	// 使用 THRESH_TOZERO 临界值
	threshold(src, dst, 127, 255, THRESH_TOZERO);
	imshow("阈值为零法", dst);

	waitKey(0);

	// 使用 THRESH_TOZERO_INV 临界值
	threshold(src, dst, 127, 255, THRESH_TOZERO_INV);
	imshow("反向阈值为零法", dst);

	waitKey(0);
}

int (*run_Threshold)()=run3901;