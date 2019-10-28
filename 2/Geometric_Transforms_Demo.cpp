#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///����ȫ�ֱ���
const char* source_window = "ԭͼ";
const char* warp_window = "����";
const char* warp_rotate_window = "���� + ��ת";

int run993()
{
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;

	///����ͼ���ļ�
	src = imread("1.jpg", 1);

	///���ý����ԭͼ��ͬ��С
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	///���ü���Affineת����������
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1.f, 0);
	srcTri[2] = Point2f(0, src.rows - 1.f);

	dstTri[0] = Point2f(src.cols*0.0f, src.rows*0.33f);
	dstTri[1] = Point2f(src.cols*0.85f, src.rows*0.25f);
	dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);

	///ȡ��Affineת���Ľ��
	warp_mat = getAffineTransform(srcTri, dstTri);

	/// ��Affineת���Ľ��Ӧ�õ�ԭͼ
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	/** Rotating the image after Warp */

	///����ͼ�����ļ�����ת����
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	///ȡ����ת����
	rot_mat = getRotationMatrix2D(center, angle, scale);

	///��תͼ
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());


	///��ʾ���
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	namedWindow(warp_window, WINDOW_AUTOSIZE);
	imshow(warp_window, warp_dst);

	namedWindow(warp_rotate_window, WINDOW_AUTOSIZE);
	imshow(warp_rotate_window, warp_rotate_dst);

	/// �ȴ�����
	waitKey(0);

	return 0;
}
int(*run_Geometric_Transforms_Demo)()=run993;