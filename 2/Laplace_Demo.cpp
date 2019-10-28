#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

int run732()
{
	Mat src, src_gray, dst;

	/// Laplacian函数用到的参数
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	const char* window_name = "Laplace Demo";

	src = imread("1.jpg");
	if (!src.data)
		return -1;

	/// 于原图使用Gaussian模糊法,使用Kernel Size(3, 3)先去除噪声
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// 转成灰度
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	/// 新建窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// 使用 Laplace 函数
	Mat abs_dst;

	Laplacian(src_gray, dst, ddepth, kernel_size,
		scale, delta, BORDER_DEFAULT);

	// Laplace 函数处理后转成
	convertScaleAbs(dst, abs_dst,0.5,0);

	imshow(window_name, abs_dst);

	waitKey(0);

	return 0;
}

int(*run_Laplace_Demo)()=run732;