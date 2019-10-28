#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

int run324()
{
	Mat src, dst;

	const char* source_window = "Source image";
	const char* equalized_window = "Equalized Image";

	///加载图形文件
	src = imread("1.jpg", 1);
	if (!src.data)
		return -1;

	//转成灰度
	cvtColor(src, src, COLOR_BGR2GRAY);

	///用色阶分布图 (Histogram) 等化(Equalization)
	equalizeHist(src, dst);

	//显示结果
	namedWindow(source_window, WINDOW_AUTOSIZE);
	namedWindow(equalized_window, WINDOW_AUTOSIZE);

	imshow(source_window, src);
	imshow(equalized_window, dst);

	//等待按键
	waitKey(0);

	return 0;

}
int(*run_EqualizeHist_Demo)()=run324;