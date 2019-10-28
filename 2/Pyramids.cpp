#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

/// ����ȫ�ֱ���
static Mat src, dst, tmp;
static const char* window_name = "Pyramids Demo";

int run312()
{
	/// ����ʹ��˵��
	printf("\n ͼ������ʾ��\n ");
	printf("------------------ \n");
	printf(" * [u] -> �Ŵ� \n");
	printf(" * [d] -> ��С \n");
	printf(" * [ESC] -> �������� \n \n");

	src = imread("animals.jpg");
	if (!src.data)
	{
		printf(" No data! -- Exiting the program \n");
		return -1;
	}

	// ������ͼ����Ҫ����ı�����
	tmp = src;
	dst = tmp;

	/// ��������
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
			printf("** �Ŵ�: �Ŵ�����\n");
		} else if ((char)c == 'd') {
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** ��С: ��Сһ��\n");
		}

		imshow(window_name, dst);

		// ���������Ҫ�����ͼ
		tmp = dst;
	}

	return 0;
}

int(*run_Pyramids)() = run312;