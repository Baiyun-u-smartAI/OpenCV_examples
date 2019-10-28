#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

/// 声明全局变量
static Mat src, dst, tmp;
static const char* window_name = "Pyramids Demo";

int run312()
{
	/// 程序使用说明
	printf("\n 图像缩放示范\n ");
	printf("------------------ \n");
	printf(" * [u] -> 放大 \n");
	printf(" * [d] -> 缩小 \n");
	printf(" * [ESC] -> 结束程序 \n \n");

	src = imread("animals.jpg");
	if (!src.data)
	{
		printf(" No data! -- Exiting the program \n");
		return -1;
	}

	// 将毒入图放入要处理的变量中
	tmp = src;
	dst = tmp;

	/// 建立窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);
	imshow(window_name, dst);

	/// Loop
	for (;;)
	{
		int c;
		c = waitKey(10);

		if ((char)c == 27)
			break;

		if ((char)c == 'u')
		{
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** 放大: 放大两倍\n");
		} else if ((char)c == 'd') {
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** 缩小: 缩小一半\n");
		}

		imshow(window_name, dst);

		// 将结果当成要处理的图
		tmp = dst;
	}

	return 0;
}

int(*run_Pyramids)() = run312;