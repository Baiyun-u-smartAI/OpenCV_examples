#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;

int run2356()
{
	Mat image1, image2, image3;

	image1 = imread("1.jpg");
	if (!image1.data)
		return 0;

	image2= imread("2.png");
	if (!image2.data)
		return 0;

	// ��image2ͼ���С����image1ͼ���С
	resize(image2, image3, image1.size());

	//��ʾԭͼ
	namedWindow("Image 1");
	imshow("Image 1",image1);

	namedWindow("Image 3");
	imshow("Image 3",image3);

	// ��ͼ�����ͼ
	Mat result;

	image3 = image3 * 0.3;
	image1 = image1 * 0.9;
	// result[x,y]=image1[x,y] * 0.9+image3[x,y] * 0.3
	add(image1, image3, result);

	namedWindow("result");
	imshow("result",result);

	waitKey();

	return 0;
}

int (*run_Effect)() =&run2356;
