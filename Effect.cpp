#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;

int main()
{
	Mat image1, image2, image3;

	image1 = imread("C:\\images\\lake.jpg");
	if (!image1.data)
		return 0;

	image2= imread("C:\\images\\fur.jpg");
	if (!image2.data)
		return 0; 

	// ��image2ͼ���С����image1ͼ���С
	resize(image2, image3, image1.size());

	//��ʾԭͼ
	namedWindow("Image 1");
	imshow("Image 1",image1);

	namedWindow("Image 3");
	imshow("Image 3",image3);

	// ������Чͼ
	Mat result;

	image3 = image3 * 0.3;
	image1 = image1 * 0.9;
	add(image1, image3, result);

	namedWindow("result");
	imshow("result",result);

	waitKey();

	return 0;
}