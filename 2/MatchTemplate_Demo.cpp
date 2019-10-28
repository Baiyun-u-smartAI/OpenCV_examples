#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace std;
using namespace cv;

///声明全局变量
static Mat img;static  Mat templ;static  Mat result;
static const char* image_window = "Source Image";
static const char* result_window = "Result window";

static int match_method;

///滑杆最大值
static int max_Trackbar = 5;

///声明函数
void MatchingMethod(int, void*);


int run913()
{
	///加载图形文件
	img = imread("1.jpg", 1);
	imshow("1", img);

	//记载 载入模板
	templ = imread("Crop_1.jpg", 1);
	imshow("Crop-1", templ);

	/// 建立窗口
	namedWindow(image_window, WINDOW_AUTOSIZE);
	namedWindow(result_window, WINDOW_AUTOSIZE);

	/// 建立滑杆
	// 0: SQDIFF          1: SQDIFF NORMED 2: TM CCORR 
	// 3: TM CCORR NORMED 4: TM COEFF      5: TM COEFF NORMED
	const char* trackbar_label = "Method: ";
	createTrackbar(trackbar_label, image_window,
		&match_method, max_Trackbar, MatchingMethod);

	// 匹配
	MatchingMethod(0, 0);

    waitKey(0);
	return 0;
}

// 因为要传参数但又用不到
void MatchingMethod(int, void*)
{
	/// 复制原图
	Mat img_display;
	img.copyTo(img_display);

	/// 建立结果数组
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	result.create(result_cols, result_rows, CV_32FC1);

	/// 执行匹配与正规化
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal, maxVal;
	Point minLoc, maxLoc, matchLoc;

	/// 寻找图中最大与最小的位置
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// 用 SQDIFF 与 SQDIFF_NORMED是越低值比较结果越好
	/// 其它方法是越高越好试
	if (match_method == TM_SQDIFF
		|| match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	// 绘匹配结果范围
	// 原图
	rectangle(img_display, matchLoc,
		Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
		Scalar::all(0), 2, 8, 0);
	// 正规化结果
	rectangle(result, matchLoc,
		Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
		Scalar::all(0), 2, 8, 0);


    result.convertTo(result, CV_8UC3, 255);
    /// 显示结果
	imshow(image_window, img_display);
	imshow(result_window, result);

	return;
}
int(*run_MatchTemplate_Demo)()=run913;