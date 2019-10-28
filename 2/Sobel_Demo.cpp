#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

int run943()
{

	Mat src, src_gray, grad;

	const char* window_name = "Sobel Demo - Simple Edge Detector";

	// Sobel�����õ��Ĳ���
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	/// ����ͼ��
	src = imread("1.jpg");
	if (!src.data)
		return -1;

	// ��ԭͼʹ��Gaussianģ����,ʹ��Kernel Size(3, 3)��ȥ������
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// ת���ɻҶ�
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	/// ��������
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// ���� grad_x �� grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// ��б�� (Gradient) X
	/*
	Scharr( src_gray, grad_x, ddepth, 1, 0,
		scale, delta, BORDER_DEFAULT );
	*/
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3,
		scale, delta, BORDER_DEFAULT);
	/*
	int kernel_size = 3;
	Laplacian(src_gray, grad_x, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	*/
	/// ת�ɾ���ֵ8λͼ��
	convertScaleAbs(grad_x, abs_grad_x,0.5,0);

	/// ��б�� Y
	/*
	Scharr( src_gray, grad_y, ddepth, 0, 1,
		scale, delta, BORDER_DEFAULT );
	*/

	Sobel(src_gray, grad_y, ddepth, 0, 1, 3,
		scale, delta, BORDER_DEFAULT);
	/*
	Laplacian(src_gray, grad_y, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	*/
	
	convertScaleAbs(grad_y, abs_grad_y,0.5,0);

	/// ����б�� (��Լ��)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow(window_name, grad);

	waitKey(0);

	return 0;
}
int(*run_Sobel_Demo)()=run943;