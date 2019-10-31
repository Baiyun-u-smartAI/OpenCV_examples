#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void Sharpen(const Mat& myImage, Mat& Result);

int run451()
{
	const char* filename = "1.jpg";

	Mat I, J, K;

	I = imread(filename, IMREAD_COLOR);
	namedWindow("Input", WINDOW_AUTOSIZE);
	namedWindow("getTickCount", WINDOW_AUTOSIZE);
	namedWindow("filter2D", WINDOW_AUTOSIZE);
	// 输入图片显示
	imshow("Input", I);
	double t = (double)getTickCount();
	// 锐化图片I 得到J
	Sharpen(I, J);

	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Hand written function times passed in seconds: " << t << endl;

	imshow("getTickCount", J);
	// 定义滤波核
	Mat kern = (Mat_<char>(3, 3) <<
		0, -1, 0,
	   -1, 5, -1,
		0, -1, 0);

	t = (double)getTickCount();
	filter2D(I, K, I.depth(), kern);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Built-in filter2D time passed in seconds:      " << t << endl;

	imshow("filter2D", K);

	waitKey(0);
	return 0;
}
void Sharpen(const Mat& myImage, Mat& Result)
{
	// 只接受一维图像
	CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images

	const int nChannels = myImage.channels();
	// 建立于初始类型相同的空矩阵
	Result.create(myImage.size(), myImage.type());
	// 行循环,从第一行开始算
	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);

		uchar* output = Result.ptr<uchar>(j);
		// 列循环，从第一列开始算
		for (int i = nChannels; i < nChannels*(myImage.cols - 1); ++i)
		{
			// 滤波核 [[0,-1,0],[-1,5,-1],[0,-1,0]]
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
		}
	}
	// 用黑色填充第0行和第0列的所有元素
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
}

int(*run_mat_mask_operations)()=run451;
