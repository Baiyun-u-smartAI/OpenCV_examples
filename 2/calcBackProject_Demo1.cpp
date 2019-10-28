#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///声明全局变量
static Mat src, hsv, hue;
static int bins = 25;

///声明函数
void Hist_and_Backproj(int, void*);

int run1948()
{
	///加载图形文件
	src = imread("hand_sample1.jpg", 1);

	///转成HSVV
	cvtColor(src, hsv, COLOR_BGR2HSV);

	///仅用色调（Hue）值
	hue.create(hsv.size(), hsv.depth());
	int ch[] = { 0, 0 };
	mixChannels(&hsv, 1, &hue, 1, ch, 1);

	const char* window_image = "Source image";
	namedWindow(window_image, WINDOW_AUTOSIZE);

	///创建滑杆以输入bins
	createTrackbar("* Hue  bins: ", window_image,
		&bins, 180, Hist_and_Backproj);

	Hist_and_Backproj(0, 0);

	///显示结果
	imshow(window_image, src);

	///等待按键
	waitKey(0);
	return 0;
}

void Hist_and_Backproj(int, void*)
{
	MatND hist;
	int histSize = MAX(bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	///色阶分布（Histogram)
	calcHist(&hue, 1, 0, Mat(), hist, 1,
		&histSize, &ranges, true, false);

	///正规化（normalize）
	normalize(hist, hist, 0, 255,
		NORM_MINMAX, -1, Mat());

	///取得后方投影（Backprojection）
	MatND backproj;
	calcBackProject(&hue, 1, 0, hist,
		backproj, &ranges, 1, true);

	/// Draw the backproj
	imshow("BackProj", backproj);

	///显示结果
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	for (int i = 0; i < bins; i++)
	{
		rectangle(histImg, Point(i*bin_w, h),
			Point((i + 1)*bin_w,
			h - cvRound(hist.at<float>(i)*h / 255.0)),
			Scalar(0, 0, 255), -1);
	}

	imshow("Histogram", histImg);

}
int(*run_calcBackProject_Demo1)()=run1948;