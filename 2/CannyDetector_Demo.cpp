#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

/// 声明全局变量
static Mat src, src_gray;
static Mat dst, detected_edges;

static int edgeThresh = 1;
static int lowThreshold;
static int const max_lowThreshold = 100;
static int ratio = 3;
static int kernel_size = 3;
static const char* window_name = "Edge Map";

// 滑杆回调函数 - Canny 以1:3作掩码输入
// 因为用不到传入的参数，所以没取参数变量名
static void CannyThreshold(int, void*)
{
	/// 以3x3的核心减少噪声
	blur(src_gray, detected_edges, Size(3, 3));

	/// Canny 检测器
	Canny(detected_edges, detected_edges, lowThreshold,
		lowThreshold*ratio, kernel_size);

	/// 用 Canny 的输出作掩码, 
	dst = Scalar::all(0);

	/// 将src以detected_edges为掩码复制到dst
	src.copyTo(dst, detected_edges);

	/// 显示掩码后结果
	imshow(window_name, dst);
	//imshow(window_name, detected_edges);
}

int run563()
{
	src = imread("1.jpg");
	if (!src.data)
		return -1;

	imshow("Lexus", src);

	/// 建一个与原图大小与型态一样的数组
	dst.create(src.size(), src.type());

	/// 转成灰度
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	/// 新建窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// 建立滑杆用来作掩码值得输入
	createTrackbar("Min Threshold:", window_name, &lowThreshold,
		max_lowThreshold, CannyThreshold);

	/// 掩码后显示结果
	CannyThreshold(0, 0);

	waitKey(0);

	return 0;
}

int(*run_CannyDetector_Demo)()=run563;