/*  For description look into the help() function. */
#include "OpenCV_example.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

static void help()
{
	cout
		<< "\n--------------------------------------------------------------------------" << endl
		<< "This program shows how to create matrices(cv::Mat) in OpenCV and its serial"
		<< " out capabilities" << endl
		<< "That is, cv::Mat M(...); M.create and cout << M. " << endl
		<< "Shows how output can be formated to OpenCV, python, numpy, csv and C styles." << endl
		<< "Usage:" << endl
		<< "./cvout_sample" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< endl;
}

//为了多重导入cpp文件，只是将main函数换了个名字
int run143()
{
	//help();

	// create by using the constructor
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));

	cout << "M = " << endl << " " << M <<  endl;

	// Can not use waitkey for M

	// create by using the create function()
	M.create(2, 2, CV_8UC(2));

	cout << "M = " << endl << " " << M << endl;

	// create multidimensional matrices
	int sz[3] = { 2, 2, 2 };
	Mat L(3, sz, CV_8UC(1), Scalar::all(0));
	// Cannot print via operator <<

	// Create using MATLAB style eye, ones or zero matrix
	Mat E = Mat::eye(3, 3, CV_64F);
	cout << "E = " << endl << " " << E << endl;

	Mat O = Mat::ones(2, 2, CV_32F);
	cout << "O = " << endl << " " << O << endl;

	Mat Z = Mat::zeros(2, 2, CV_8UC1);
	cout << "Z = " << endl << " " << Z << endl;

	// create a 3x3 double-precision identity matrix
	Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C = " << endl << " " << C << endl << endl;

	Mat RowClone = C.row(1).clone();
	cout << "RowClone = " << endl << " " << RowClone << endl;

	// Fill a matrix with random values
	Mat R = Mat(3, 2, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255));

	// Demonstrate the output formating options
	cout << "R (default) = " << endl << R << endl;
	cout << "R (python)  = " << endl << format(R, Formatter::FMT_PYTHON) << endl;
	cout << "R (numpy)   = " << endl << format(R, Formatter::FMT_NUMPY) << endl;
	cout << "R (csv)     = " << endl << format(R, Formatter::FMT_CSV) << endl;
	cout << "R (c)       = " << endl << format(R, Formatter::FMT_C) << endl;
	Point2f P(5, 1);

	cout << "Point (2D) = " << P << endl << endl;

	Point3f P3f(2, 6, 7);
	cout << "Point (3D) = " << P3f << endl << endl;


	vector<float> v;
	v.push_back((float)CV_PI);   v.push_back(2);    v.push_back(3.01f);

	cout << "浮点向量矩阵 = " << Mat(v) << endl << endl;

	vector<Point2f> vPoints(5);
	for (size_t i = 0; i < vPoints.size(); ++i)
		vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));

	cout << "二维图点向量 = " << vPoints << endl << endl;

	getchar();
	return 0;
}


//强制让main.cpp执行run_mat_the_basic_image_container()时，指向改文件的函数
int (*run_mat_the_basic_image_container)() =&run143;
