#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

// 宣告程序用到的副裎式
Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int run2301()
{
	Mat I, J;
	I = imread("1.jpg", IMREAD_COLOR);
	if (!I.data)
	{
		cout << "无法载入 1.jpg 图档." << endl;
		return -1;
	}

	// 将字符串转成 C++ 型态的数字
	int divideWith = 0;
	stringstream s;
	s << "5";
	s >> divideWith;
	if (!s || !divideWith)
	{
		cout << "非有效数字. " << endl;
		return -1;
	}

	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));

	const int times = 100;
	double t;

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		J = ScanImageAndReduceC(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "用 C operator [] 降低色屏跑 "
		<< times << " 次: 平均要"
		<< t << " 毫秒." << endl;

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		J = ScanImageAndReduceIterator(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "用 iterator 降低色屏跑 "
		<< times << " 次: 平均要"
		<< t << " 毫秒." << endl;

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		ScanImageAndReduceRandomAccess(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "用 on-the-fly地址产生法 降低色屏跑 "
		<< times << " 次: 平均要"
		<< t << " 毫秒." << endl;

	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; ++i)
		p[i] = table[i];

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
		LUT(I, lookUpTable, J);

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "用 LUT 函示 降低色屏跑  "
		<< times << " 次: 平均要" <<
		t << " 毫秒." << endl;

	cout << "\n- The End - ";

	getchar();

	return 0;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
	// 只接受 char 型态的图块 ( matrices )
	CV_Assert(I.depth() != sizeof(uchar));

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
	// 只接受 char 型态的图块 ( matrices )
	CV_Assert(I.depth() != sizeof(uchar));

	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>();
			it != end; ++it)

			*it = table[*it];
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>();
			it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}

	return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
	// 只接受 char 型态的图块 ( matrices )
	CV_Assert(I.depth() != sizeof(uchar));

	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;

		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
		break;
	}
	}

	return I;
}

int(*run_how_to_scan_images)()=run2301;