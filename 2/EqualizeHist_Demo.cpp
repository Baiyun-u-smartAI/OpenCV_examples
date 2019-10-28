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

	///����ͼ���ļ�
	src = imread("1.jpg", 1);
	if (!src.data)
		return -1;

	//ת�ɻҶ�
	cvtColor(src, src, COLOR_BGR2GRAY);

	///��ɫ�׷ֲ�ͼ (Histogram) �Ȼ�(Equalization)
	equalizeHist(src, dst);

	//��ʾ���
	namedWindow(source_window, WINDOW_AUTOSIZE);
	namedWindow(equalized_window, WINDOW_AUTOSIZE);

	imshow(source_window, src);
	imshow(equalized_window, dst);

	//�ȴ�����
	waitKey(0);

	return 0;

}
int(*run_EqualizeHist_Demo)()=run324;