#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;
// ����ȫ�ֱ���
static Mat image0, image, gray, mask;
static int ffillMode = 1;   // ���ɫģʽ
static int loDiff = 20, upDiff = 20; // ������ʼ��������ɫ��
static int connectivity = 4;  // connectivity ģʽ
static int isColor = true;   // �ҶȻ��ɫ
static bool useMask = false;  // ʹ���ڱ�
static int newMaskVal = 255;
// ���ظ�����
static void onMouse(int event, int x, int y, int, void*)
{
	if (event != EVENT_LBUTTONDOWN)
		return;
	Point seed = Point(x, y);
	int lo = ffillMode == 0 ? 0 : loDiff;
	int up = ffillMode == 0 ? 0 : upDiff;
	int flags = connectivity + (newMaskVal << 8) +
		(ffillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;
	Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 +
		b*0.114);
	Mat dst = isColor ? image : gray;
	int area;
	// ʹ���ڱ�
	if (useMask)
	{
		threshold(mask, mask, 1, 128, THRESH_BINARY);
		area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
		imshow("mask", mask);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
	}
	imshow("image", dst);
	cout << area << " ����(pixel)���ػ�\n";
}
int run562()
{
	char* filename = "fruits.jpg";
	image0 = imread(filename, 1);
	if (image0.empty())
	{
		cout << "��ȡ�ĵ�ʧ��\n";
		return 0;
	}
	image0.copyTo(image);
	cvtColor(image0, gray, COLOR_BGR2GRAY);
	mask.create(image0.rows + 2, image0.cols + 2, CV_8UC1);
	namedWindow("image", 0);
	// �������ڻ��˻ظ�����
	createTrackbar("lo_diff", "image", &loDiff, 255, 0);
	createTrackbar("up_diff", "image", &upDiff, 255, 0);
	// �������ظ�����
	setMouseCallback("image", onMouse, 0);
	for (;;)
	{
		imshow("image", isColor ? image : gray);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "���� ...\n";
			break;
		}
		switch ((char)c)
		{
		case 'c':
			if (isColor)
			{
				cout << "��ɻҶ�\n";
				cvtColor(image0, gray, COLOR_BGR2GRAY);
				mask = Scalar::all(0);
				isColor = false;
			}
			else
			{
				cout << "��ɲ�ɫ\n";
				image0.copyTo(image);
				mask = Scalar::all(0);
				isColor = true;
			}
			break;
		case 'm':
			if (useMask)
			{
				destroyWindow("mask");
				useMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				mask = Scalar::all(0);
				imshow("mask", mask);
				useMask = true;
			}
			break;
		case 'r':
			cout << "��ԭͼ��\n";
			image0.copyTo(image);
			cvtColor(image, gray, COLOR_BGR2GRAY);
			mask = Scalar::all(0);
			break;
		case 's':
			cout << "���ü������ɫģʽ\n";
			ffillMode = 0;
			break;
		case 'f':
			cout << "���ù̶���Χ���ɫģʽ\n";
			ffillMode = 1;
			break;
		case 'g':
			cout << "���� Gradient (floating range) ���ɫģʽ\n";
			ffillMode = 2;
			break;
		case '4':
			cout << "���� 4-connectivity ģʽ\n";
			connectivity = 4;
			break;
		case '8':
			cout << "���� 8-connectivity ģʽ\n";
			connectivity = 8;
			break;
		}
	}
	return 0;
}
int(*run_calcBackProject_Demo3)()=run562;