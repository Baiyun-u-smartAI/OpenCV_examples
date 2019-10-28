#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace std;
using namespace cv;

///����ȫ�ֱ���
static Mat img;static  Mat templ;static  Mat result;
static const char* image_window = "Source Image";
static const char* result_window = "Result window";

static int match_method;

///�������ֵ
static int max_Trackbar = 5;

///��������
void MatchingMethod(int, void*);


int run913()
{
	///����ͼ���ļ�
	img = imread("1.jpg", 1);
	imshow("1", img);

	//���� ����ģ��
	templ = imread("Crop_1.jpg", 1);
	imshow("Crop-1", templ);

	/// ��������
	namedWindow(image_window, WINDOW_AUTOSIZE);
	namedWindow(result_window, WINDOW_AUTOSIZE);

	/// ��������
	// 0: SQDIFF          1: SQDIFF NORMED 2: TM CCORR 
	// 3: TM CCORR NORMED 4: TM COEFF      5: TM COEFF NORMED
	const char* trackbar_label = "Method: ";
	createTrackbar(trackbar_label, image_window,
		&match_method, max_Trackbar, MatchingMethod);

	// ƥ��
	MatchingMethod(0, 0);

    waitKey(0);
	return 0;
}

// ��ΪҪ�����������ò���
void MatchingMethod(int, void*)
{
	/// ����ԭͼ
	Mat img_display;
	img.copyTo(img_display);

	/// �����������
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	result.create(result_cols, result_rows, CV_32FC1);

	/// ִ��ƥ�������滯
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal, maxVal;
	Point minLoc, maxLoc, matchLoc;

	/// Ѱ��ͼ���������С��λ��
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// �� SQDIFF �� SQDIFF_NORMED��Խ��ֵ�ȽϽ��Խ��
	/// ����������Խ��Խ����
	if (match_method == TM_SQDIFF
		|| match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	// ��ƥ������Χ
	// ԭͼ
	rectangle(img_display, matchLoc,
		Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
		Scalar::all(0), 2, 8, 0);
	// ���滯���
	rectangle(result, matchLoc,
		Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
		Scalar::all(0), 2, 8, 0);


    result.convertTo(result, CV_8UC3, 255);
    /// ��ʾ���
	imshow(image_window, img_display);
	imshow(result_window, result);

	return;
}
int(*run_MatchTemplate_Demo)()=run913;