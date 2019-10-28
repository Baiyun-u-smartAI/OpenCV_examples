#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///声明全局变量
const char* source_window = "原图";
const char* warp_window = "翘曲";
const char* warp_rotate_window = "翘曲 + 旋转";

int run993()
{
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;

	///加载图形文件
	src = imread("1.jpg", 1);

	///设置结果与原图相同大小
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	///设置计算Affine转换的三个点
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1.f, 0);
	srcTri[2] = Point2f(0, src.rows - 1.f);

	dstTri[0] = Point2f(src.cols*0.0f, src.rows*0.33f);
	dstTri[1] = Point2f(src.cols*0.85f, src.rows*0.25f);
	dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);

	///取得Affine转换的结果
	warp_mat = getAffineTransform(srcTri, dstTri);

	/// 将Affine转换的结果应用到原图
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	/** Rotating the image after Warp */

	///根据图的中心计算旋转矩阵
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	///取得旋转矩阵
	rot_mat = getRotationMatrix2D(center, angle, scale);

	///旋转图
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());


	///显示结果
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	namedWindow(warp_window, WINDOW_AUTOSIZE);
	imshow(warp_window, warp_dst);

	namedWindow(warp_rotate_window, WINDOW_AUTOSIZE);
	imshow(warp_rotate_window, warp_rotate_dst);

	/// 等待按键
	waitKey(0);

	return 0;
}
int(*run_Geometric_Transforms_Demo)()=run993;