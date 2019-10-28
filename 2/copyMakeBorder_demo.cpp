#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

static Mat src, dst;
static int top, bottom, left, right;
static int borderType;
static const char* window_name = "copyMakeBorder Demo";
RNG rng(12345);

int run318()
{

	int c;

	src = imread("1.jpg");
	if (!src.data)
		return -1;

	imshow("org", src);

	///程序使用说明
	printf("\n \t copyMakeBorder Demo: \n");
	printf("\t -------------------- \n");
	printf("**按下 'c' 以随机设置边框 \n");
	printf("**按下 'r' 以取消边框 \n");
	printf("**按下 'ESC' 以结束程序 \n");

	///新建窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);

	///边框厚度
	top = (int)(0.05*src.rows);     ///上
	bottom = (int)(0.05*src.rows);  ///下
	left = (int)(0.05*src.cols);    ///左
	right = (int)(0.05*src.cols);   ///右

	dst = src;

	imshow(window_name, dst);

	for (;;)
	{
		c = waitKey(500);

		if ((char)c == 27) {
			break;
		} else if ((char)c == 'c') {
			//补固定值
			borderType = BORDER_CONSTANT;
		} else if ((char)c == 'r') {
			//原图值加框
			borderType = BORDER_REPLICATE;
		}

		///边框值，使用rng随机产生0与254间的值，不含255
		Scalar value(rng.uniform(0, 255), rng.uniform(0, 255),
			rng.uniform(0, 255));

		///value值只有borderType = BORDER_CONSTANT才有用
		copyMakeBorder(src, dst, top, bottom, left, right,
			borderType, value);

		imshow(window_name, dst);
	}

	return 0;
}
int(*run_copyMakeBorder_demo)()=run318;