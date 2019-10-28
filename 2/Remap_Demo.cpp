#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

///声明全局变量
static Mat src, dst;
static Mat map_x, map_y;
static const char* remap_window = "Remap demo";
static int ind = 0;

///声明函数
void update_map(void);

int run897()
{
	src = imread("1.jpg", 1);

	///用原图的大小创建 dst, map_x and map_y
	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);

	///创建窗口
	namedWindow(remap_window, WINDOW_AUTOSIZE);

	for (;;)
	{
		///等0.1秒
		int c = waitKey(100);

		// 按键是否为 ESC
		if ((char)c == 27)
			break;

		///更新 map_x & map_y
		update_map();

		remap(src, dst, map_x, map_y, INTER_LINEAR,
			BORDER_CONSTANT, Scalar(0, 0, 0));

		imshow(remap_window, dst);

		printf("ind %d", ind);

		waitKey();
	}
	return 0;
}

void update_map(void)
{
	ind = ind % 4;

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			switch (ind)
			{
				case 0:
					if (i > src.cols*0.25 && i < src.cols*0.75
						&& j > src.rows*0.25 && j < src.rows*0.75)
					{
						map_x.at<float>(j, i) = 2 * (i - src.cols*0.25f) + 0.5f;
						map_y.at<float>(j, i) = 2 * (j - src.rows*0.25f) + 0.5f;
					}
					else
					{
						map_x.at<float>(j, i) = 0;
						map_y.at<float>(j, i) = 0;
					}
					break;

				case 1:
					map_x.at<float>(j, i) = (float)i;
					map_y.at<float>(j, i) = (float)(src.rows - j);
					break;

				case 2:
					map_x.at<float>(j, i) = (float)(src.cols - i);
					map_y.at<float>(j, i) = (float)j;
					break;

				case 3:
					map_x.at<float>(j, i) = (float)(src.cols - i);
					map_y.at<float>(j, i) = (float)(src.rows - j);
					break;
			}
		}
	}
	ind++;
}
int(*run_Remap_Demo)()=run897;