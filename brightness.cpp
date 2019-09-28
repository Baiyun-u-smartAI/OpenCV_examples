#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
using namespace cv;

double alpha; /**< Simple contrast control */
int beta; /**< Simple brightness control */
int main(int argc, char** argv)
{
	Mat image = imread("C:\\images\\lena.jpg");

	Mat new_image = Mat::zeros(image.size(), image.type());
	imshow("zero", new_image);

	/// Initialize values (Basic Linear Transform)
	std::cout << " ��������ת��" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "* ���� alpha ֵ [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "* ���� beta ֵ [0-100]: "; std::cin >> beta;

	/// ת����ʽ new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				// ������ص�ÿ��ɫ����ת��
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	imshow("Original Image", image);
	imshow("New Image", new_image);

	waitKey();

	return 0;
}