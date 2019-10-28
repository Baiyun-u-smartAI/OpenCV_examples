#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

int run943()
{

	Mat src, src_gray, grad;

	const char* window_name = "Sobel Demo - Simple Edge Detector";

	// Sobel函数用到的参数
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	/// 载入图档
	src = imread("1.jpg");
	if (!src.data)
		return -1;

	// 于原图使用Gaussian模糊法,使用Kernel Size(3, 3)先去除噪声
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// 转换成灰度
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	/// 建立窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// 建立 grad_x 与 grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// 倾斜度 (Gradient) X
	/*
	Scharr( src_gray, grad_x, ddepth, 1, 0,
		scale, delta, BORDER_DEFAULT );
	*/
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3,
		scale, delta, BORDER_DEFAULT);
	/*
	int kernel_size = 3;
	Laplacian(src_gray, grad_x, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	*/
	/// 转成绝对值8位图像
	convertScaleAbs(grad_x, abs_grad_x,0.5,0);

	/// 倾斜度 Y
	/*
	Scharr( src_gray, grad_y, ddepth, 0, 1,
		scale, delta, BORDER_DEFAULT );
	*/

	Sobel(src_gray, grad_y, ddepth, 0, 1, 3,
		scale, delta, BORDER_DEFAULT);
	/*
	Laplacian(src_gray, grad_y, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	*/
	
	convertScaleAbs(grad_y, abs_grad_y,0.5,0);

	/// 总倾斜度 (大约的)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow(window_name, grad);

	waitKey(0);

	return 0;
}
int(*run_Sobel_Demo)()=run943;