#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

int run139()
{
	Mat src, dst, kernel;

	Point anchor;
	double delta;
	int ddepth;
	int kernel_size;
	const char* window_name = "filter2D Demo";

	int c;

	src = imread("animals.jpg");
	if (!src.data)
		return -1;

	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// filter2D�����ĳ�ʼ����(arguments)
	/// ����
	anchor = Point(-1, -1);

	/// �������̼ӵ�ÿ�����ص�ֵ
	delta = 0;

	/// dst����ȣ�-1��ʾ��Ԫͼ��ͬ
	ddepth = -1;

	/// Loop - ÿ 0.5 ��(500����)�ò�ͬ�ĺ��Ĵ�Сɸѡ (filter) ͼ��
	int ind = 0;
	for (;;)
	{
		c = waitKey(500);
		/// �� 'ESC' ��������
		if ((char)c == 27)
		{
			break;
		}

		/// ���������ķ���ɸѡ(normalized box filter)�����º��Ĵ�С
		kernel_size = 3 + 2 * (ind % 5);
		kernel = Mat::ones(kernel_size, kernel_size, CV_32F)
			/ (float)(kernel_size*kernel_size);

		/// ��ʼɸѡ
		filter2D(src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

		imshow(window_name, dst);

		ind++;
	}

	return 0;
}
int(*run_filter2D_demo)()=run139;