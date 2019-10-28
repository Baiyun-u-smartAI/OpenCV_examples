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

	///����ʹ��˵��
	printf("\n \t copyMakeBorder Demo: \n");
	printf("\t -------------------- \n");
	printf("**���� 'c' ��������ñ߿� \n");
	printf("**���� 'r' ��ȡ���߿� \n");
	printf("**���� 'ESC' �Խ������� \n");

	///�½�����
	namedWindow(window_name, WINDOW_AUTOSIZE);

	///�߿���
	top = (int)(0.05*src.rows);     ///��
	bottom = (int)(0.05*src.rows);  ///��
	left = (int)(0.05*src.cols);    ///��
	right = (int)(0.05*src.cols);   ///��

	dst = src;

	imshow(window_name, dst);

	for (;;)
	{
		c = waitKey(500);

		if ((char)c == 27) {
			break;
		} else if ((char)c == 'c') {
			//���̶�ֵ
			borderType = BORDER_CONSTANT;
		} else if ((char)c == 'r') {
			//ԭͼֵ�ӿ�
			borderType = BORDER_REPLICATE;
		}

		///�߿�ֵ��ʹ��rng�������0��254���ֵ������255
		Scalar value(rng.uniform(0, 255), rng.uniform(0, 255),
			rng.uniform(0, 255));

		///valueֵֻ��borderType = BORDER_CONSTANT������
		copyMakeBorder(src, dst, top, bottom, left, right,
			borderType, value);

		imshow(window_name, dst);
	}

	return 0;
}
int(*run_copyMakeBorder_demo)()=run318;